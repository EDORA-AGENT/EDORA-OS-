# 🖥️ EDORA OS

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:050505,50:00c6ff,100:0072ff&height=220&section=header&text=EDORA%20OS&fontSize=60&fontColor=ffffff&animation=fadeIn&fontAlignY=35" />
</p>

<p align="center">
  <b>⚡ EDO Shell • 💾 Virtual Filesystem • 🔐 EDO Security • 🌐 Network Tools</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white">
  <img src="https://img.shields.io/badge/EDORA%20OS-v1.3-00c6ff?style=for-the-badge">
  <img src="https://img.shields.io/badge/Virtual%20OS-Experimental-8A2BE2?style=for-the-badge">
  <img src="https://img.shields.io/badge/Status-Active-00C853?style=for-the-badge">
</p>

---

# 🧠 What Is EDORA OS?

**EDORA OS** is an experimental operating-system simulation written in **C++**.

It provides a command-line environment inspired by traditional operating systems while running safely as a normal application on the host machine.

Instead of implementing a real kernel and hardware drivers, EDORA OS creates its own:

```text
┌──────────────────────────────────────────┐
│              🖥️ EDORA OS                 │
├──────────────────────────────────────────┤
│              EDO SHELL                   │
├──────────────────────────────────────────┤
│          💾 VIRTUAL FILESYSTEM            │
├──────────────────────────────────────────┤
│     C:       D:       E:                 │
│   SYSTEM    DATA    BACKUP               │
├──────────────────────────────────────────┤
│             HOST OS                     │
└──────────────────────────────────────────┘
```

> **A small C++ project designed to feel like a tiny operating system.**

---

# ⚡ Features

EDORA OS currently includes a surprisingly large collection of shell features.

### 💾 Virtual Filesystem

EDORA creates its own filesystem inside:

```text
EDORA_DRIVES/
```

with three virtual drives:

```text
C:\    → System
D:\    → Data / Games
E:\    → Backup
```

Example:

```text
C:\
├── system\
├── programs\
│
D:\
├── games\
├── data\
│
E:\
└── backup\
```

The filesystem is backed by the host filesystem but is restricted to the EDORA virtual-drive environment.

---

# 🖥️ EDO Shell

The main interface is **EDO Shell v1.3**.

```text
+================================================+
|                  EDORA OS                      |
|               EDO SHELL v1.3                  |
+================================================+
| Virtual Operating System                       |
| Virtual Filesystem : ONLINE                    |
| EDO Security       : ACTIVE                    |
| Network            : AVAILABLE                |
+================================================+
```

Shell prompt:

```text
user@edora:C:\$
```

Root prompt:

```text
root@edora:C:\$
```

---

# 📂 Filesystem Commands

EDORA includes a collection of filesystem commands.

| Command              | Description             |
| -------------------- | ----------------------- |
| `dir`                | List directory contents |
| `ls`                 | List directory contents |
| `cd <folder>`        | Change directory        |
| `cd ..`              | Go to parent directory  |
| `cd \`               | Go to drive root        |
| `mkdir <name>`       | Create directory        |
| `touch <file>`       | Create file             |
| `rm <name>`          | Delete file/folder      |
| `cat <file>`         | Read file               |
| `type <file>`        | Read file               |
| `copy <src> <dst>`   | Copy files/folders      |
| `move <src> <dst>`   | Move files/folders      |
| `rename <old> <new>` | Rename                  |
| `tree`               | Display directory tree  |
| `find <name>`        | Search for files        |

Example:

```text
C:\> mkdir projects
Directory created.

C:\> cd projects

C:\projects> touch hello.txt
File created.

C:\projects> echo Hello EDORA > hello.txt
```

---

# 📝 Text Tools

EDORA also contains basic text-processing commands.

```text
echo <text>
grep <text> <file>
head <file>
tail <file>
history
```

### Example

```text
C:\> echo Hello World
Hello World

C:\> history

EDORA COMMAND HISTORY
---------------------
   1  help
   2  mkdir projects
   3  cd projects
   4  echo Hello World
```

---

# 🔢 BIN & HEX Tools

EDORA contains experimental binary-file utilities.

### BIN Editor

```text
bin <file>
```

### Read Binary

```text
binread <file>
```

### HEX Viewer

```text
binhex <file>
```

Example:

```text
HEX VIEW

