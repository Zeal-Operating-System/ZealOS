# ZealOS

[![Discord](https://img.shields.io/discord/934200098144022609?color=7289DA&label=Discord&logo=discord&logoColor=white)](https://discord.gg/rK6U3xdr7D) [![](https://img.shields.io/badge/wiki-documentation-forestgreen)](https://github.com/Zeal-Operating-System/ZealOS/wiki)
Zeal
Nor should our zeal in communicating Christian knowledge be relaxed because it has sometimes
to be exercised in expounding matters apparently humble and unimportant, and whose exposition
is usually irksome, especially to minds accustomed to the contemplation of the more sublime
truths of religion. If the Wisdom of the eternal Father descended upon the earth in the meanness
of our flesh to teach us the maxims of a heavenly life, who is there whom the love of Christ does
not constrain to become little in the midst of his brethren, and, as a nurse fostering her children,
so anxiously to wish for the salvation of his neighbours as to be ready, as the Apostle says of
himself, to give them not only the gospel of God, but even his own life.

The Zeal Operating System is a modernized, professional fork of the 64-bit Temple Operating System. Guiding principles of development include transparency, full user control, and adherence to public-domain/open-source implementations.

![](/screenshots/screenshot2.png)

ZealOS strives to be simple, documented, and require as little of a knowledge gap as possible. One person should be able to comprehend the entire system in at least a semi-detailed way within a few days of study.
Simplify, don't complicate; make accessible, don't obfuscate.

> The CIA encourages code obfuscation. They make it more complicated than necessary.\
—Terry A. Davis

Features in development include:
  - [32-bit color VBE graphics](https://github.com/TempleProgramming/HolyGL)
  - Fully-functional AHCI support
  - Network card drivers and a networking stack

[Changes include](https://zeal-operating-system.github.io/Doc/ChangeLog.DD.html):
  - 60 FPS
  - VBE graphics with variable resolutions
  - Reformatted code for readability
  - Added comments and documentation
  - HolyC -> ZealC
  - System-wide renaming for clarity

## Getting started

### Prerequisites

- For running in a VM: Intel VT-x/AMD-V acceleration enabled in your BIOS settings. (Required to virtualize any 64-bit operating system properly.)
    * If using Windows, [Hyper-V must be enabled.](https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/quick-start/enable-hyper-v#enable-the-hyper-v-role-through-settings)
- Working knowledge of the C programming language.

To create a Distro ISO, run the `build-iso` script. Check the Wiki guide for details on [building an ISO](https://github.com/Zeal-Operating-System/ZealOS/wiki/Building-an-ISO). After creating an ISO, see the Wiki guides on installing in [VirtualBox](https://github.com/Zeal-Operating-System/ZealOS/wiki/Installing-(Virtualbox)), [VMWare](https://github.com/Zeal-Operating-System/ZealOS/wiki/Installing-(VMWare)), and [bare-metal](https://github.com/Zeal-Operating-System/ZealOS/wiki/Installing-(Bare%E2%80%90metal)).

### Contributing

There are two ways to contribute. The first way involves everything happening inside the OS, as intended by Terry. After you've built the latest ISO, installed to a VM, made your changes, and powered off the VM, you can run the `sync` script to merge your changes to the repo.

Alternatively, you can edit repo files using an external editor, outside of the OS.

Afterwards, you can make a pull request on the `master` branch.

## Background

In around November of 2019, [VoidNV](https://web.archive.org/web/20210414181948/https://github.com/VoidNV) forked [ZenithOS](https://web.archive.org/web/20200811190005/https://github.com/VoidNV/ZenithOS) from TempleOS. [Releases of pre-git ZenithOS are currently archived on the mega.nz website.](https://mega.nz/#F!ZIEGmSRQ!qvL6Wk6THzE-dazkfT6N3Q) The repository was removed in August of 2020, and reuploaded to [ZenithOS](https://web.archive.org/web/20210630230454/https://github.com/ZenithOS/ZenithOS). The latest archived [front page](https://web.archive.org/web/20200811190005/https://github.com/VoidNV/ZenithOS/), [master.zip](https://web.archive.org/web/20200811190054/https://codeload.github.com/VoidNV/ZenithOS/zip/master), and [related links](https://web.archive.org/web/*/https://github.com/VoidNV/ZenithOS/*) can be found on archive.org.

In July of 2021, ZealOS was forked from ZenithOS.

## Screenshots

Network Report, UDP Chat Application and AutoComplete, with Stars wallpaper

![](/screenshots/screenshot3.png)

32-bit color!

![](/screenshots/screenshot1.png)
