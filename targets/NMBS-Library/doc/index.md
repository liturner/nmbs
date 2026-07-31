# Getting Started

This documentation is installed locally under /usr/share/doc/libnmbs-dev/html/index.html. You can open this in a web
browser directly, or utilise a package such as _dochelp_ to browse for it.

The library contains the root namespace ```nmbs``` in C++. The API is primarily based
around [functions](namespacemembers_func.html), minimising the use of data structures to simple structs for holding
data. The structs themselves have very little, if any, functionality.

# Examples

Once you have installed the development files (e.g. _libnmbs-dev_ on Debian), you will be able to integrate libnmbs1
into your project as follows:

```cmake
find_package(NMBS REQUIRED CONFIG)

target_link_libraries(Your-Target
        PRIVATE
        NMBS::NMBS-Library
)
```

Ensure that the core header is included in your code.

```cpp
#include <nmbs/nmbs.h>
```

The following is a minimal example for writing and reading the XMP metadata on an image. Note that the error handling
for the library is using nmbs::Expected, which is simply a std::Expected<T, nmbs::Error> typedef. The majority of errors
will be reported in this manner. The nmbs::Error contains a human-readable message, and a machine-readable code.

Further examples can be found in the targets/NMBS-Examples folder of the source code.

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
