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
#include <chrono>
#include <cstring>
#include <string>

#include "nmbs_private.h"
#include "nmbs/binding.h"
#include "nmbs/c/nmbs.h"

nmbs_confidentiality_labels nmbs_read_labels(const char* file) noexcept
{
    nmbs_confidentiality_labels return_labels;
    return_labels.size = 0;
    return_labels.label = nullptr;

    try
    {
        const auto labels = nmbs::read_labels(std::filesystem::path(std::string(file)));
        if (labels.empty())
        {
            return return_labels;
        }

        return_labels.label = static_cast<nmbs_confidentiality_label*>(std::malloc(labels.size() * sizeof(nmbs_confidentiality_label)));
        if (!return_labels.label)
        {
            nmbs_free_confidentiality_labels(&return_labels);
            return return_labels;
        }

        for (int i = 0; i < labels.size(); ++i)
        {
            return_labels.label[i].policy_identifier = strdup(labels[i].confidentiality_information.policy_identifier.c_str());
            return_labels.label[i].classification = strdup(labels[i].confidentiality_information.classification.c_str());
            ++return_labels.size;
        }
        return return_labels;
    }
    catch (const std::exception& e) {
        // Log the error inside C++ so you know what went wrong
        std::cerr << "C++ Exception caught in nmbs_read_labels: " << e.what() << std::endl;
        return return_labels;
    }
    catch (...)
    {
        std::cerr << "C++ Exception caught in nmbs_read_labels" << std::endl;
        return return_labels;
    }
}

int nmbs_write_labels(const char* file, const nmbs_confidentiality_labels* labels) noexcept
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

[[nodiscard]] uint32_t nmbs_binding_support(const char* file) noexcept
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

void nmbs_free_confidentiality_label(nmbs_confidentiality_label* label) noexcept
{
    try
    {
        std::free(const_cast<char*>(label->policy_identifier));
        label->policy_identifier = nullptr;
        std::free(const_cast<char*>(label->classification));
        label->classification = nullptr;
    }
    catch (...)
    {
        std::cerr << "C++ Exception caught in during nmbs_free. High chance of memory leaks!" << std::endl;
    }
}

void nmbs_free_confidentiality_labels(nmbs_confidentiality_labels* labels) noexcept
{
    try
    {
        for (int i = 0; i < labels->size; ++i)
        {
            nmbs_free_confidentiality_label(&labels->label[i]);
        }
        std::free(labels->label);
        labels->label = nullptr;
        labels->size = 0;
    }
    catch (...)
    {
        std::cerr << "C++ Exception caught in during nmbs_free. High chance of memory leaks!" << std::endl;
    }
}

