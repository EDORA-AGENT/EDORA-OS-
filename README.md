<div align="center"><img src="https://capsule-render.vercel.app/api?type=waving&color=0:050505,50:00C6FF,100:0066FF&height=220&section=header&text=EDORA%20OS&fontSize=70&fontColor=FFFFFF&animation=fadeIn&fontAlignY=35&desc=Experimental%20Operating%20System%20Simulation&descAlignY=58&descSize=18" width="100%"/>🖥️ EDORA OS

"A tiny operating-system experience built with C++"

<p>
  <img src="https://img.shields.io/badge/C%2B%2B-17%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white"/>
  <img src="https://img.shields.io/badge/EDORA%20OS-Experimental-00C6FF?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Architecture-Modular-7F00FF?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge"/>
</p><p>
  <b>Kernel</b> •
  <b>Shell</b> •
  <b>Virtual Filesystem</b> •
  <b>Login</b> •
  <b>Network</b> •
  <b>Applications</b>
</p><br>«EDORA OS isn't Linux.

It isn't Windows.

It's EDORA.»

</div>---

🧠 What is EDORA OS?
EDORA OS is an experimental operating-system simulation written in C++.

The project is designed to recreate the feeling of using an operating system — including a kernel layer, login system, shell, virtual drives, filesystem management, applications, security simulation and network utilities — while still running as a normal application on the host operating system.

The latest version has been reorganized into a more modular architecture instead of putting the entire system inside one giant source file.

                         ┌──────────────────────┐
                         │      EDORA OS        │
                         └──────────┬───────────┘
                                    │
                         ┌──────────▼───────────┐
                         │        KERNEL        │
                         └──────────┬───────────┘
                                    │
              ┌─────────────────────┼─────────────────────┐
              │                     │                     │
       ┌──────▼──────┐      ┌──────▼──────┐      ┌──────▼──────┐
       │    LOGIN    │      │    SHELL    │      │  NETWORK    │
       └─────────────┘      └──────┬──────┘      └─────────────┘
                                   │
                    ┌──────────────┼──────────────┐
                    │              │              │
              ┌─────▼─────┐ ┌────▼─────┐ ┌──────▼──────┐
              │ FILESYSTEM │ │ COMMANDS │ │    APPS     │
              └────────────┘ └──────────┘ └─────────────┘

---

⚡ Features

Component| Status
🧠 Kernel layer| 🟢 Active
💻 EDO Shell| 🟢 Active
🔐 Login system| 🟢 Active
💾 Virtual filesystem| 🟢 Active
📁 File management| 🟢 Active
🌐 Network tools| 🟢 Active
📝 Notepad / Editors| 🟢 Active
🔢 Binary / HEX tools| 🟢 Active
🎮 Applications / Games| 🟢 Active
👑 Root simulation| 🟢 Active
💥 Kernel Panic simulation| 🟢 Active
🔄 Reboot / Shutdown| 🟢 Active

---

🏗️ Project Structure

The new architecture separates EDORA OS into multiple components:

EDORA-OS-/
│
├── 📁 apps/
│   └── Applications & built-in programs
│
├── 📁 commands/
│   └── Shell command implementations
│
├── 📁 filesystem/
│   └── Virtual filesystem management
│
├── 📁 kernel/
│   └── Kernel initialization & system lifecycle
│
├── 📁 login/
│   └── Login / authentication system
│
├── 📁 network/
│   └── Network-related functionality
│
├── 📁 shell/
│   └── EDO Shell
│
├── 📄 edora.h
├── 📄 main.cpp
├── 📄 CMakeLists.txt
├── 📄 LICENSE
└── 📄 README.md

This modular structure makes it easier to extend EDORA OS without turning the project into one giant source file.

---

🧠 Kernel

EDORA includes a dedicated kernel layer responsible for the system lifecycle.

kernelInit()
      │
      ▼
   EDORA OS
      │
      ├── Shell
      ├── Filesystem
      ├── Login
      └── Applications
      │
      ▼
kernelShutdown()

The kernel currently provides an OS-like abstraction rather than directly controlling hardware.

Kernel functions

kernelInit()
kernelShutdown()
kernelPanic()
rebootSystem()
shutdownSystem()

«⚠️ EDORA's kernel is a simulation layer. It is not a real hardware kernel.»

---

🔐 Login System

EDORA now initializes a login stage before entering the shell.

┌──────────────────────────────────┐
│          EDORA OS LOGIN          │
├──────────────────────────────────┤
│                                  │
│  Username:                       │
│  Password:                       │
│                                  │
│  [ AUTHENTICATING... ]           │
│                                  │
└──────────────────────────────────┘

After successful authentication:

LOGIN
  │
  ▼
KERNEL
  │
  ▼
SHELL

---

💻 EDO Shell

The EDO Shell is the main interface of EDORA OS.

Example:

EDORA OS
EDO SHELL

Virtual Operating System
Filesystem : ONLINE
Security   : ACTIVE
Network    : AVAILABLE

user@edora:C:\$

Root mode:

