/// @file nmbs/exit_code.h
/// @brief Standardized integer exit codes for the nmbs application and library.
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

namespace nmbs
{
    /// @brief Standard exit codes produced by nmbs tools.
    /// @details Suitable for use as executable return values or library error indicators.
    /// @since 1.0.0
    enum ExitCode {

        /// @brief No errors occurred; operation completed successfully.
        /// @since 1.0.0
        success = 0,

        /// @brief One or more provided arguments were invalid.
        /// @since 1.0.0
        invalid_arguments = 1,

        /// @brief The specified file could not be found.
        /// @since 1.0.0
        file_not_found = 10,

        /// @brief No XMP packet was attached to the file.
        /// @since 1.0.0
        xmp_not_found = 11,

        /// @brief The file contained XMP, but the desired key was missing.
        /// @since 1.0.0
        xmp_key_not_found = 12,

        /// @brief The XML parser was unable to read the provided XML.
        /// @since 1.0.0
        xml_could_not_parse = 13,

        /// @brief The XML parser was unable to create an XPath context.
        /// @since 1.0.0
        xml_could_not_create_xpath_context = 14,

        /// @brief No label was attached to the file.
        /// @since 1.0.0
        no_label_present = 15,

        /// @brief No binding profile is available for the selected file type.
        /// @since 1.0.0
        no_binding_support = 16,

        /// @brief An unspecified or unknown error occurred.
        /// @since 1.0.0
        unknown_error = 99
    };
}
