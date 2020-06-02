<a href="https://discord.gg/S6GZfRb"><img alt="Discord" src="https://img.shields.io/discord/661062825027829770?style=flat-square"></a>
![goto counter](https://img.shields.io/github/search/VoidNV/ZenithOS/goto?style=flat-square)
# ZenithOS

The Zenith Operating System is a modernized, professional fork of the 64-bit Temple Operating System.

Features in development include:
  - Fully-functional AHCI support.
  - ~~VBE support~~ 32-bit color VBE graphics.
  - A new GUI framework in 32-bit color.
  - Compiler optimizations for speed improvements.
  - SSE2+ instruction support in compiler and assembler.
  - Network card drivers and a networking stack.

![](/screenshots/screenshot2.png)

## Getting started

Every commit contains a "Zenith-latest-XXXX-XX-XX-XX-XX_XX_XX.iso" in the root of master, which is a timestamped ISO build of that commit. It might not be stable. See the "Releases" page for the latest stable release.

### Contributing

This basically a read-only repository. Everything happens inside the OS, as intended by Terry. After you've installed the latest release in a VM, you can make changes to the source. Once you've made your changes, you can make copies of the relevant files and put them into a folder, along with some kind of notes as to what you've done as a DolDoc document. You can then make a RedSea ISO file out of that folder by running `RedSeaISO("MyChanges.ISO", "/Home/Folder");`. Mount the VM hard drive in whatever OS-specific way you have to, grab the ISO, and send it my way; a pull request attachment would work fine.

## Background

In around November of 2019, I decided I wanted to continue Terry's work in a direction that would make it a viable operating system while still keeping the innovative, and frankly, divine-intellect ideas and strategies intact.

At first, I was developing exclusively inside a VM and occasionally generating ISOs as official releases. This was not a good approach, as things broke and I had no way of telling what changes caused what. So I decided to scrap that and restart from scratch.\
Releases of the "old" Zenith are currently archived on the `mega.nz` website:
  - [Previous Releases](https://mega.nz/#F!ZIEGmSRQ!qvL6Wk6THzE-dazkfT6N3Q)

Changes include:
  - 60FPS.
  - VBE graphics with variable resolutions.
  - 440Hz 'A' tuning changed to 432Hz.
  - HolyC -> CosmiC.
  - System-wide renaming for clarity
  - No weird shift-space mechanism
  - Caps Lock is reassigned as Backspace
  - Reformatted code for readability

## Screenshots

32-bit color!

![](/screenshots/screenshot1.png)
