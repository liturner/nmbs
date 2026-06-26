/// @file nmbs.h
/// @brief C API for certain aspects of the libnmbs
/// @details These are primarily written to support in GLib like integrations, such as
/// the Nautilus extension system. It is not intended to cover all aspect of
/// the C++ API, rather it will be minimally expanded as needed. It is assumed
/// that the primary users of the libnmbs will be using C++.
///
/// @author Luke Ian Turner
/// @date 2026-06-22
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

/// @defgroup c_api C Language API
/// @brief The C interface to libnmbs.
///
/// This API does not "wrap" the underlying C++ API, rather it aims to provide a
/// clean C Style API with a slightly reduced scope to the full C++ API. It has
/// been written to enable the Nautilus extension in GNOME, and will be extended
/// as needed.
///
/// *Principles*
///
/// * You create it, you delete it. Us the new and delete functions provided for the structs. Fill and manipulate with the support functions.
/// * Naming Scheme = [NAMESPACE]_[STRUCT|global]_[FUNCTION]

/// @defgroup c_confidentiality_labels Confidentiality Labels
/// @ingroup c_api
/// @brief Functions for working with ADatP-4774 labels.

/// @defgroup c_spif Security Policies
/// @ingroup c_api
/// @brief Functions for working with SPIF files and Security Policies.

#ifdef __cplusplus
# define NMBS_NOEXCEPT noexcept
#else
# define NMBS_NOEXCEPT
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/// @brief C struct representation of nmbs::confidentiality_label.
/// @details It is not intended that you create these yourself. Use the functions provided
/// for nmbs_confidentiality_labels.
/// @ingroup c_api
/// @see nmbs_confidentiality_labels
typedef struct {
    ///
    /// e.g. NATO, PUBLIC etc...
    char* policy_identifier;

    ///
    /// e.g. UNMARKED, UNCLASSIFIED, SECRET etc.
    char* classification;
} nmbs_confidentiality_label;

/// @brief C struct for holding lists of nmbs_confidentiality_label.
/// @details One of the most important structures in the C API. This is the item for which the
/// majority of the API functions will be provided. Most importantly, create instances using
/// nmbs_confidentiality_labels_new, and clean them up using nmbs_confidentiality_labels_delete.
/// Additional support functions are provided for accessing or manipulating functions.
/// @ingroup c_confidentiality_labels
/// @see nmbs_confidentiality_labels_new
/// @see nmbs_confidentiality_labels_delete
/// @see nmbs_confidentiality_labels_read_labels
typedef struct {
    int size;
    nmbs_confidentiality_label* label;
} nmbs_confidentiality_labels;

/// @brief Creates and returns an instance of nmbs_confidentiality_labels.
/// @ingroup c_confidentiality_labels
/// @return Pointer to a "new" nmbs_confidentiality_labels
/// @see nmbs_confidentiality_labels_delete
[[nodiscard]] nmbs_confidentiality_labels* nmbs_confidentiality_labels_new() NMBS_NOEXCEPT;

/// @brief "delete"s an instance of nmbs_confidentiality_labels.
/// @ingroup c_confidentiality_labels
/// @see nmbs_confidentiality_labels_new
void nmbs_confidentiality_labels_delete(nmbs_confidentiality_labels* labels) NMBS_NOEXCEPT;

/// @brief Reads the nmbs_confidentiality_labels from a file, regardless of binding profile.
/// @ingroup c_confidentiality_labels
/// @param labels_out A pointer to your buffer which we will fill.
/// @param file Path to the file to read labels from.
/// @see nmbs_confidentiality_labels_new
void nmbs_confidentiality_labels_read_labels(nmbs_confidentiality_labels* labels_out, const char* file) NMBS_NOEXCEPT;

/// @brief Writes ADatP-4774 labels to a file, using the most appropriate method.
/// @details Any existing labels will be overwritten. If an "append" functionality
/// is desired, please call nmbs_read_labels first, and extend the list.
/// @ingroup c_confidentiality_labels
/// @param file to write labels to
/// @param labels to write to the file. The caller owns the memory
/// @return nmbs::exit_code
[[nodiscard]] int nmbs_confidentiality_labels_write_labels(const char* file, const nmbs_confidentiality_labels* labels) NMBS_NOEXCEPT;

