#include <iostream>
#include <string>
#include <chrono>

std::string nmbs_confidentiality_label(const std::string& policyIdentifier, const std::string& classification)
{
    const auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::utc_clock::now());
    const std::string nowString = std::format("{:%FT%TZ}", now);

    std::string xml;
    xml.reserve(700);
    xml.append("<slab:originatorConfidentialityLabel xmlns:slab=\"urn:nato:stanag:4774:confidentialitymetadatalabel:1:0\">");
    xml.append("<slab:ConfidentialityInformation>");
    xml.append("<slab:PolicyIdentifier>");
    xml.append(policyIdentifier);
    xml.append("</slab:PolicyIdentifier>");
    xml.append("<slab:Classification>");
    xml.append(classification);
    xml.append("</slab:Classification>");
    xml.append("</slab:ConfidentialityInformation>");
    xml.append("<slab:CreationDateTime>");
    xml.append(nowString);
    xml.append("</slab:CreationDateTime>");
    xml.append("</slab:originatorConfidentialityLabel>");
    return xml;
}

int main(int argc, char* argv[]) {

    if (argc != 3)
    {
        std::cerr << "This program requires two arguments, some other number was supplied. Please submit a Policy Identifier and a Classification." << std::endl;
        return 1;
    }

    std::cout << nmbs_confidentiality_label(argv[1], argv[2]);
    
    return 0;
}