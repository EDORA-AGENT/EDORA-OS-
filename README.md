# 🖥️ EDORA OS

<p align="center">

<img src="https://img.shields.io/badge/EDORA%20OS-2.3-black?style=for-the-badge&logo=linux" alt="EDORA OS">

<img src="https://img.shields.io/badge/Architecture-i386%20%2B%20x86__64-blue?style=for-the-badge" alt="Architecture">

<img src="https://img.shields.io/badge/Boot-BIOS-green?style=for-the-badge" alt="Boot">

<img src="https://img.shields.io/badge/Language-C%2B%2B-orange?style=for-the-badge&logo=c%2B%2B" alt="C++">

<img src="https://img.shields.io/badge/Status-Experimental-purple?style=for-the-badge" alt="Status">

</p>

<p align="center">

**A small real x86 operating system built from scratch.**

</p>

---

## 🚀 About

**EDORA OS** is a personal experimental operating system project created by **XIAO LOUIE**.

The project started as a simple C++ OS simulator and is now being developed into a **real BIOS-bootable x86 operating system**.

EDORA OS currently boots through:

```text
BIOS
 ↓
EDORA Bootloader
 ↓
Kernel loaded from disk
 ↓
A20
 ↓
GDT
 ↓
Protected Mode
 ↓
EDORA Kernel
 ↓
VGA Terminal
 ↓
PS/2 Keyboard
 ↓
Shell
```

### Current status

The stable, fully tested target is the 32-bit BIOS/USB build. An x86_64
experimental branch is also available with a four-level page table, NXE and
serial boot diagnostics, but it is **not production-ready** and should not be
used as the main USB installation yet.

The goal is not to create another Linux distribution.

The goal is to **learn how an operating system works from the lowest level upward.**

---

## ✨ Current Features

### 🥾 Bootloader

* BIOS bootable
* 512-byte boot sector
* BIOS INT 13h disk access
* LBA disk loading
* Kernel loading at `0x10000`
* A20 line enabled
* GDT initialization
* Protected Mode transition
* 32-bit kernel load limit: 64 sectors

### 🧪 x86_64 experimental boot

* Real-mode to protected-mode to long-mode transition
* PML4 -> PDPT -> PD -> PT identity mapping
* `EFER.NXE` validation and activation
* NX pages for stack and VGA memory
* Specific boot failure messages for disk, CPU and NX support
* Serial diagnostics for QEMU

The 64-bit kernel currently stops after boot diagnostics. Authentication,
filesystem, networking, scheduler and user applications remain in the 32-bit
kernel and have not yet been ported to x86_64.

### 🧠 Kernel

* Freestanding C++
* x86 / i386 architecture
* Custom kernel entry point
* Custom linker script
* Kernel stack
* Protected Mode execution

### ⌨️ Keyboard

* PS/2 keyboard driver
* Polling input
* Letters
* Numbers
* Symbols
* Shift
* Caps Lock
* Backspace
* Enter
* Tab

### 🖥️ VGA Terminal

* VGA text mode
* `80 × 25`
* Hardware cursor
* Colored text
* Header
* Footer
* Terminal box
* Scrolling
* Command prompt

Example:

```text
┌──────────────────────────────────────────────────────────────────────────────┐
│ EDORA TERMINAL 3.1                                             EDORA OS      │
├──────────────────────────────────────────────────────────────────────────────┤
│                                                                              │
│  EDORA OS                                                                    │
│  Real x86 Operating System                                                   │
│                                                                              │
│  [ OK ] Kernel online                                                        │
│  [ OK ] VGA terminal initialized                                             │
│  [ OK ] PS/2 keyboard ready                                                  │
│                                                                              │
│  Type 'help' to see available commands.                                      │
│                                                                              │
│  EDORA:\> _                                                                 │
│                                                                              │
└──────────────────────────────────────────────────────────────────────────────┘
```

---

## 💻 Shell

Current shell commands:

```text
help
clear
about
echo
```

Example:

```text
EDORA:\> about

EDORA OS 2.3
------------------------------
Real x86 Operating System
Architecture : i386
Boot         : BIOS
CPU Mode     : Protected Mode
Keyboard     : PS/2
Display      : VGA 80x25
Terminal     : EDORA VGA 3.1
Made by      : XIAO LOUIE
```

---

## 🏗️ Project Structure

