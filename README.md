![Website](https://img.shields.io/website?down_color=lightgray&down_message=offline&style=flat-square&up_color=green&up_message=online&url=https%3A%2F%2Fzenithos.org)
![goto counter](https://img.shields.io/github/search/VoidNV/ZenithOS/goto?style=flat-square)
# ZenithOS

The Zenith Operating System is a modernized, professional fork of the 64-bit Temple Operating System. It is a direct reaction against corporate technological subversion, their takeover of free and open source software, and the removal of complete user control over computers.

![](/screenshots/screenshot2.png)

Unlike the \*nix atheists who thrive on distinguishing themselves from the "others" by making the system inaccessible, unintuitive, and require arcane knowledge to work with, we strive to be simple, documented, and require as little of a knowledge gap as possible. One person should be able to comprehend the entire system in at least a semi-detailed way within a few days of study. We simplify, not complicate; make accessible, not obfuscate.

> The CIA encourages code obfuscation. They make it more complicated than necessary.\
—Terry A. Davis

Features in development include:
  - Fully-functional AHCI support
  - ~~VBE support~~ 32-bit color VBE graphics
  - A new GUI framework in 32-bit color
  - Compiler optimizations for speed improvements
  - SSE2+ instruction support in compiler and assembler
  - Network card drivers and a networking stack


Changes include:
  - 60 FPS
  - VBE graphics with variable resolutions
  - 440Hz 'A' tuning changed to 432Hz
  - HolyC -> CosmiC
  - System-wide renaming for clarity
  - No weird shift-space mechanism
  - Caps Lock is reassigned as Backspace
  - Reformatted code for readability
  - Added comments and documentation

## Getting started

### Prerequisites

- For running in a VM: Intel VT-x/AMD-V acceleration enabled in your BIOS settings (required to virtualize any 64-bit operating system properly).
- A brain capable of becoming un-"jedi-mind-tricked".

Every commit contains a "Zenith-latest-YYYY-MM-DD-HH_MM_SS.iso" in the root of master, which is a timestamped ISO build of that commit. It might not be stable. See the [Releases](https://github.com/VoidNV/ZenithOS/releases) for the latest stable release. As ZenithOS is in heavy development the last release may be quite behind from master.

This is basically a read-only repository. Everything happens inside the OS, as intended by Terry. After you've installed the latest release in a VM, you can make changes to the source. Once you've made your changes, you can make copies of the relevant files and put them into a folder, along with some kind of notes as to what you've done either as a DolDoc document or in the pull request later. You can then make a RedSea ISO file out of that folder by running `RedSeaISO("MyChanges.ISO", "/Home/Folder");`. Export the contents of the VM hard drive in whatever OS-specific way you have to (there are scripts in the root of the repo), grab the ISO, and send it my way; a pull request attachment with the zipped ISO would work fine.

## Background

In around November of 2019, I decided I wanted to continue Terry's work in a direction that would make it a viable operating system while still keeping the innovative and frankly, divine-intellect ideas and design strategies intact.

At first, I was developing exclusively inside a VM and occasionally generating ISOs as official releases. This was not a good approach, as things broke and I had no way of telling which changes caused what. So I decided to scrap that and restart from scratch.\
Releases of the "old" Zenith are currently archived on the `mega.nz` website:
  - [Previous Releases](https://mega.nz/#F!ZIEGmSRQ!qvL6Wk6THzE-dazkfT6N3Q)

## Screenshots

System Report, Z Splash and AutoComplete, with Stars wallpaper

![](/screenshots/screenshot3.png)

32-bit color!

![](/screenshots/screenshot1.png)
