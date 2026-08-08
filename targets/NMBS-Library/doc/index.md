# nmbs (Normalised Metadata Binding Service)

**nmbs** is a lightweight C++ library for generating and parsing NATO confidentiality metadata. It implements core 
components of the ADatP-4774 and ADatP-4778 specifications, enabling developers to consistently attach 
standards-compliant labels to files.

# Getting Started

If installed via Debian packages (e.g., `libnmbs-dev`), this documentation is available locally at 
`/usr/share/doc/libnmbs-dev/html/index.html`. You can open this directly in a web browser or utilize a package such as 
`dochelp`.

The API is rooted in the `nmbs` namespace and is highly functional. Data structures are kept as simple, immutable 
structs with minimal internal logic. Most operations are performed via top-level functions (see the 
[nmbs namespace](namespacenmbs.html) reference).

## Integration

Integrate `libnmbs1` into your CMake project:

```cmake
find_package(NMBS REQUIRED CONFIG)

target_link_libraries(Your-Target
        PRIVATE
        NMBS::NMBS-Library
)
```

Ensure the core header is included in your source files:

```cpp
#include <nmbs/nmbs.h>
```

# Example Usage

The following minimal example demonstrates writing and reading XMP metadata on an image.

Error handling is managed via nmbs::Expected (an alias for std::expected<T, nmbs::Error>), providing both human-readable 
messages and programmatic exit codes. Further examples can be found in the targets/NMBS-Examples directory of the source 
tree.

```cpp
#include <iostream>
#include <nmbs/nmbs.h>

int main()
{
    const std::filesystem::path file{"my-image.jpg"};

    std::vector<nmbs::ConfidentialityLabel> labels(1);
    labels[0].confidentiality_information.policy_identifier = "PUBLIC";
    labels[0].confidentiality_information.classification = "UNMARKED";

    if (const auto output = nmbs::write_labels(file, labels); !output.has_value())
    {
        std::cerr << output.error().message() << std::endl;
        return output.error().code();
    }

    if (const auto result = nmbs::read_binding(file); result && *result)
    {
        for (const nmbs::binding::BindingInformation& binding = **result; const auto& label : binding.labels)
        {
            std::cout << label.confidentiality_information.policy_identifier << " " <<
                label.confidentiality_information.classification << std::endl;
        }
        return nmbs::ExitCode::success;
    }
    else if (!result)
    {
        std::cerr << result.error().message() << std::endl;
        return result.error().code();
    }
    return nmbs::ExitCode::no_label_present;
}
```
