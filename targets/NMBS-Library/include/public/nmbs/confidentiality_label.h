/// @file nmbs/confidentiality_label.h
/// @brief Object representation of a Confidentiality Label as per ADatP-4774
///
/// @author Luke Ian Turner
/// @date 2026-06-11
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

#pragma once

#include <chrono>
#include <string>

namespace nmbs
{
    /// @brief Struct representation of the ADatP-4774 "Confidentiality Label"
    /// @details More information can be found on this in section 2.4 of ADatP-4774.1 Ed. A V. 1. The
    /// standard specifies three types of label containing identical data. This struct
    /// represents all three originatorConfidentialityLabel, alternativeConfidentialityLabel and
    /// successorConfidentialityLabel. See nmbs::confidentiality_label::confidentiality_label_type
    /// and the nmbs::confidentiality_label::label_type field.
    ///
    /// Noteworthy is that the label couples "confidentiality information" with a timestamp and
    /// additional metadata such as the user and review dates.
    /// @since 1.0.0
    /// @see nmbs::ConfidentialityLabel::ConfidentialityInformation
    /// @see nmbs::ConfidentialityLabel::ConfidentialityLabelType
    struct ConfidentialityLabel
    {
        /// @brief Identifier for the specialisation of the label.
        /// @details There is no <s4774:ConfidentialityLabel> in the standard, but all specialisations
        /// share the exact same values. The specialisation is used in validation steps with logic for
        /// deciding which classification applies.
        /// @since 1.0.0
        enum ConfidentialityLabelType
        {
            /// @brief <s4774::originatorConfidentialityLabel>
            /// @since 1.0.0
            originator,

            /// @brief <s4774::alternativeConfidentialityLabel>
            /// @since 1.0.0
            alternative,

            /// @brief <s4774::successorConfidentialityLabel>
            /// @since 1.0.0
            successor
        };

        /// @brief A core element of the nmbs::confidentiality_label containing the classification (e.g. PUBLIC UNMARKED)
        /// @details This struct represents <s4774::ConfidentialityInformation>.
        /// @since 1.0.0
        struct ConfidentialityInformation
        {
            /// @brief <s4774::PolicyIdentifier>
            /// @since 1.0.0
            std::string policy_identifier;

            /// @brief <s4774::Classification>
            /// @since 1.0.0
            std::string classification;

            /// @brief <s4774::PrivacyMark>
            /// @since 1.0.0
            std::optional<std::string> privacy_mark;

            /// @brief Default equality operator.
            /// @since 1.0.0
            bool operator==(const ConfidentialityInformation&) const = default;
        };

        /// @brief Identifier for the entity that created or applied the label.
        /// @details Represents <s4774:OriginatorID>. String constants are provided for standard formats.
        /// @since 1.0.0
        struct OriginatorId
        {
            /// @brief RFC 822 (email) address format.
            /// @since 1.0.0
            inline static const std::string rfc822_name = "rfc822Name";

            /// @brief DNS name format.
            /// @since 1.0.0
            inline static const std::string dns_name = "dNSName";

            /// @brief Directory name format.
            /// @since 1.0.0
            inline static const std::string directory_name = "directoryName";

            /// @brief URI format.
            /// @since 1.0.0
            inline static const std::string uniform_resource_identifier = "uniformResourceIdentifier";

            /// @brief IP address format.
            /// @since 1.0.0
            inline static const std::string ip_address = "iPAddress";

            /// @brief X.400 address format.
            /// @since 1.0.0
            inline static const std::string x400_address = "x400Address";

            /// @brief Jabber ID format.
            /// @since 1.0.0
            inline static const std::string jid = "jID";

            /// @brief User Principal Name format.
            /// @since 1.0.0
            inline static const std::string user_principal_name = "userPrincipalName";

            /// @brief The format type of the identifier (e.g., rfc822Name).
            /// @since 1.0.0
            std::string id_type;

            /// @brief The actual identifier value.
            /// @since 1.0.0
            std::string value;

            /// @brief Default equality operator.
            /// @since 1.0.0
            bool operator==(const OriginatorId&) const = default;
        };

        /// @brief Overloaded constructor taking the label type as a parameter.
        /// @details The label type can be changed later. Initializes creation date to the current UTC time.
        /// @param label_type The type of label this instance will represent.
        /// @since 1.0.0
        explicit ConfidentialityLabel(const ConfidentialityLabelType label_type = originator) :
            label_type(label_type),
            creation_date_time(std::chrono::floor<std::chrono::seconds>(std::chrono::utc_clock::now())) {}

        /// @brief Default copy constructor.
        /// @since 1.0.0
        ConfidentialityLabel(const ConfidentialityLabel&) = default;

        /// @brief Default copy assignment operator.
        /// @since 1.0.0
        ConfidentialityLabel& operator=(const ConfidentialityLabel& rhs) = default;

        /// @brief Default equality operator.
        /// @since 1.0.0
        bool operator==(const ConfidentialityLabel&) const = default;

        /// @brief Field to save having to implement type inheritance.
        /// @since 1.0.0
        ConfidentialityLabelType label_type;

        /// @brief <s4774:ConfidentialityInformation>
        /// @since 1.0.0
        ConfidentialityInformation confidentiality_information;

        /// @brief <s4774:OriginatorID>
        /// @since 1.0.0
        std::optional<OriginatorId> originator_id;

        /// @brief <s4774:CreationDateTime>
        /// @since 1.0.0
        std::chrono::time_point<std::chrono::utc_clock, std::chrono::seconds> creation_date_time;
    };

}
