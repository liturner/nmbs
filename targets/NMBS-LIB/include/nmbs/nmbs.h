//
// Created by luke on 6/6/26.
//

#ifndef TT_NMBS_NMBS_H
#define TT_NMBS_NMBS_H

#include <string>
#include <filesystem>

namespace nmbs
{
    /// The XML namespace urn as defined by ADatP-4774 Ed.A V.1.
    inline constexpr std::string_view s4774namespace("urn:nato:stanag:4774:confidentialitymetadatalabel:1:0");

    /// The XML prefix to be used for s4774namespace. Note, that this is defined in the ADatP-5636 Ed.A V.1 standard.
    /// There is potentially a second alias in use within other software, namely "slab". This is incorrect. "slab" was
    /// used in the ADatP-4774 Ed.A V.1 examples and xsd, but ADatP-5636 provides the normative definition. It is to be
    /// expected that the next releases of ADatP-4774 will update the prefix in future releases.
    ///
    /// Technically speaking, this should be irrelevant as software *should* be using the namespaces for identification,
    /// and not the prefixes. This is however often not the case.
    inline constexpr std::string_view s4774prefix("s4774");

    /// The XML namespace urn as defined by ADatP-4778 Ed.A V.1.
    inline constexpr std::string_view s4778namespace("urn:nato:stanag:4778:bindinginformation:1:0");


    inline constexpr std::string_view s4778prefix("s4778");

    inline constexpr std::string_view s4778xmpNamespace("urn:nato:stanag:4778:bindinginformation:1:0:xmp#");

    /// The XML namespace for the XMP packet as defined in ADatP-4778.2 Ed.A V.1. It should be noted that this namespace
    /// prefix only appears in examples, and is neither in ADatP-4778, nor ADatP-5636 normatively referenced.
    ///
    /// The final key for the XMP property will then be
    /// "Xmp.[s4778xmpPrefix].[s4778key]". It is however *critical* to note that the value of s4778xmpPrefix is only
    /// for human readability. Programs trying to access the value must use the s4778xmpNamespace to first identify the
    /// prefix or prefixes used (yes, there can be multiple!).
    inline constexpr std::string_view s4778xmpPrefix("mbxmp");

    /// The key value as to be used in an XMP property. The final key for the XMP property will then be
    /// "Xmp.[s4778xmpPrefix].[s4778key]". It is however *critical* to note that the value of s4778xmpPrefix is only
    /// for human readability. Programs trying to access the value must use the s4778xmpNamespace to first identify the
    /// prefix or prefixes used (yes, there can be multiple!).
    inline constexpr std::string_view s4778key("bindingInformation");

    std::string confidentiality_label(std::string_view policyIdentifier, std::string_view classification);

    /// Wraps the provided confidentialityLabel in a BindingInformation element. This implementation assumes that the
    /// resulting BindingInformation will be embedded in another data object. As such, there are no xml version tags,
    /// and the DataReference is set to an empty string.
    /// @param confidentialityLabel the XML confidentiality label to be used in the binding.
    /// @return an XML string whose root element is a BindingInformation element.
    std::string binding_information(std::string_view confidentialityLabel);

    int write_xmp(const std::filesystem::path& path, std::string_view payload);
}

#endif //TT_NMBS_NMBS_H
