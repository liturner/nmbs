# Normalised Metadata Binding Service (nmbs)

This project provides a set of tools for use with the NATO Confidentiality Metadata Labels as specified in ADatP-4774 
and ADatP-4778.

The project is aimed as a Debian Linux project only. The intention is to produce a set of commands which can be run 
directly on a system. A Library containing the core functionality will also be produced, enabling other tools to 
integrate much of the core functionality with ease. Furthermore, a GNOME Files (Nautilus) extension is provided as the
primary GUI for the functionality.

Please look at the public documentation for end user help. This README is aimed at software engineers.

[https://nmbs.turnertech.de/](https://nmbs.turnertech.de/)

# Versioning Tags

This is primarily aimed at being consumed by a Debian package. As such, the version tags schema used is `uscan` 
friendly. 

Pre-Release: v1.0.0-betaX (`uscan` automatically mangles to 1.0.0~betaX in Debian Tooling)
Release: v1.0.0 (`uscan` automatically mangles to 1.0.0 in Debian Tooling)

# Building

Look at the CI tooling provided for the most accurate build example. If you are doing more than installing some APT
dependencies and running some CMake commands, something is wrong...

- [The GitHub ci](.github/workflows/ci.yml)
- [The docker build](docker/build.dockerfile)

This is a CLion project. The project settings include docker and cpack targets, just using the GUI will work for the 
CMake Targets. Investigate the [.idea](.idea) folder

A `prepare` script is included in the source root to install the build dependencies for this project.

# Testing

CTest is the root of our unit testing. It triggers GTest too. See the [The docker build](docker/build.dockerfile).

## Nautilus Development

It is quite easy to develop for Nautilus. Quite simply, symlink the debug .so to the nautilus extensions folder.
Important to know is that Nautilus runs with a daemon in the background. You must sometimes kill this or the module
will not reload.

Check the run configurations of NMBS-Nautilus to see how to Debug. In CLion this is stored in git, so just debug
the target to start Nautilus with gdb.

```shell
nautilus -q
```
```shell
sudo ln -s $PWD/build/debug/targets/NMBS-Nautilus/libnmbs-nautilusd.so /usr/lib/x86_64-linux-gnu/nautilus/extensions-4/libnmbs-nautilus.so 
```
```shell
sudo rm /usr/lib/x86_64-linux-gnu/nautilus/extensions-4/libnmbs-nautilus.so
```

# Runtime Environment Variables

In addition to anything documented in the [end user documentation](https://nmbs.turnertech.de/), the following 
environment variables are useful for developers: 

| Variable        |                                                                                                      | Example                  |
|-----------------|------------------------------------------------------------------------------------------------------|--------------------------| 
| NMBS_LOCPATH    | An override path to localisation files. No trailing slash.                                           | /usr/share/locale        |

# Localising

The project uses gettext for localisation. Please either update the .po
files in the NMBS-i18n target, or generate a new locale using the following
command. Note that the CMake is fully automated. All .po files in the po 
folder will be automatically built and updated.

```bash
msginit --locale=de.UTF-8 --input=targets/NMBS-i18n/nmbs.pot --output=targets/NMBS-i18n/po/de.po
```

# Standards

- ADatP-4774 (Ed.A V.1 12.2017) CONFIDENTIALITY METADATA LABEL SYNTAX
- ADatP-4778 (Ed.A V.1 10.2018) METADATA BINDING MECHANISM
- ADatP-5636 (Ed.A V.1 11.2022) NATO CORE METADATA SPECIFICATION(NCMS)

# Dependencies

Dependencies are kept to a minimum. Particular focus is paid to ensuring Licenses are all very flexible, APT presence of
packages, and trustworthiness. Ideally, this project will be developed on a Debian distro, with simple calls to install
the libs via APT on a Developer Machine, and APT Dependencies in release.

Check out the [prepare](prepare) script to see all the dependencies.

## External Resources

This project ships with a small number of external resources. Many of these were shipped with the NATO Standards. 
Important to note is that only PUBLIC UNMARKED resources have been included. Unfortunately several XSD resources are
still marked NATO UNCLASSIFIED. It will take some time to write "clean room" implementations from the standards to ship.

Their original sources are as follows.

| File                                       | Source                                                                                     | Description                                                                                                            |
|--------------------------------------------|--------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------|
| nl-cl.xsd                                  | [ADatP-4774.5 EDA V1.zip](https://nso.nato.int/nso/nsdd/main/standards/srd-details/245/EN) | XSD for ConfidentialityLabel                                                                                           |
| nl-mb.xsd                                  | [ADatP-4774.5 EDA V1.zip](https://nso.nato.int/nso/nsdd/main/standards/srd-details/245/EN) | XSD for BindingInformation                                                                                             |
| xmlspif.xsd                                | [xmlspif.org](http://www.xmlspif.org/schema/xmlspif.xsd)                                   | XSD for the "Security Policy Information File" format used to describe available classifications.                      |
| 20140916_PU_PUBLIC Security Policy-v1.spif | [ADatP-4774.5 EDA V1.zip](https://nso.nato.int/nso/nsdd/main/standards/srd-details/245/EN) | This contains a list of the standard classifications used. It is not normative, but till now is the best I have found. |
| 20210506_PU_NATO Security Policy-v88.spif  | [ADatP-4774.5 EDA V1.zip](https://nso.nato.int/nso/nsdd/main/standards/srd-details/245/EN) | This contains a list of the standard classifications used. It is not normative, but till now is the best I have found. |
