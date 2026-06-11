# TurnerTech - NATO Metadata Binding Service (tt-nmbs)

This project plans to produce a set of tools for use with NATO Confidentiality Metadata Labels. In particular the first
step aims to provide some basic functionality specifically for XMP metadata in various image formats. The project is
however going to be built in such a way as to allow for expansion.

The project is aimed as a Debian Linux project only. The intention is to produce (at least at first) a set of commands
which can be run directly on a system. This should ensure that there are no IT Security limitations (e.g. sending a TOP
SECRET document to some web service to label it opens increases the security complexity).

A Library containing the core functionality will also be produced, enabling other tools to integrate much of the core
functionality with ease. For example, a GUI tool saving a screenshot can label the file before it even gets saved to
disk.

# Usage

Install the package to your system using apt.

```shell
apt install nmbs
```

The documentation for the CLI and API are packaged with the tool itself.

```shell
# For the CLI, use the supplied man page, or the --help argument
man nmbs-set-xmp
nmbs-set-xmp --help

# Or the API man page for the library
man 3 nmbs
```

# Standards

- ADatP-4774 (Ed.A V.1 12.2017) CONFIDENTIALITY METADATA LABEL SYNTAX
- ADatP-4778 (Ed.A V.1 10.2018) METADATA BINDING MECHANISM
- ADatP-5636 (Ed.A V.1 11.2022) NATO CORE METADATA SPECIFICATION(NCMS)

# Dependencies

Dependencies are kept to a minimum. Particular focus is paid to ensuring Licenses are all very flexible, APT presence of
packages, and trustworthiness. Ideally, this project will be developed on a Debian distro, with simple calls to install
the libs via APT on a Developer Machine, and APT Dependencies in release.

| Name     | Type       | APT             | Description                                                            |
|----------|------------|-----------------|------------------------------------------------------------------------|
| Exiv2    | Product    | libexiv2-dev    | C++ Lib for writing metadata to numerous formats, in particular images |
| argparse | Product    | libargparse-dev | C++17 Headers for parsing CLI options                                  |
|          | Build      | build-essential |                                                                        |
|          | Build      | libgtest-dev    |                                                                        |
|          | Build      | doxygen         |                                                                        |
|          | Build      | ninja-build     |                                                                        |
|          | Build      | help2man        |                                                                        |
|          | Recomended | exiv2           | CLI tools for Exiv2. Usefull for debugging                             |

## External Resources

This project ships with a small number of external resources. Their original sources are as follows.

| File                                       | Source                                                                                     | Description                                                                                                            |
|--------------------------------------------|--------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------|
| nl-cl.xsd                                  | [ADatP-4774.5 EDA V1.zip](https://nso.nato.int/nso/nsdd/main/standards/srd-details/245/EN) | XSD for ConfidentialityLabel                                                                                           |
| nl-mb.xsd                                  | [ADatP-4774.5 EDA V1.zip](https://nso.nato.int/nso/nsdd/main/standards/srd-details/245/EN) | XSD for BindingInformation                                                                                             |
| 20140916_PU_PUBLIC Security Policy-v1.spif | [ADatP-4774.5 EDA V1.zip](https://nso.nato.int/nso/nsdd/main/standards/srd-details/245/EN) | This contains a list of the standard classifications used. It is not normative, but till now is the best I have found. |
| 20210506_PU_NATO Security Policy-v88.spif  | [ADatP-4774.5 EDA V1.zip](https://nso.nato.int/nso/nsdd/main/standards/srd-details/245/EN) | This contains a list of the standard classifications used. It is not normative, but till now is the best I have found. |
