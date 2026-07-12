/// @file nmbs-verify.cpp
/// @brief
///
/// @author Luke Ian Turner
/// @date 2026-06-07
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


#include <nmbs/nmbs.h>
#include <argparse/argparse.hpp>
#include <iostream>
#include <filesystem>

int main(const int argc, char* argv[]) {

    // Argument Parsing. Note, there is quite a lot of functionality needed long term. Make sure the API
    // can get complicated. Use arguments like "-f" for a file, and not positional args
    argparse::ArgumentParser program("nmbs-verify", std::string(nmbs::version()));
    program.add_description("Gets the classification tag on compatible file types following the NATO ADatP-4774, ADatP-4778 and ADatP-5636 standards.");
    program.add_argument("-f", "--file").help("The file to retrieve the classification labels from").required().nargs(1);
    program.add_argument("-r", "--raw").help("Print the raw XML binding. This will be output as a single line and is intended to be ingested by other applications").flag();

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return nmbs::ExitCode::invalid_arguments;
    }

    // Argument Validation
    const std::filesystem::path file = program.get<std::string>("-f");
    if (!(std::filesystem::exists(file) && std::filesystem::is_regular_file(file))) {
        std::cerr << "file not found" << std::endl;
        return nmbs::ExitCode::file_not_found;
    }

    // Program Logic
    try
    {
        if (program["--raw"] == true) {
            if (const auto raw_xml = nmbs::read_binding_xml(file); raw_xml.has_value())
            {
                std::cout << raw_xml.value() << std::endl;
                return nmbs::ExitCode::success;
            }
            std::cerr << "no label was present on the provided file" << std::endl;
            return nmbs::ExitCode::no_label_present;
        }
        if (const auto labels = nmbs::read_labels(file); labels.has_value())
        {
            for (const auto& label : labels.value())
            {
                std::cout << label.confidentiality_information.policy_identifier << " " << label.confidentiality_information.classification << std::endl;
                return nmbs::ExitCode::success;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "std::exception: " << e.what() << std::endl;
        return nmbs::ExitCode::unknown_error;
    }
}