root@edora:C:\$

---

📂 Virtual Filesystem

EDORA creates its own virtual storage environment:

EDORA_DRIVES/
│
├── C/
│   ├── system/
│   └── programs/
│
├── D/
│   ├── games/
│   └── data/
│
└── E/
    └── backup/

Virtual drives

C:\   → System
D:\   → Data / Games
E:\   → Backup

The filesystem uses the host filesystem as its storage layer while providing EDORA's own drive/path abstraction.

---

📁 Filesystem Commands

dir / ls
cd <folder>
cd ..
cd \
mkdir <name>
touch <file>
rm <name>
cat <file>
type <file>
copy <src> <dst>
move <src> <dst>
rename <old> <new>
tree
find <name>

Example:

C:\> mkdir projects

Directory created.

C:\> cd projects

C:\projects> touch hello.txt

File created.

C:\projects> cat hello.txt

---

📝 Text Tools

EDORA provides several basic text-processing utilities:

echo <text>
grep <text> <file>
head <file>
tail <file>
history

Example:

C:\> echo Hello EDORA

Hello EDORA

C:\> history

1  help
2  mkdir projects
3  cd projects
4  echo Hello EDORA

---

🔢 Binary & HEX Tools

EDORA includes experimental tools for working with binary data.

Binary Editor

bin <file>

Binary Reader

binread <file>

HEX Viewer

binhex <file>

Example:

HEX VIEW

48 65 6C 6C 6F 20 45 44
4F 52 41 00 01 02 03 04

These tools are mainly intended for learning and experimentation with raw file data.

---

📝 EDO Editor

EDORA also contains its own experimental ".edo" file system.

edo <file>
edoread <file>
edoraw <file>

Example:

Original:

Hello EDORA

Experimental EDO representation:

Jgnnq GFQTC

«⚠️ EDO is an experimental encoding mechanism, not secure cryptographic encryption.»

---

🧮 System Utilities

EDORA provides several system-style utilities:

time
date
datetime
clock
calc
sysinfo
neofetch

Calculator:

C:\> calc 10 + 20

Result: 30

Supported operators:

+
-
*
/

---

🌐 Network

EDORA includes a network utility:

ping <host>

Example:

C:\> ping google.com

The current implementation delegates the ping operation to the host operating system.

EDORA does not currently implement a complete native network stack.

---

🎮 EDORA Applications

Because every OS needs applications.

And games.

Obviously. :)))

┌──────────────────────────────┐
│       EDORA APPLICATIONS     │
├──────────────────────────────┤
│  📝 Notepad                  │
│  🔢 Binary Editor            │
│  🔍 HEX Viewer               │
│  📄 EDO Editor               │
│  🎮 Games                    │
└──────────────────────────────┘

🎯 Guess Number

The built-in game generates a number between:

1 ─────────────────── 100

Your mission:

GUESS THE NUMBER.

---

👑 SUDO & ROOT

EDORA provides an application-level root simulation.

Normal user:

user@edora:C:\$

Root:

root@edora:C:\$

Commands:

sudo
root
passwd

Root permissions are used for protected EDORA operations.

«⚠️ This is not real operating-system privilege escalation.
It only changes EDORA's internal user state.»

---

💥 Kernel Panic

Yes.

EDORA has a kernel panic.

panic

Output:

╔══════════════════════════════════════════╗
║              KERNEL PANIC                ║
╠══════════════════════════════════════════╣
║                                          ║
║ EDORA Kernel encountered a fatal error.  ║
║                                          ║
║ System halted.                           ║
║                                          ║
╚══════════════════════════════════════════╝

Don't worry.

It is simulated.

Your actual operating system survives. :)))

---

🗑️ System Delete Simulation

EDORA contains a deliberately dramatic system-destruction simulation:

delete systemcl -t

Example:

[1/5] Checking system...
[2/5] Checking dependencies...
[3/5] Preparing deletion...
[4/5] Simulation...
[5/5] Cancelled for safety.

EDORA OS remains intact.

💀 Don't worry.

It doesn't actually destroy the host operating system.

---

🔄 Reboot & Shutdown

Restart the EDORA environment:

reboot

Shutdown:

shutdown

Exit the shell:

exit

A reboot resets the virtual environment back to its initial state.

---

📜 Command Reference

SYSTEM

help
clear
about
whoami
pwd
drives
neofetch
sysinfo
time
date
datetime
clock

FILESYSTEM

dir
ls
cd
mkdir
touch
rm
cat
type
copy
move
rename
tree
find

TEXT

echo
grep
head
tail
history

EDITORS

bin
binread
binhex
edo
edoread
edoraw

NETWORK

ping

SECURITY

sudo
root
passwd

APPLICATIONS

game

SYSTEM CONTROL

panic
delete systemcl -t
reboot
shutdown
exit

---

🧩 Architecture