48 65 6c 6c 6f 20 45 44
4f 52 41 00 01 02 03 04
```

These tools are intended for experimentation with file data and binary representations.

---

# 🔐 EDO File Format

EDORA includes its own experimental text encoding system called **EDO**.

```text
edo <file>
edoread <file>
edoraw <file>
```

The current implementation uses a simple **Caesar-style +2 character shift** for alphabetic characters.

Example:

```text
Original:
Hello EDORA

EDO:
Jgnnq GFQTC
```

Read the encrypted file:

```text
edoread file.edo
```

View the raw contents:

```text
edoraw file.edo
```

> ⚠️ EDO is an experimental encoding system, **not cryptographically secure encryption**.

---

# ⏰ System Utilities

EDORA provides several system-style commands.

```text
time
date
datetime
clock
calc
sysinfo
neofetch
```

### Calculator

```text
calc 10 + 20
```

Output:

```text
Result: 30
```

Supported operators:

```text
+
-
*
/
```

---

# 🌐 Network

EDORA includes a real network ping command:

```text
ping <host>
```

Example:

```text
ping google.com
```

The command invokes the host operating system's `ping` utility.

> EDORA itself does not implement a complete network stack.

---

# 🎮 EDORA Games

Because every operating system needs games. :)))

```text
game
```

Current game:

```text
┌──────────────────────────────┐
│        EDORA GAMES            │
├──────────────────────────────┤
│ 1. Guess Number              │
│ 2. Exit                      │
└──────────────────────────────┘
```

### 🎯 Guess Number

Guess a random number between:

```text
1 ──────────────── 100
```

The shell will tell you whether your guess should be higher or lower.

---

# 👑 SUDO & ROOT

EDORA includes a simple root-user simulation.

```text
sudo
```

Check root status:

```text
root
```

Normal user:

```text
user@edora:C:\$
```

Root user:

```text
root@edora:C:\$
```

Root access is used for protected EDORA operations such as the system-delete simulation.

> ⚠️ This is an **application-level user simulation**, not real operating-system privilege escalation.

---

# 💀 Kernel Panic

EDORA even has its own fake kernel panic.

```text
panic
```

Output:

```text
+================================================+
|                 KERNEL PANIC                   |
+================================================+
| EDORA Kernel encountered a fatal error.        |
|                                                |
| System halted.                                 |
+================================================+
```

This is only a visual simulation and does **not** crash the host operating system.

---

# 🗑️ System Delete Simulation

EDORA includes a deliberately dramatic system deletion command:

```text
delete systemcl -t
```

However...

```text
[1/5] Checking system...
[2/5] Checking dependencies...
[3/5] Preparing deletion...
[4/5] Simulation...
[5/5] Cancelled for safety.

EDORA OS remains intact.
```

💀

It is intentionally implemented as a **simulation** rather than actually deleting the EDORA system.

---

# 🔄 Reboot & Shutdown

Restart the virtual environment:

```text
reboot
```

Shutdown EDORA:

```text
shutdown
```

The reboot process resets:

```text
Drive → C:
User  → user
Path  → C:\
```

---

# 📜 Complete Command List

```text
SYSTEM
────────────────────────────────────

help
clear
about
whoami
pwd
drives

FILESYSTEM
────────────────────────────────────

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

TEXT
────────────────────────────────────

echo <text>
grep <text> <file>
head <file>
tail <file>
history

EDITORS
────────────────────────────────────

bin <file>
binread <file>
binhex <file>
edo <file>
edoread <file>
edoraw <file>

UTILITIES
────────────────────────────────────

time
date
datetime
clock
calc <a> <op> <b>
ping <host>
neofetch
sysinfo

SECURITY
────────────────────────────────────

sudo
root

OTHER
────────────────────────────────────

game
panic
delete systemcl -t
reboot
shutdown
exit
```

---

# 🏗️ Architecture

The project is intentionally built without a large framework.

```text
                    EDORA OS
                       │
                 ┌─────┴─────┐
                 │ EDO SHELL │
                 └─────┬─────┘
                       │
       ┌───────────────┼────────────────┐
       ▼               ▼                ▼
  💾 Filesystem    🛠️ Utilities      🔐 Security
       │               │                │
   C: D: E:       calc / ping       sudo / root
       │               │                │
       └───────────────┼────────────────┘
                       ▼
                 🎮 Applications
                       │
                  Game / Editors
