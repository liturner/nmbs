---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
title: Home
---
<div style="background-color: #fff3cd; color: #856404; border: 1px solid #ffeeba; padding: 12px; text-align: center; border-radius: 4px; margin-bottom: 25px; font-weight: 500;">
  ⚠️ <strong>Work in Progress:</strong> This project and documentation are currently under active development.
</div>


**nmbs** is a lightweight, minimal implementation of NATO security labeling and metadata binding standards. It provides parsing, validation, and encoding utilities to enable a free alternative to applying confidentiality metadata to files, without the need for heavy and expensive Data Loss Protection (DLP) suites.

**nmbs** has two primary use cases:

1. On desktop machines within controlled networks to enable end users to label files. In combination with enterprise DLP at the network edge, the network can scale without the need for per-machine licenses, just to label files.

2. Embeded in other applications, allowing software developers to tag files when they are written, or read labels when opening files and correctly display marking data.

&nbsp;

---

## Key Features

* **Embedded Labels:** Such as NATO UNCLASSIFIED, or COMPANYX RED.
* **Its Fast:** High-performance C/C++ metadata parsing and construction.
* **Standard Compliant:** Strict adherence to NATO specifications.
* **Packaging Friendly:** Built for easy integration into Linux environments and Debian packaging workflows.
* **GNOME Integration:** Seamlessly integrated into GNOME Files.
* **Headless Support:** Operation on servers with no GUI via a CLI.
* **Multi Language:** English, French and German internationalisation.

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

## Protocol Implementation Conformance Statement (PICS)

| Standard | Feature / Module | Support Level |
| :--- | :--- | :---: |
| **STANAG 4774** | Security Policy Information File | **Read** |
| | Confidentiality Label | **Read/Write** |
| | Confidentiality Celarance | - |
| | Access Control Framework | - |
| | Label Catalogs | - |
| **STANAG 4778** | urn:nato:stanag:4778:profile:cryptoartefact:1:2 | - |
| | urn:nato:stanag:4778:profile:smtp:1:2 | - |
| | urn:nato:stanag:4778:profile:xmpp:1:3 | - |
| | urn:nato:stanag:4778:profile:ooxml:1:2 | - |
| | urn:nato:stanag:4778:profile:soap:1:1 | - |
| | urn:nato:stanag:4778:profile:rest:1:2 | **Read/Write** |
| | urn:nato:stanag:4778:profile:gopc:1:2 | - |
| | urn:nato:stanag:4778:profile:sidecar:1:2 | **Read/Write** |
| | urn:nato:stanag:4778:profile:xmp:1:1 | **Read/Write** |
| | urn:nato:stanag:4778:profile:wsmp:1:1 | - |
| | urn:nato:stanag:4778:profile:xml:schema:1:0 | **Read** |


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

