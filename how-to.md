---
layout: page
title: How-To
permalink: /how-to/
---
<div style="background-color: #fff3cd; color: #856404; border: 1px solid #ffeeba; padding: 12px; text-align: center; border-radius: 4px; margin-bottom: 25px; font-weight: 500;">
  ⚠️ <strong>Work in Progress:</strong> This project and documentation are currently under active development.
</div>

* TOC
{:toc}

&nbsp;

---
---

## Install nmbs

At the time of writing, __nmbs__ is not yet in the Debian APT repository. Once it is:

```shell
# Get the CLI
sudo apt install nmbs

# Get the GNOME Files integration
sudo apt install nautilus-nmbs
```

Until then, you can [download releases from GitHub](https://github.com/liturner/nmbs/releases).

&nbsp;

---
---

## GNOME

__nmbs__ may be used from within the GNOME Files (Nautilus) application. It integrates seamlessly with the UI.

&nbsp;

---

### How to classify a File

Right Click it in GNOME Files, if it can be classified, the "Classify" option will be in the context menu.

&nbsp;

---

### How to delete a Classification from a File

Right Click it in GNOME Files, if it can be declassified, the "Clear Classification" option will be in the context menu.

&nbsp;

---

### How to view Classification Marking in a Column

If you use the list view in GNOME Files, you can add extra columns. __nmbs__ provides a "Classification" column which can be selected. When activated, the Marking of the Classification will be displayed as in the following example:

![File Properties]({{ "/assets/images/file-column.png" | relative_url }})

&nbsp;

---

### How to view Classification Details in the Properties Screen

While the Marking may be seen in the GNOME Files columns, extra details like when and by whom the classification was made must be accessed in the "Properties" of the file. To access the details, open the properties screen of the Classified File (e.g. via Right Click -> Properties). If the file has been classified, there will be a "Classification" (exact word varies depending on system language) section you can enter. See the following example:

![File Properties]({{ "/assets/images/file-properties.png" | relative_url }})

If you click on the Classification section, the details will be opened in a screen similar to the following:

![Classification Properties Screen]({{ "/assets/images/file-properties-classification.png" | relative_url }})

&nbsp;

---

### How to configure the Originator ID

The Originator ID for any Classifications done by a user in the GNOME Files GUI may be set at the user lever in `dconf`. Please set an RFC822 (email address) style name, such as "user@organisation". This value will only be used on labels set in GNOME Files, and not by the CLI.

```shell
dconf write /org/gnome/nautilus-nmbs/originator-id '"user@organisation.org"'
```

Alternatively, this may be set in a GUI tool such as `dconf-editor`

![dconf-editor]({{ "/assets/images/dconf-editor.png" | relative_url }})

&nbsp;

---
---

## CLI

### How to explore available Security Policies and Classifications

```shell
nmbs-get
```

&nbsp;

---

### How to label a file with a Classification

```shell
nmbs-set
```

&nbsp;

---

### How to check if a file has a Classification

```shell
nmbs-verify
```

&nbsp;

---
---

## Administration

### How to add Company Classifications

__nmbs__ uses [Security Policy Information Files](http://www.xmlspif.org/) (SPIF) to manage and verify policies. If you wish to add extra policies, simply place a valid SPIF file in the "/etc/nmbs/spif" directory. e.g.:

```shell
/etc/nmbs/spif/organisation.org.spif
```

Alternatively, you can also use the override environment variable in certain cases. Only use this if you know what you are doing, using the etc folder is a much better method.

```shell
NMBS_SPIF_DIR_OVERRIDE=/home/user/my-spif-folder
```

&nbsp;

---

### How to override a default SPIF

It is possible to override e.g. the NATO policy which is shipped with the package. This may be usefull if e.g. NATO update their policies, and you wish to have the latest version before __nmbs__ is updated.

Simply ensure that your updated SPIF has the same "securityPolicyId" element, and a newer "version" attribute. Place it in the "/etc/nmbs/spif" directory as previously mentioned. The snippet below highlights the fields used for this functionality.

```xml
<!-- The version attribute must be greater than your installed file -->
<spif:SPIF version="88">
    <!-- The securityPolicyId element must be equivalent with your installed file -->
	<securityPolicyId name="NATO" id="1.3.26.1.3.1"/>
</spif:SPIF>
```

&nbsp;

---
---

## Find more Help

__nmbs__ ships with:

### CLI Tool --help

Use --help on any of the CLI tools to get the most accurate help for your version. e.g.:

```shell
nmbs-get --help
nmbs-set --help
nmbs-verify --help
```

&nbsp;

---

### manpages

Specifically, `man 1` pages are installed for the CLI Tools. At time of writing, this will provide a near identical output to --help

```shell
man 1 nmbs-get
man 1 nmbs-set
man 1 nmbs-verify
```

&nbsp;

---

### API Docs for libnmbs

The API Documentation is available on the [API page]({{ "/api/" | relative_url }}).

Alternatively, if you have installed `libnmbs-doc`, the `doxygen` can be accessed using a `doc-base` tool like `dochelp` or by e.g.

```shell
xdg-open /usr/share/doc/libnmbs-dev/html/index.html
```