```text
EDORA-OS-/
│
├── boot/
│   ├── 32/
│   │   └── boot.asm
│   └── 64/
│       └── boot64.asm
│
├── kernel/
│   ├── kernel.cpp
│   ├── kernel.h
│   │
│   ├── real32/
│   │   ├── kernel_main.cpp
│   │   ├── kernel_entry.asm
│   │   ├── linker.ld
│   │   ├── core/
│   │   │   ├── paging.cpp
│   │   │   ├── exceptions.cpp
│   │   │   ├── filesystem.cpp
│   │   │   └── process.cpp
│   │   └── drivers/
│   │       ├── keyboard.cpp
│   │       ├── ata.cpp
│   │       ├── timer.cpp
│   │       ├── rtl8139.cpp
│   │       └── vga.cpp
│
│   └── real64/
│       ├── kernel_entry.asm
│       ├── kernel_main.cpp
│       └── linker.ld
│
├── shell/
│
├── filesystem/
│
├── commands/
│
├── apps/
│
├── network/
│
├── login/
│
├── main.cpp
├── edora.h
├── CMakeLists.txt
└── README.md
```

The original simulator is kept alongside the real OS development so the project can evolve without losing the earlier work.

---

## 🛠️ Toolchain

EDORA OS is currently developed and tested with:

| Tool                   | Purpose          |
| ---------------------- | ---------------- |
| NASM                   | Assembly         |
| Clang                  | Freestanding C++ |
| LLD                    | ELF/i386 linking |
| QEMU                   | Virtual machine  |
| PowerShell             | Build workflow   |
| VS Code / Code::Blocks | Development      |

---

## 🔨 Build

The Makefile is the recommended build entry point.

### Stable 32-bit build

```powershell
mingw32-make clean
mingw32-make
mingw32-make run
```

The output is:

```text
build/edora.img
```

### USB RAMFS image

The kernel RAMFS is embedded in the image and loaded into memory at boot. No
hard disk is required after boot.

```powershell
mingw32-make usb
mingw32-make run-usb
```

The raw USB image is:

```text
build/edora-usb.img
```

Write this image in raw/DD mode with Rufus or a similar tool. The current USB
boot path is BIOS/Legacy or CSM; UEFI-only systems are not supported by this
image yet.

### Experimental 64-bit build

```powershell
mingw32-make x64
mingw32-make run64
```

Output:

```text
build64/edora64.img
```

This target is for QEMU validation only. It is explicitly **not ready for
real hardware or production USB boot**. The serial output should reach:

```text
EDORA64: kernel entry
EDORA64: EFER.NXE enabled
EDORA64: 4-level paging active
EDORA64: boot completed
```

The `BOOTX64.EFI` file is currently a UEFI diagnostic application and does
not yet hand off to the 32-bit kernel.

### 1. Assemble the bootloader

```powershell
nasm -f bin boot\32\boot.asm -o build\boot.bin
```

### 2. Assemble kernel entry

```powershell
nasm -f elf32 kernel\real32\kernel_entry.asm -o build\kernel_entry.o
```

### 3. Compile keyboard driver

```powershell
clang++ --target=i386-unknown-elf -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -nostdinc++ -c kernel\real32\drivers\keyboard.cpp -o build\keyboard.o
```

### 4. Compile VGA driver

```powershell
clang++ --target=i386-unknown-elf -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -nostdinc++ -c kernel\real32\drivers\vga.cpp -o build\vga.o
```

### 5. Compile kernel

```powershell
clang++ --target=i386-unknown-elf -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -nostdinc++ -c kernel\real32\kernel_main.cpp -o build\kernel_main.o
```

### 6. Link kernel

```powershell
ld.lld -m elf_i386 -T kernel\real32\linker.ld --oformat binary -o build\kernel.bin build\kernel_entry.o build\kernel_main.o build\keyboard.o build\vga.o
```

---

## 💿 Create Disk Image

Combine the bootloader and kernel:

```powershell
Remove-Item build\edora.img -ErrorAction SilentlyContinue

cmd /c copy /b build\boot.bin+build\kernel.bin build\edora.img
```

Pad the image to complete sectors:

```powershell
$img = [System.IO.File]::ReadAllBytes("build\edora.img")
$size = [Math]::Ceiling($img.Length / 512) * 512

$img2 = New-Object byte[] $size

[Array]::Copy($img, $img2, $img.Length)

[System.IO.File]::WriteAllBytes(
    "build\edora.img",
    $img2
)
```

---

## 🧪 Run with QEMU

```powershell
& ".\qemu\qemu-system-x86_64.exe" `
    -drive format=raw,file=build\edora.img `
    -boot c
```

