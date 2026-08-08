/// @file nmbs/nmbs.h
/// @brief Main include header for the libnmbs library.
/// @details Provides a single import for the entire nmbs namespace.
///
/// @author Luke Ian Turner
/// @date 2026-06-06
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

#include <string>
#include <filesystem>

#include "binding.h"
#include "confidentiality_label.h"
#include "binding_information.h"
#include "expected.h"

/// @brief Lightweight utilities for NATO confidentiality metadata.
/// @details Implements core components of ADatP-4774, ADatP-4778, and STANAG 5636.
/// Provides a dependency-free toolkit to attach standards-compliant labels to low-sensitivity artifacts.
/// @since 1.0.0
namespace nmbs
{
    /// @brief Retrieves the semantic version of the library.
    /// @details Returns the version in `MAJOR.MINOR.PATCH` format, matching the build configuration.
    /// Pre-release suffixes are not appended.
    /// @return The semantic version string.
    /// @since 1.0.0
    [[nodiscard]] std::string_view version() noexcept;

    /// @brief Releases globally allocated memory and resets library state.
    /// @details Safe to call at any time to assist memory profilers (e.g., Valgrind).
    /// Subsequent library calls may incur performance penalties as caches are rebuilt.
    /// @since 1.0.0
    void cleanup();

    /// @brief Writes ADatP-4778 binding information using the optimal binding profile.
    /// @details Embedded profiles take precedence over sidecar profiles. Existing binding data will be overwritten.
    /// @param path Path to the target file.
    /// @param confidentiality_labels Collection of labels to apply.
    /// @param binding_support Optional pre-calculated binding profile capabilities.
    /// @return The written XML string on success, or an nmbs::Error on failure.
    /// @see nmbs::binding::support
    /// @since 1.0.0
    [[nodiscard]] Expected<std::string> write_labels(
        const std::filesystem::path& path,
        const std::vector<ConfidentialityLabel>& confidentiality_labels,
        std::optional<binding::ProfileSupport> binding_support = std::nullopt);

    /// @brief Reads and deserializes the ADatP-4778 binding from the specified file.
    /// @details If multiple bindings exist, precedence is undefined and only one is returned.
    /// @param path Path to the target file.
    /// @param binding_support Optional pre-calculated binding profile capabilities.
    /// @return The parsed BindingInformation, std::nullopt if none exists, or an error.
    /// @see nmbs::binding::support
    /// @since 1.0.0
    [[nodiscard]] Expected<std::optional<binding::BindingInformation>> read_binding(
        const std::filesystem::path& path,
        std::optional<binding::ProfileSupport> binding_support = std::nullopt);

    /// @brief Reads the raw XML of the ADatP-4778 binding from the specified file.
    /// @param path Path to the target file.
    /// @param binding_support Optional pre-calculated binding profile capabilities.
    /// @return The raw XML string, std::nullopt if none exists, or an error.
    /// @see nmbs::binding::support
    /// @since 1.0.0
    [[nodiscard]] Expected<std::optional<std::string>> read_binding_xml(
        const std::filesystem::path& path,
        std::optional<binding::ProfileSupport> binding_support = std::nullopt);

    /// @brief Removes the ADatP-4778 binding from the specified file.
    /// @param path Path to the target file.
    /// @param binding_support Optional pre-calculated binding profile capabilities.
    /// @return Void on success, or an error on failure.
    /// @see nmbs::binding::support
    /// @since 1.0.0
    Expected<void> remove_binding(
        const std::filesystem::path& path,
        std::optional<binding::ProfileSupport> binding_support = std::nullopt);
}
