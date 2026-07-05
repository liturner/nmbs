/// @file expected.h
/// @brief expected.h brief
/// @details expected.h details
///
/// @author luke
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

    /// @brief A simple error container to use with nmbs::expected for communicating domain issues to function callers.
    /// @details Intended to be small and lightweight. A nmbs::exit_code is provided to better enable logic to be built
    /// on top of specific errors. Static factory functions are provided to support in generating errors. e.g.
    ///
    /// - auto failure_error = nmbs::error::file_not_found();
    ///
    /// The constructors are private, and the produced instances are immutable with only const accessors being provided.
    /// Copy constructors, including move support are provided.
    ///
    /// @see nmbs::error::message
    /// @see nmbs::error::code
    class error
    {
        exit_code code_;
        std::string message_;

    private:
        error(const exit_code code, std::string message) : code_(code), message_(std::move(message))
        {
        }

    public:
        error() = delete;
        error(error&&) noexcept = default;
        error& operator=(error&&) noexcept = default;
        error(const error&) = default;
        error& operator=(const error&) = default;

        [[nodiscard]] exit_code code() const { return code_; }
        [[nodiscard]] const std::string& message() const { return message_; }

        static error unexpected(
            std::string message = "An unexpected error occurred")
        {
            return {exit_code::unknown_error, std::move(message)};
        }

        static error file_not_found(
            std::string message = "Requested resource could not be found")
        {
            return {exit_code::file_not_found, std::move(message)};
        }

        static error xmp_not_found(
            std::string message = "Requested resource did not contain any XMP data (at all)")
        {
            return {exit_code::xmp_not_found, std::move(message)};
        }

        static error xmp_key_not_found(
            std::string message = "Requested resource did not contain the desired XMP key")
        {
            return {exit_code::xmp_key_not_found, std::move(message)};
        }

        static error xml_could_not_parse(
            std::string message = "Requested XML could not be read")
        {
            return {exit_code::xml_could_not_parse, std::move(message)};
        }

        static error xml_could_not_create_xpath_context(
            std::string message = "Requested XML could not be read")
        {
            return {exit_code::xml_could_not_create_xpath_context, std::move(message)};
        }
    };

    /// @brief Convenience typedef to standardise usage of nmbs::error in all std::expected usages.
    ///
    template <typename T>
    using expected = std::expected<T, error>;
}