EDORA OS should boot directly from the virtual disk.

---

## 🧬 Boot Architecture

```text
                 ┌──────────────────┐
                 │      BIOS        │
                 └────────┬─────────┘
                          │
                          ▼
                 ┌──────────────────┐
                 │ EDORA Bootloader │
                 │    512 bytes     │
                 └────────┬─────────┘
                          │
                    INT 13h / LBA
                          │
                          ▼
                 ┌──────────────────┐
                 │   EDORA Kernel   │
                 │     0x10000      │
                 └────────┬─────────┘
                          │
                          ▼
                    Enable A20
                          │
                          ▼
                    Load GDT
                          │
                          ▼
                 ┌──────────────────┐
                 │ Protected Mode   │
                 └────────┬─────────┘
                          │
                          ▼
                 ┌──────────────────┐
                 │   Kernel Main    │
                 └────────┬─────────┘
                          │
             ┌────────────┴────────────┐
             ▼                         ▼
      ┌─────────────┐           ┌─────────────┐
      │ VGA Driver  │           │ PS/2 Driver │
      └──────┬──────┘           └──────┬──────┘
             │                         │
             └────────────┬────────────┘
                          ▼
                   EDORA TERMINAL
```

---

## 🗺️ Roadmap

### EDORA OS 2.x

* [x] BIOS bootloader
* [x] Kernel loading
* [x] A20
* [x] GDT
* [x] Protected Mode
* [x] Real x86 kernel
* [x] PS/2 keyboard
* [x] VGA terminal
* [x] Hardware cursor
* [x] Basic shell
* [ ] `history`
* [ ] `reboot`
* [ ] Better command parser

### EDORA OS 2.4

**RAM Filesystem**

```text
dir
cd
pwd
mkdir
touch
cat
rm
```

### EDORA OS 2.5

* Calculator
* System time
* Basic system information
* More shell utilities

### EDORA OS 2.6

**Interrupt System**

* IDT
* PIC
* IRQ
* Keyboard interrupts
* Timer interrupts

### EDORA OS 2.7

**Memory Management**

* Physical memory manager
* Heap
* Kernel allocator

### EDORA OS 3.0

**Applications**

* Games
* Text applications
* System utilities

### EDORA OS 3.5

**Graphics**

* Mouse
* Framebuffer
* Graphics primitives

### EDORA OS 4.0

**Desktop**

```text
┌─────────────────────────────────────────────┐
│ EDORA OS                         12:42      │
├─────────────────────────────────────────────┤
│                                             │
│      🗂 Files      ⚙ Settings      💻 Shell │
│                                             │
│                                             │
├─────────────────────────────────────────────┤
│ EDORA OS                                    │
└─────────────────────────────────────────────┘
```

---

## 🎯 Project Philosophy

EDORA OS is mainly a **learning and experimentation project**.

Instead of relying on an existing operating-system framework, the project explores the fundamentals:

```text
Boot
 ↓
CPU modes
 ↓
Memory
 ↓
Interrupts
 ↓
Drivers
 ↓
Filesystem
 ↓
Processes
 ↓
Applications
 ↓
Desktop
```

Every subsystem is built step-by-step.

---

## 👨‍💻 Creator

**XIAO LOUIE**

Cyber Security • C/C++ Developer • Creator

EDORA Studio / EDORA-AGENT

> Building things from zero, one layer at a time.

---

## ⭐ Support

If you find the project interesting, consider giving the repository a ⭐ on GitHub.

It helps motivate further development of EDORA OS.

---

## 📜 License

EDORA OS is an experimental personal project.

See the repository license for the applicable terms.

---

## ⚡ Status

> 🟢 **EDORA OS is currently booting successfully on x86 through BIOS/QEMU.**

Current milestone:

```text
EDORA OS 2.3
        ↓
Real x86 Kernel
        ↓
Protected Mode
        ↓
VGA Terminal 3.1
        ↓
PS/2 Keyboard
        ↓
Interactive Shell
```

---

### MADE BY XIAO LOUIE

**A young programmer building EDORA OS from scratch.** ❤️

**A 13-year-old programmer**

💻 C++ Developer
🐧 Linux Enthusiast
⚙️ EDORA OS Creator
🚀 EDORA STUDIO

<br>

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0072ff,100:00c6ff&height=120&section=footer&animation=fadeIn" width="100%"/>

**EDORA OS — Build. Learn. Create.**

</div>