The current project is structured around several independent modules:

                         ┌─────────────────┐
                         │    EDORA OS     │
                         └────────┬────────┘
                                  │
              ┌───────────────────┼───────────────────┐
              │                   │                   │
        ┌─────▼─────┐       ┌────▼────┐       ┌──────▼─────┐
        │   KERNEL  │       │  LOGIN  │       │  NETWORK   │
        └─────┬─────┘       └─────────┘       └────────────┘
              │
        ┌─────▼─────┐
        │   SHELL   │
        └─────┬─────┘
              │
    ┌─────────┼─────────┐
    │         │         │
┌───▼───┐ ┌──▼────┐ ┌──▼────┐
│  FS   │ │COMMAND│ │  APPS │
└───────┘ └───────┘ └───────┘

---

🛠️ Build

Requirements

You need:

- C++17-compatible compiler
- "g++" or another C++17 compiler
- Standard C++ library
- C++17 "<filesystem>" support
- CMake (optional, depending on your build workflow)

---

⚡ Compile with g++

g++ main.cpp -std=c++17 -o edora

Run:

./edora

Windows

g++ main.cpp -std=c++17 -o edora.exe

Run:

.\edora.exe

---

📦 CMake

EDORA also includes:

CMakeLists.txt

This allows the project to move toward a cleaner cross-platform build workflow as the architecture grows.

---

🚀 Quick Start

git clone https://github.com/EDORA-AGENT/EDORA-OS-.git

cd EDORA-OS-

g++ main.cpp -std=c++17 -o edora

./edora

Then:

login
   ↓
kernel
   ↓
EDO Shell
   ↓
start exploring

Try:

help
neofetch
drives
ls
sysinfo
game

---

📸 Screenshots

Add your screenshots inside:

assets/
├── terminal.png
├── login.png
├── neofetch.png
├── filesystem.png
├── root.png
└── panic.png

Then display them here:

<p align="center">
  <img src="./assets/terminal.png" width="850" alt="EDORA OS Terminal">
</p>

---

🧪 Project Status

EDORA OS
══════════════════════════════════════════════

Kernel              [██████████] ONLINE
Login               [██████████] ONLINE
Shell               [██████████] ONLINE
Filesystem          [██████████] ONLINE
Commands            [██████████] ONLINE
Applications        [██████████] ONLINE
Network             [██████████] ONLINE
Security Simulation [██████████] ONLINE

STATUS: 🟢 EXPERIMENTAL / ACTIVE

EDORA is still an experimental project and is actively evolving.

---

⚠️ Important

EDORA OS is not a bootable operating system.

It currently runs as a normal application on top of the host OS.

It does not currently provide:

❌ Real hardware drivers
❌ Real bootloader
❌ Real CPU scheduling
❌ Real memory management
❌ Native hardware abstraction
❌ Real OS-level privileges
❌ A complete native network stack

Instead, EDORA simulates many operating-system concepts for experimentation and learning.

---

🔒 Security Notes

EDORA is primarily an educational and experimental project.

Some systems are intentionally simplified.

For example:

- Authentication is currently application-level.
- Root is simulated internally.
- The virtual filesystem is not a hardened security sandbox.
- Network commands may interact with utilities provided by the host OS.

Do not use EDORA OS as a security boundary or production operating system.

---

🗺️ Roadmap

[✓] Modular Kernel
[✓] EDO Shell
[✓] Virtual Filesystem
[✓] Login System
[✓] Command System
[✓] Applications
[✓] Network Tools
[✓] Root Simulation

[ ] Graphical Desktop Environment
[ ] Window Manager
[ ] GUI File Manager
[ ] Better Command Parser
[ ] Improved Authentication
[ ] Virtual Disk Images
[ ] Package Manager
[ ] Plugin System
[ ] More Applications
[ ] Better Terminal UI
[ ] Configuration System
[ ] Automated Tests

---

🧠 Why EDORA?

EDORA OS started with a simple question:

«"What if I built my own operating-system experience in C++?"»

Not Linux.

Not Windows.

Not Unix.

Something different.

Something experimental.

Something that I could build from scratch and continuously improve.

              C++
               │
               ▼
        ┌─────────────┐
        │    EDORA    │
        │     OS      │
        └──────┬──────┘
               │
       ┌───────┼────────┐
       │       │        │
       ▼       ▼        ▼
    KERNEL   SHELL     FS
       │       │        │
       └───────┼────────┘
               ▼
        ┌─────────────┐
        │   EDORA OS  │
        └─────────────┘

---

👨‍💻 Developer

<div align="center">Xiao Louie

EDORA STUDIO

💻 C++ Developer
🖥️ OS Experimenter
🐧 Linux Enthusiast
🔐 Cybersecurity Learner
🧪 Builder of questionable software

</div>---

⭐ Support

If you like the project:

⭐ Star the repository

🐛 Report bugs

💡 Suggest features

🔧 Contribute improvements

🚀 Build your own experiments with EDORA

---

<div align="center">🖥️ EDORA OS

user@edora:C:\$ _

Think. Build. Break. Rebuild.

<br><img src="https://capsule-render.vercel.app/api?type=waving&color=0:0066FF,50:00C6FF,100:050505&height=120&section=footer" width="100%"/></div>