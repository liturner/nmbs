/// @file example1.cpp
/// @brief Minimal example of using the NMBS-Library to write and read from an image.
///
/// @author Luke Ian Turner
/// @date 2026-08-02
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
#include <nmbs/nmbs.h>

int main()
{
    const std::filesystem::path file{"my-image.jpg"};

    std::vector<nmbs::ConfidentialityLabel> labels(1);
    labels[0].confidentiality_information.policy_identifier = "PUBLIC";
    labels[0].confidentiality_information.classification = "UNMARKED";

    if (const auto output = nmbs::write_labels(file, labels); !output.has_value())
    {
        std::cerr << output.error().message() << std::endl;
        return output.error().code();
    }

    if (const auto result = nmbs::read_binding(file); result && *result)
    {
        for (const nmbs::binding::BindingInformation& binding = **result; const auto& label : binding.labels)
        {
            std::cout << label.confidentiality_information.policy_identifier << " " <<
                label.confidentiality_information.classification << std::endl;
        }
        return nmbs::ExitCode::success;
    }
    else if (!result)
    {
        std::cerr << result.error().message() << std::endl;
        return result.error().code();
    }
    return nmbs::ExitCode::no_label_present;
}
