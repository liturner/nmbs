---
layout: page
title: How-To
permalink: /how-to/
---

## GNOME

nmbs may be used from within the GNOME Files (Nautilus) application. It integrates seamlessly with the UI.

### How to configure the Originator ID

The Originator ID for any Classifications done by a user in the GNOME Files GUI may be set at the user lever in dconf. Please set an RFC822 (email address) style name, such as "user@organisation". This value will only be used on labels set in GNOME Files, and not by the CLI.

> dconf write /org/gnome/nautilus-nmbs/originator-id '"user@organisation.org"'

Alternatively, this may be set in a GUI tool such as *dconf-editor*

![]({{ "/assets/images/dconf-editor.png" | relative_url }})

## CLI

