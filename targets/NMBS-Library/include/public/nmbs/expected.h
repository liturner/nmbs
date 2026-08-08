/// @file nmbs/expected.h
/// @brief Standard error handling types for the nmbs library.
/// @details Defines the immutable nmbs::Error container and the nmbs::Expected
/// alias, standardizing function return types via std::expected.
///
/// @author Luke Ian Turner
/// @date 2026-07-04
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

#include <expected>
#include <string>
#include <utility>

#include "exit_code.h"

namespace nmbs
{
    /// @brief Lightweight domain error container for use with nmbs::Expected.
    /// @details Provides an nmbs::ExitCode for programmatic error handling.
    /// Instances are immutable and must be created via static factory functions:
    ///
    ///     auto err = nmbs::Error::file_not_found();
    ///
    /// @since 1.0.0
    /// @see nmbs::Error::message
    /// @see nmbs::Error::code
    class Error
    {
        ExitCode code_;
        std::string message_;

    private:
        Error(const ExitCode code, std::string message) : code_(code), message_(std::move(message))
        {
        }

    public:
        /// @brief Default constructor is explicitly deleted.
        /// @since 1.0.0
        Error() = delete;

        /// @brief Default move constructor.
        /// @since 1.0.0
        Error(Error&&) noexcept = default;

        /// @brief Default move assignment operator.
        /// @since 1.0.0
        Error& operator=(Error&&) noexcept = default;

        /// @brief Default copy constructor.
        /// @since 1.0.0
        Error(const Error&) = default;

        /// @brief Default copy assignment operator.
        /// @since 1.0.0
        Error& operator=(const Error&) = default;

        /// @brief Retrieves the underlying error code.
        /// @return The associated nmbs::ExitCode.
        /// @since 1.0.0
        [[nodiscard]] ExitCode code() const { return code_; }

        /// @brief Retrieves the descriptive error message.
        /// @return A const reference to the message string.
        /// @since 1.0.0
        [[nodiscard]] const std::string& message() const { return message_; }

        /// @brief Creates an unknown error.
        /// @param message Optional custom error description.
        /// @since 1.0.0
        static Error unexpected(
            std::string message = "An unexpected error occurred")
        {
            return {ExitCode::unknown_error, std::move(message)};
        }

        /// @brief Creates a file not found error.
        /// @param message Optional custom error description.
        /// @since 1.0.0
        static Error file_not_found(
            std::string message = "Requested resource could not be found")
        {
            return {ExitCode::file_not_found, std::move(message)};
        }

        /// @brief Creates an XMP data missing error.
        /// @param message Optional custom error description.
        /// @since 1.0.0
        static Error xmp_not_found(
            std::string message = "Requested resource did not contain any XMP data (at all)")
        {
            return {ExitCode::xmp_not_found, std::move(message)};
        }

        /// @brief Creates an XMP key missing error.
        /// @param message Optional custom error description.
        /// @since 1.0.0
        static Error xmp_key_not_found(
            std::string message = "Requested resource did not contain the desired XMP key")
        {
            return {ExitCode::xmp_key_not_found, std::move(message)};
        }

        /// @brief Creates an XML parsing error.
        /// @param message Optional custom error description.
        /// @since 1.0.0
        static Error xml_could_not_parse(
            std::string message = "Requested XML could not be read")
        {
            return {ExitCode::xml_could_not_parse, std::move(message)};
        }

        /// @brief Creates an XML XPath context error.
        /// @param message Optional custom error description.
        /// @since 1.0.0
        static Error xml_could_not_create_xpath_context(
            std::string message = "Requested XML could not be read")
        {
            return {ExitCode::xml_could_not_create_xpath_context, std::move(message)};
        }

        /// @brief Creates an unsupported binding error.
        /// @param message Optional custom error description.
        /// @since 1.0.0
        static Error no_binding_support(
            std::string message = "Requested file does not support any supported binding mechanism")
        {
            return {ExitCode::no_binding_support, std::move(message)};
        }
    };

    /// @brief Alias for std::expected standardized with nmbs::Error.
    /// @since 1.0.0
    /// @see nmbs::Error
    template <typename T>
    using Expected = std::expected<T, Error>;
}
