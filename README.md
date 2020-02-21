# ZenithOS

The Zenith Operating System is a modernized, professional fork of the 64-bit Temple Operating System.

Features in development include:
  - Fully-functional AHCI support.
  - Compiler optimizations for speed improvements.
  - ~~VBE support~~ 32-bit color VBE graphics.
  - Network card drivers, network stack.

![](/screenshots/screenshot2.png)

## Getting started

Every commit contains a "Zenith-latest-XXXX-XX-XX-XX-XX_XX_XX.iso" in the root of master, which is a timestamped ISO build of that commit. It might not be complete, or stable. See the "Releases" Tab for the latest stable release.

### Contributing

This basically a read-only repository. Everything happens inside the OS, as intended by Terry. After you've installed the latest release in a VM, you can make changes to the source. Once you've made your changes, you can make copies of the relevant files and put them into a folder, along with some kind of notes as to what you've done as a DolDoc document. You can then make a RedSea ISO file out of that folder by running `RedSeaISO("MyChanges.ISO", "/Home/Folder");`. Mount the VM hard drive in whatever OS-specific way you have to and grab the ISO and send it my way; a pull request attachment would work fine.

## Background

At first, I was developing exclusively inside a VM and occasionally generating ISOs as official releases. This was not a good approach, as things broke and I had no way of telling what changes caused what. So I decided to scrap that and restart from scratch.\
Previous releases are currently archived on the `mega.nz` website:
  - [Previous Releases](https://mega.nz/#F!ZIEGmSRQ!qvL6Wk6THzE-dazkfT6N3Q)

Changes include:
  - 60FPS.
  - VBE graphics with variable resolutions.
  - Added a NONE #define for use in default function arguments.
  - 440Hz 'A' tuning changed to 432Hz.
  - HolyC -> CosmiC.
  - System-wide renames:
    - AOnce -> ZOnce
    - ACAlloc -> ZCAlloc
    - AMAlloc -> ZMAlloc
    - AStrNew -> ZStrNew
    - Adam -> Zenith
    - Seth -> Daemon
    - BEqu -> BEqual
    - Bwd -> Backward
    - Cfg -> Config
    - Chg -> Change
    - Chk -> Check
    - Cmp -> Comp
      - (Compiler. CCmpCtrl->CCompCtrl, etc)
    - Cmp -> Compare
      - (StrCmp->StrCompare, etc)
    - Cnt -> Count
    - Cpy -> Copy
    - Cvt -> Convert
    - Dbg -> Debug
    - Dft -> Default
    - Drv -> Drive
    - Dsk -> Disk
    - Evt -> Event
    - Fmt -> Format
    - Fwd -> Forward
    - Glbls -> Globals
    - Hndlr -> Handler
    - Lst -> List
    - Ms -> Mouse
    - Msg -> Message
    - Pkt -> Packet
    - Pmt -> Prompt
    - Prs -> Parse
    - QSort -> QuickSort
    - Que -> Queue
    - Rem -> Remove
    - Rst -> Reset
    - Rqst -> Request
    - Scrn -> Screen
    - Snd -> Sound
    - Srv -> Server
    - Stk -> Stack
    - Stmt -> Statement
    - TempleOS -> ZenithOS

## Screenshots

32-bit color!

![](/screenshots/screenshot1.png)
