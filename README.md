# ZealOS

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

[Changes include](https://zeal-operating-system.github.io/ZealOS/Doc/ChangeLog.DD.html):
  - 60 FPS
  - VBE graphics with variable resolutions
  - Reformatted code for readability
  - Added comments and documentation
  - HolyC -> CosmiC
  - System-wide renaming for clarity
  - Removed shift-space mechanism
  - 440Hz 'A' tuning changed to 432Hz

## Getting started

### Prerequisites

- For running in a VM: Intel VT-x/AMD-V acceleration enabled in your BIOS settings. (Required to virtualize any 64-bit operating system properly.)
- Working knowledge of the C programming language.

Every commit contains a "ZealOS-YYYY-MM-DD-HH_MM_SS.iso" in the root of master, which is a timestamped ISO build of that commit. Use this ISO for installation: see the Wiki for guides on installing in [VirtualBox](https://github.com/Zeal-Operating-System/ZealOS/wiki/Installing-(Virtualbox)), [VMWare](https://github.com/Zeal-Operating-System/ZealOS/wiki/Installing-(VMWare)), and [bare-metal](https://github.com/Zeal-Operating-System/ZealOS/wiki/Installing-(Bare%E2%80%90metal)).

### Contributing

This is basically a read-only repository. Everything happens inside the OS, as intended by Terry. After you've installed the latest release in a VM and made your changes, you can run the `K.CC` file in the Home/ directory to build a Distro ISO. Then, use either the `mnt.sh` or `export.ps1` script to merge your changes & Distro ISO to the repo. 

Alternatively, you can put individual files into a folder, and run `RedSeaISO("MyChanges.ISO", "/Home/Folder");` to package them into an ISO, then use the mount scripts to export the ISO.

Afterwards, you can make a pull request on the `master` branch. (Make sure to include either the new Distro ISO or package ISO in the pull request, since all other files on the repo are read-only and overwritten each commit: all merges are done manually.)

## Background

In around November of 2019, [VoidNV](https://web.archive.org/web/20210414181948/https://github.com/VoidNV) forked [ZenithOS](https://web.archive.org/web/20200811190005/https://github.com/VoidNV/ZenithOS) from TempleOS to continue Terry's work in a direction that would make it a viable operating system while still keeping the innovative and divine-intellect ideas and design strategies intact. At first, development occurred exclusively inside a VM and ISOs were occasionally generated as official releases, but this was scrapped and restarted from scratch. [Releases of the "old" ZenithOS are currently archived on the mega.nz website.](https://mega.nz/#F!ZIEGmSRQ!qvL6Wk6THzE-dazkfT6N3Q) The repository was removed in August of 2020, and reuploaded to [ZenithOS](https://web.archive.org/web/20210630230454/https://github.com/ZenithOS/ZenithOS). The latest archived [front page](https://web.archive.org/web/20200811190005/https://github.com/VoidNV/ZenithOS/), [master.zip](https://web.archive.org/web/20200811190054/https://codeload.github.com/VoidNV/ZenithOS/zip/master), and [related links](https://web.archive.org/web/*/https://github.com/VoidNV/ZenithOS/*) can be found on archive.org.

In July of 2021, ZealOS was forked from ZenithOS.

## Screenshots

Network Report, UDP Chat Application and AutoComplete, with Stars wallpaper

![](/screenshots/screenshot3.png)

32-bit color!

![](/screenshots/screenshot1.png)