/// @brief C struct for holding security classification (e.g. UNCLASSIFIED).
/// @details Use the API for nmbs_security_policies.
/// @ingroup c_api
/// @see nmbs_security_policies
typedef struct nmbs_security_classification
{
    char* name;
} nmbs_security_classification;

/// @brief C struct for holding a security policy (e.g. NATO).
/// @details Use the API for nmbs_security_policies.
/// @ingroup c_api
/// @see nmbs_security_policies
typedef struct nmbs_security_policy
{
    char* name;
    unsigned long classification_count;
    nmbs_security_classification* security_classifications;
} nmbs_security_policy;


/// @brief C struct for holding a list of nmbs_security_policy.
/// @details One of the most important structures in the C API. This is the item for which the
/// majority of the API functions will be provided. Most importantly, create instances using
/// nmbs_security_policies_new, and clean them up using nmbs_security_policies_delete.
/// Additional support functions are provided for accessing or manipulating functions.
/// @ingroup c_spif
/// @see nmbs_security_policies_new
/// @see nmbs_security_policies_delete
/// @see nmbs_security_policies_read_installed
typedef struct nmbs_security_policies
{
    unsigned long size;
    nmbs_security_policy* policy;
} nmbs_security_policies;

/// @brief Creates and returns an instance of nmbs_security_policies.
/// @ingroup c_spif
/// @return Pointer to a "new" nmbs_security_policies
[[nodiscard]] nmbs_security_policies* nmbs_security_policies_new() NMBS_NOEXCEPT;

/// @brief "delete"s an instance of nmbs_security_policies_delete.
/// @ingroup c_spif
void nmbs_security_policies_delete(nmbs_security_policies* policies) NMBS_NOEXCEPT;

/// @brief Reads the nmbs_security_policies which are installed on the system.
/// @details The C++ API contains a few constants detailing where the lib will look
/// for installed SPIF files.
/// @ingroup c_spif
/// @see nmbs::spif::packaged_spif_location
/// @see nmbs::spif::administered_spif_location
/// @see nmbs::spif::override_spif_location_env_var
void nmbs_security_policies_read_installed(nmbs_security_policies* policies_out) NMBS_NOEXCEPT;

/// @brief C Flags detailing various binding support for specific files.
/// @ingroup c_api
/// @see ::nmbs_binding_flags_read_support
typedef enum nmbs_binding_flags : uint32_t {
    ///
    /// The file does not support ADatP-4774 labels (at least in this implementation...)
    nmbs_binding_none              = 0,

    ///
    /// The file supports the XMP binding profile, and is writeable
    nmbs_binding_supports_xmp      = 1 << 0,

    ///
    /// The file has an XMP binding, and its readable
    nmbs_binding_has_xmp           = 1 << 1,

    ///
    /// The file supports the Sidecar binding profile, and is writeable
    nmbs_binding_supports_sidecar  = 1 << 2,

    ///
    /// The file has a Sidecar binding, and its readable
    nmbs_binding_has_sidecar       = 1 << 3,

    ///
    /// The file supports an embedded binding, and no writeable sidecar file is present
    nmbs_binding_recommend_xmp     = 1 << 4,

    ///
    /// The file either does not support an embedded binding, or a writeable sidecar file is present
    nmbs_binding_recommend_sidecar = 1 << 5
} nmbs_binding_flags;

/// Provides flags indicating the binding methods supported or used on the path.
/// The method does its best to be fast, nonetheless the result should ideally
/// be cached, as it queries numerous IO APIs to ascertain what is supported.
/// @ingroup c_api
/// @param file to investigate
/// @return ::nmbs_binding_flags
[[nodiscard]] uint32_t nmbs_binding_flags_read_support(const char* file) NMBS_NOEXCEPT;

#ifdef __cplusplus
}
#endif
