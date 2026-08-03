---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
title: Home
---
<div style="background-color: #fff3cd; color: #856404; border: 1px solid #ffeeba; padding: 12px; text-align: center; border-radius: 4px; margin-bottom: 25px; font-weight: 500;">
  ⚠️ <strong>Work in Progress:</strong> This project and documentation are currently under active development.
</div>


**nmbs** is a lightweight, native C++ implementation of NATO security labeling and metadata binding standards. It provides automated parsing, validation, and encoding utilities for integrating standardised confidentiality metadata into modern data pipelines.

&nbsp;

---

## Key Features

* **C++ Engine:** High-performance metadata parsing and construction.
* **Standard Compliant:** Strict adherence to NATO specifications.
* **Packaging Friendly:** Built for easy integration into Linux environments and Debian packaging workflows.

&nbsp;

---

## GNOME Files Integration

![nmbs Nautilus Integration Example]({{ '/assets/images/example-column.png' | relative_url }})


---

## CLI

```shell
nmbs-get
nmbs-set
nmbs-verify
```

&nbsp;

---

## Supported NATO Standards

nmbs implements specifications published by NATO:

* **[STANAG 4774 Ed.A V.1](https://nso.nato.int/nso/nsdd/main/standards/ap-details/1967/EN)** — *CONFIDENTIALITY METADATA LABEL SYNTAX*
  Defines the structure and XML schema used to express confidentiality labels attached to data objects.
* **[STANAG 4778 Ed.A V.1](https://nso.nato.int/nso/nsdd/main/standards/ap-details/1968/EN)** — *METADATA BINDING MECHANISM*
  Defines the methods for securely encapsulating and binding metadata (such as 4774 labels) to data payloads.

&nbsp;

---

## Standard Implementation Completeness

| Standard | Feature / Module | Support Level |
| :--- | :--- | :---: |
| **STANAG 4774** | Confidentiality Label Structure & Schema | **x%** |
| **STANAG 4774** | XML Serialization & Parsing | **x%** |
| **STANAG 4778** | Metadata Binding Container Syntax | **x%** |
| **STANAG 4778** | Cryptographic Binding / Signature Verification | **Not Supported** |

&nbsp;

---

## Quick Code Example

```cpp
#include <nmbs/nmbs.h>

int main()
{
    const std::filesystem::path file{"my-image.jpg"};

    std::vector<nmbs::ConfidentialityLabel> labels(1);
    labels[0].confidentiality_information.policy_identifier = "PUBLIC";
    labels[0].confidentiality_information.classification = "UNMARKED";

    nmbs::write_labels(file, labels);
    
    return 0;
}

```

