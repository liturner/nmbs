//
// Created by luke on 6/6/26.
//
#include <nmbs/nmbs.h>
#include <nmbs/version.h>

#include <exiv2/exiv2.hpp>
#include <chrono>
#include <iostream>

namespace nmbs
{
    std::string getProjectVersion()
    {
        return projectVersion;
    }

    std::string confidentiality_label(const std::string_view policyIdentifier, const std::string_view classification)
    {
        const auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::utc_clock::now());
        const std::string nowString = std::format("{:%FT%TZ}", now);

        // Leaving this just flexible enough to make it easy to add loops for more complex labels later.
        std::string xml;
        xml.reserve(700);
        xml.append(std::format(R"(<{0}:originatorConfidentialityLabel xmlns:{0}="{1}"><{0}:ConfidentialityInformation><{0}:PolicyIdentifier>{2}</{0}:PolicyIdentifier><{0}:Classification>{3}</{0}:Classification></{0}:ConfidentialityInformation><{0}:CreationDateTime>{4}</{0}:CreationDateTime></{0}:originatorConfidentialityLabel>)", s4774prefix, s4774namespace, policyIdentifier, classification, nowString));

        return xml;
    }

    std::string binding_information(const std::string_view confidentialityLabel)
    {
        return std::format(R"(<{0}:BindingInformation xmlns:{0}="{1}"><{0}:MetadataBindingContainer><{0}:MetadataBinding><{0}:Metadata>{2}</{0}:Metadata><{0}:DataReference URI="" /></{0}:MetadataBinding></{0}:MetadataBindingContainer></{0}:BindingInformation>)", s4778prefix, s4778namespace, confidentialityLabel);
    }

    int write_xmp(const std::filesystem::path& path, const std::string_view payload)
    {
        try
        {
            auto image = Exiv2::ImageFactory::open(path.string());
            if (image.get() == nullptr) return 1;
            image->readMetadata();
            Exiv2::XmpData& xmpData = image->xmpData();
            Exiv2::XmpProperties::registerNs(std::string(s4778xmpNamespace), std::string(s4778xmpPrefix));
            const Exiv2::XmpKey slabKey{std::string(s4778xmpPrefix), std::string(s4778key)};
            const Exiv2::XmpTextValue slabValue{std::string{payload}};
            xmpData.add(slabKey, &slabValue);
            image->writeMetadata();
        }
        catch (const Exiv2::Error& e) {
            std::cerr << "Exiv2 Exception: " << e.what() << "\n";
            return 1;
        }
        catch (const std::exception& e) {
            std::cerr << "Standard Exception: " << e.what() << "\n";
            return 1;
        }

        return 0;
    }
}
