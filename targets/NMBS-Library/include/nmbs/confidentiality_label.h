/// @file confidentiality_label.h
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
    ///
    /// @brief <s4774::ConfidentialityInformation>
    struct confidentiality_information
    {
        ///
        /// @brief <s4774::PolicyIdentifier>
        std::string policy_identifier;

        ///
        /// @brief <s4774::Classification>
        std::string classification;
    };

    ///
    /// @brief ABC for confidentiality labels
    /// @see nmbs::originator_confidentiality_label
    struct confidentiality_label
    {
        enum confidentiality_label_type
        {
            originator,
            alternative,
            successor
        };

        ///
        /// @brief <s4774::ConfidentialityInformation>
        confidentiality_information information;
        virtual confidentiality_label_type label_type() = 0;
        virtual ~confidentiality_label() = default;
    };

    ///
    /// @brief <s4774::originatorConfidentialityLabel>
    struct originator_confidentiality_label : confidentiality_label
    {
        ///
        /// @brief <s4774::CreationDateTime>
        std::chrono::time_point<std::chrono::utc_clock, std::chrono::seconds> creation_date_time;
        confidentiality_label_type label_type() override {return originator;};
    };

}
