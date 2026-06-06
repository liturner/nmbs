//
// Created by luke on 6/6/26.
//
#include <nmbs/nmbs.h>

#include <chrono>

namespace nmbs
{
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

    std::string canonicalize(const std::string& text)
    {
        std::string out;
        out.reserve(text.size() * 2); // avoids repeated reallocations

        for (char c : text) {
            switch (c) {
            case '<':  out += "&lt;";  break;
            case '>':  out += "&gt;";  break;
            case '&':  out += "&amp;"; break;
            case '"':  out += "&quot;"; break;
            case '\'': out += "&apos;"; break;
            default:   out += c; break;
            }
        }

        return out;
    }
}