/// @file nmbs/binding_information.h
/// @brief Object representation of the ADatP-4778 BindingInformation element
///
/// @author Luke Ian Turner
/// @date 2026-08-01
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

#include <optional>
#include <string>
#include <vector>

#include "confidentiality_label.h"

namespace nmbs::binding
{
    /// @brief Holds information about both the labels, and the file the labels are bound to.
    /// @details The type representing the XML <s4778:%BindingInformation> element.
    /// This is not a pure representation, the deserialization will also
    /// store some internal metadata. It is the outermost data structure in nmbs.
    /// @since 1.0.0
    struct BindingInformation
    {
        /// @brief Holder for nmbs internal metadata.
        /// @details This data is not part of the ADatP-4778 standard.
        /// @since 1.0.0
        struct InternalMetadata
        {
            /// @brief The identified binding profile, populated during reading.
            /// @since 1.0.0
            std::optional<std::string> binding_profile;
        };

        /// @brief Holds a reference to the file to which the accompanying labels reference.
        /// @details The type representing the XML <s4778:DataReference> element.
        /// @since 1.0.0
        struct DataReference
        {
            /// @brief The URI identifying the target data file.
            /// @since 1.0.0
            std::string uri;

            /// @brief The optional type of the uri.
            /// @since 1.0.0
            std::optional<std::string> content_type;
        };

        /// @brief The collection of confidentiality labels bound to the referenced data.
        /// @since 1.0.0
        std::vector<ConfidentialityLabel> labels;

        /// @brief The reference to the data file being labeled.
        /// @since 1.0.0
        DataReference reference;

        /// @brief Internal library tracking data.
        /// @since 1.0.0
        InternalMetadata internal_metadata;
    };
}
