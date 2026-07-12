/// @file nmbs-set.cpp
/// @brief Basic example of using the libnmbs API
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

    // Argument Parsing
    argparse::ArgumentParser program("nmbs-set", std::string(nmbs::version()));
    program.add_description("Sets the classification tag on compatible file types following the NATO ADatP-4774, ADatP-4778 and ADatP-5636 standards.");
    program.add_argument("-f", "--file").help("The file to apply the classification label to").required().nargs(1);
    program.add_argument("-v", "--verbose").help("Print the label written to the file on stdout").flag();
    program.add_argument("-p", "--policy").help("The policy identifier (e.g. NATO, ITAR)").required().nargs(1);
    program.add_argument("-c", "--classification").help(R"(The policy classification (e.g. UNCLASSIFIED, RESTRICTED, CONFIDENTIAL, SECRET, "TOP SECRET" (not the need for parenthesis with spaces!))").required().nargs(1);

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return nmbs::ExitCode::invalid_arguments;
    }

    // Argument Validation
    nmbs::ConfidentialityLabel label;
    const std::filesystem::path file = program.get<std::string>("--file");
    label.confidentiality_information.policy_identifier = program.get<std::string>("--policy");
    label.confidentiality_information.classification = program.get<std::string>("--classification");

    if (!(std::filesystem::exists(file) && std::filesystem::is_regular_file(file))) {
        std::cerr << "file not found" << std::endl;
        return nmbs::ExitCode::file_not_found;
    }

    // Program Logic
    try
    {
        std::vector<nmbs::ConfidentialityLabel> labels;
        labels.push_back(label);
        auto output = nmbs::write_labels(file,  labels);
        if (output.has_value())
        {
            if (program["--verbose"] == true) {
                std::cout << "  Key: Xmp.mbxmp.bindingInformation" << std::endl
                << "Value: " << output.value() << std::endl;
            }
            return nmbs::ExitCode::success;
        }
        std::cerr << output.error().message() << std::endl;
        return output.error().code();

    }
    catch (const std::exception& e)
    {
        std::cerr << "std::exception: " << e.what() << std::endl;
        return nmbs::ExitCode::unknown_error;
    }

    return nmbs::ExitCode::success;
}