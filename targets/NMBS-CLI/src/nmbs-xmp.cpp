//
// Created by luke on 6/7/26.
//
#include <nmbs/nmbs.h>
#include <iostream>

int main(int argc, char* argv[]) {

    if (argc != 1)
    {
        std::cerr << "This program requires two arguments, some other number was supplied. Please submit a Policy Identifier and a Classification." << std::endl;
        return 1;
    }

    const std::string confidentialityLabel = nmbs::confidentiality_label("TT", "Dummy");
    const std::string bindingInformation = nmbs::binding_information(confidentialityLabel);
    std::cout << bindingInformation;
    nmbs::write_xmp("test.jpg", bindingInformation);

    return 0;
}