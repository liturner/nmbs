//
// Created by luke on 6/7/26.
//
#include <nmbs/nmbs.h>
#include <argparse/argparse.hpp>
#include <iostream>

int main(const int argc, char* argv[]) {

    // Argument Parsing
    argparse::ArgumentParser program("nmbs-xmp", nmbs::version());
    program.add_description("sets the classification tag on XMP compatible file types following the NATO ADatP-4774, ADatP-4778 and ADatP-5636 standards. This is a minimal tagging tool, and is only intended to aid in simple tagging. Further refinement, such as the addition of exemptions or markings is outside the scope of this tool. The use case of this tool is rather to lower the cost of tagging uninteresting files in complex systems (e.g. this tool may be used by software to tag software icons as UNCLASSIFIED, rather than paying thousands for full tagging tools...)");
    program.add_argument("file").help("the file to apply the classification label to");
    program.add_argument("policy").help("the policy identifier (e.g. NATO, ITAR)");
    program.add_argument("classification").help(R"(the policy classification (e.g. UNCLASSIFIED, RESTRICTED, CONFIDENTIAL, SECRET, "TOP SECRET" (not the need for parenthesis with spaces!))");
    program.add_argument("-a", "--additive").help("add the classification to the existing label instead of overwriting it").flag();

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    // Argument Validation
    auto file = program.get<std::string>("file");
    auto policy = program.get<std::string>("policy");
    auto classification = program.get<std::string>("classification");

    // Program Logic
    const std::string confidentialityLabel = nmbs::confidentiality_label(policy, classification);
    const std::string bindingInformation = nmbs::binding_information(confidentialityLabel);
    nmbs::write_xmp(file, bindingInformation);

    return 0;
}