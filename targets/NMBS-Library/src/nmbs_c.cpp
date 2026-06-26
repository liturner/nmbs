/// @file nmbs_c.cpp
/// @brief Compilation unit to include anything C (currently libxml) related.
/// @details The intention of this file is to place in one location all the
/// C code (which requires particular care) into one location.
///
/// @author Luke Ian Turner
/// @date 2026-06-13
/// @copyright Copyright (c) 2026 Luke Ian Turner
/// @copyright
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// @copyright
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
/// @copyright
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

#include "nmbs_private.h"
#include "nmbs/binding.h"
#include "nmbs/spif.h"
#include "nmbs/c/nmbs.h"

[[nodiscard]] nmbs_security_policies* nmbs_security_policies_new() noexcept
{
    auto return_policies = new nmbs_security_policies;
    return_policies->size = 0;
    return_policies->policy = nullptr;
    return return_policies;
}


void nmbs_security_policies_read_installed(nmbs_security_policies* policies_out) noexcept
{
    auto& policies_cpp = nmbs::spif::get_security_policies();
    if (policies_cpp.empty())
    {
        return;
    }

    policies_out->policy = new nmbs_security_policy[policies_cpp.size()];
    policies_out->size = policies_cpp.size();

    for (int i = 0; i < policies_cpp.size(); ++i)
    {
        policies_out->policy[i].name = new char[policies_cpp[i].name.length() + 1];
        std::memcpy(policies_out->policy[i].name, policies_cpp[i].name.c_str(), policies_cpp[i].name.length() + 1);
        policies_out->policy[i].security_classifications = new nmbs_security_classification[policies_cpp[i].security_classifications.size()];
        policies_out->policy[i].classification_count = policies_cpp[i].security_classifications.size();
        for (int j = 0; j < policies_cpp[i].security_classifications.size(); ++j)
        {
            policies_out->policy[i].security_classifications[j].name = new char[policies_cpp[i].security_classifications[j].name.length() + 1];
            std::memcpy(policies_out->policy[i].security_classifications[j].name,
                policies_cpp[i].security_classifications[j].name.c_str(),
                policies_cpp[i].security_classifications[j].name.length() + 1);
        }
    }
}

void nmbs_confidentiality_labels_read_labels(nmbs_confidentiality_labels* labels_out, const char* file) noexcept
{
    try
    {
        const auto labels = nmbs::read_labels(std::filesystem::path(std::string(file)));
        if (labels.empty())
        {
            return;
        }
        labels_out->label = new nmbs_confidentiality_label[labels.size()];
        labels_out->size = labels.size();
        for (int i = 0; i < labels.size(); ++i)
        {
            labels_out->label[i].policy_identifier = new char[labels[i].confidentiality_information.policy_identifier.size() + 1];
            memcpy(labels_out->label[i].policy_identifier,
                labels[i].confidentiality_information.policy_identifier.c_str(),
                labels[i].confidentiality_information.policy_identifier.size() + 1);

            labels_out->label[i].classification = new char[labels[i].confidentiality_information.classification.size() + 1];
            memcpy(labels_out->label[i].classification,
                labels[i].confidentiality_information.classification.c_str(),
                labels[i].confidentiality_information.classification.size() + 1);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "C++ Exception caught in nmbs_confidentiality_labels_read_labels: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "C++ Exception caught in nmbs_confidentiality_labels_read_labels" << std::endl;
    }
}

int nmbs_confidentiality_labels_write_labels(const char* file, const nmbs_confidentiality_labels* labels) noexcept
{
    try
    {
        std::vector<nmbs::confidentiality_label> cpp_labels(labels->size);
        cpp_labels.resize(labels->size);
        for (int i = 0; i < labels->size; ++i)
        {
            cpp_labels[i].label_type = nmbs::confidentiality_label::originator;
            cpp_labels[i].confidentiality_information.policy_identifier = labels->label[i].policy_identifier;
            cpp_labels[i].confidentiality_information.classification = labels->label[i].classification;
        }

        nmbs::write_labels(std::filesystem::path(std::string(file)), cpp_labels);
        return nmbs::success;
    }
    catch (const nmbs::exception& e) {
        std::cerr << "C++ Exception caught in nmbs_write_labels: " << e.what() << std::endl;
        return e.code();
    }
    catch (const std::exception& e) {
        std::cerr << "C++ Exception caught in nmbs_write_labels: " << e.what() << std::endl;
        return nmbs::unknown_error;
    }
    catch (...)
    {
        std::cerr << "C++ Exception caught in nmbs_write_labels" << std::endl;
        return nmbs::unknown_error;
    }
}

[[nodiscard]] uint32_t nmbs_binding_flags_read_support(const char* file) noexcept
{
    if (!file) {
        return 0;
    }
    try
    {
        const std::filesystem::path target_path(file);
        nmbs::binding::flags cpp_flags = nmbs::binding::support(target_path);
        return static_cast<uint32_t>(cpp_flags);
    }
    catch (const std::exception& e) {
        std::cerr << "C++ Exception caught in nmbs_binding_support: " << e.what() << std::endl;
        return 0;
    }
    catch (...)
    {
        std::cerr << "C++ Exception caught in nmbs_binding_support" << std::endl;
        return 0;
    }
}

[[nodiscard]] nmbs_confidentiality_labels* nmbs_confidentiality_labels_new() noexcept
{
    auto labels = new nmbs_confidentiality_labels;
    labels->size = 0;
    labels->label = nullptr;
    return labels;
}

void nmbs_confidentiality_labels_delete(nmbs_confidentiality_labels* labels) noexcept
{
    try
    {
        for (int i = 0; i < labels->size; ++i)
        {
            delete[] labels->label[i].policy_identifier;
            delete[] labels->label[i].classification;
        }
        delete[] labels->label;
        delete labels;
    }
    catch (...)
    {
        std::cerr << "C++ Exception caught in during nmbs_confidentiality_labels_delete. High chance of memory leaks!" << std::endl;
    }
}

void nmbs_security_policies_delete(nmbs_security_policies* policies) noexcept
{
    try
    {
        for (int i = 0; i < policies->size; ++i)
        {
            for (unsigned long j = 0; j < policies->policy[i].classification_count; ++j)
            {
                delete[] policies->policy[i].security_classifications[j].name;
            }
            delete[] policies->policy[i].name;
            delete[] policies->policy[i].security_classifications;
        }
        delete[] policies->policy;
        delete policies;
    }
    catch (...)
    {
        std::cerr << "C++ Exception caught in during nmbs_security_policies_delete. High chance of memory leaks!" << std::endl;
    }
}