```

---

# 🛠️ Build

## Requirements

You need:

* C++17-compatible compiler
* `g++`
* Standard C++ library
* `std::filesystem` support

### Linux / macOS

```bash
g++ main.cpp -std=c++17 -o edora
```

Run:

```bash
./edora
```

### Windows

```bash
g++ main.cpp -std=c++17 -o edora.exe
```

Run:

```bash
edora.exe
```

---

# 📁 Generated Files

When EDORA OS starts for the first time, it creates:

```text
EDORA_DRIVES/
```

Example:

```text
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
```

This directory represents the virtual storage environment of EDORA OS.

---

# 🧪 Project Status

```text
EDORA OS v1.3

████████████████████████████████ 100%

Shell               [██████████] ONLINE
Virtual Filesystem  [██████████] ONLINE
File Manager        [██████████] ONLINE
Text Tools          [██████████] ONLINE
EDO Editor          [██████████] ONLINE
HEX Viewer          [██████████] ONLINE
Calculator          [██████████] ONLINE
Network Ping        [██████████] ONLINE
Games               [██████████] ONLINE
Security Simulation  [██████████] ONLINE
```

**Status: 🟢 Experimental / Functional**

---

# ⚠️ Important Notes

EDORA OS is **not a real bootable operating system**.

It runs as a normal application on top of the host operating system.

It does not currently provide:

* ❌ A real kernel
* ❌ Hardware drivers
* ❌ Bootloader
* ❌ Real process scheduler
* ❌ Real memory management
* ❌ Native hardware abstraction
* ❌ Real OS-level user privileges

Instead, it simulates these concepts where appropriate.

---

# 🔒 Security Notes

This project is primarily educational.

Some components are intentionally simplified.

For example:

```text
sudo password
```

is currently implemented directly inside the source code, and the `ping` command delegates to the host shell.

Therefore:

> **Do not treat EDORA OS as a security boundary or production operating system.**

The virtual filesystem is designed to restrict normal file operations to the EDORA drive environment, but this should not be considered a hardened sandbox.

---

# 🗺️ Roadmap

Future versions may introduce:

* [ ] 🖥️ Graphical Desktop Environment
* [ ] 🪟 Window Manager
* [ ] 📁 Graphical File Manager
* [ ] 📝 Improved Text Editor
* [ ] 🧠 Better command parser
* [ ] 🔐 Improved authentication
* [ ] 💾 Virtual disk images
* [ ] 📦 Package manager
* [ ] 🧩 Plugin system
* [ ] 🎮 More games
* [ ] 🌐 More network utilities
* [ ] 🖥️ Better terminal UI
* [ ] ⚙️ Configuration system
* [ ] 🧪 Automated testing

---

# 🧠 Why I Built This

EDORA OS started as an experiment to answer a simple question:

> **"Can I build my own tiny operating system experience in C++?"**

The result isn't Linux.

It isn't Windows.

It isn't Unix.

It's **EDORA**.

```text
       C++
        │
        ▼
    ┌─────────┐
    │   EDO   │
    │  SHELL  │
    └────┬────┘
         │
    ┌────┴────┐
    ▼         ▼
  💾 FS     🛠️ TOOLS
    │         │
    └────┬────┘
         ▼
     🖥️ EDORA OS
```

---

# 📸 Screenshots

Add screenshots of the terminal here:

```text
assets/
├── terminal.png
├── neofetch.png
├── filesystem.png
└── panic.png
```

Then embed them with:

```html
<p align="center">
  <img src="./assets/terminal.png" width="850" alt="EDORA OS Terminal">
</p>
```

---

# 👨‍💻 Developer

<p align="center">

## Xiao Louie — EDORA STUDIO

💻 C++ Developer
🖥️ OS Experimenter
🐧 Linux Enthusiast
🧪 Builder of questionable software

</p>

---

# ⭐ Support

If you think EDORA OS is interesting:

⭐ **Star the repository**

🐛 Find bugs
💡 Suggest ideas
🔧 Improve the code
🚀 Build something with it

---

<p align="center">

# 🖥️ EDORA OS

### `user@edora:C:\$`

**Think. Build. Break. Rebuild.**

</p>

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:0072ff,50:00c6ff,100:050505&height=120&section=footer"/>
</p>
