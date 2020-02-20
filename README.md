# ZenithOS
[ZenithOS.org](http://zenithos.org/)

The Zenith Operating System is a modernized, professional fork of the 64-bit Temple Operating System.

Features in development include:
  - Fully-functional AHCI support.
  - Compiler optimizations for speed improvements.
  - ~~VBE support~~ 32-bit color VBE graphics.
  - Network card drivers, network stack.

Every commit contains a "Zenith-Latest.iso" in the /src/Tmp folder, which is an ISO build of that commit.

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
