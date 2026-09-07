<div align="center">

<a href="https://github.com/EDORA-AGENT/EDORA-OS-">
  <img src="https://readme-typing-svg.demolab.com?font=JetBrains+Mono&size=28&duration=3000&pause=800&color=00C8FF&center=true&vCenter=true&width=700&lines=Welcome+to+EDORA+OS;A+Custom+OS+Simulator;Built+with+C%2B%2B;EDORA+OS+v1.0" alt="Typing SVG" />
</a>

<br>

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:00c6ff,100:0072ff&height=180&section=header&text=EDORA%20OS&fontSize=55&fontColor=ffffff&animation=fadeIn&fontAlignY=35" width="100%"/>


### ⚡ A lightweight operating system simulator written in C++

[![Version](https://img.shields.io/badge/EDORA%20OS-v1.0-00c6ff?style=for-the-badge)](https://github.com/EDORA-AGENT/EDORA-OS-)
[![Language](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge\&logo=cplusplus\&logoColor=white)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/Build-CMake-064F8C?style=for-the-badge\&logo=cmake\&logoColor=white)](https://cmake.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge\&logo=windows\&logoColor=white)](https://www.microsoft.com/windows)
[![Status](https://img.shields.io/badge/Status-Development%20Paused-yellow?style=for-the-badge)](#-development-status)

</div>

---

# 🖥️ What is EDORA OS?

**EDORA OS** is a custom operating system simulator written in **C++**.

It is designed to simulate the experience of using a real operating system while remaining completely safe inside its own virtual filesystem.

EDORA OS includes:

* 🖥️ Custom shell
* 💾 Virtual drives
* 📁 Virtual filesystem
* 🔐 User authentication
* 👑 Root / sudo system
* 📝 Text editor
* 🔢 Binary editor
* 🧩 EDO file system
* 🌐 Network ping
* 🎮 Built-in game
* ⚙️ Kernel simulation
* 📊 System information
* 🔄 Reboot & shutdown simulation

> **EDORA OS does not modify your real Windows filesystem.**

---

# ✨ Features

### 💻 EDORA Shell

A custom command-line shell with a Linux-inspired interface.

```text
user@edora:C:\system$
```

Root mode:

```text
root@edora:C:\system#
```

---

### 💾 Virtual Drives

EDORA OS provides simulated drives:

```text
C:\
D:\
E:\
```

Example:

```text
C:\system
D:\games
E:\backup
```

The virtual filesystem is stored inside:

```text
EDORA_DRIVES/
```

---

### 🔐 Authentication System

EDORA OS contains a persistent login system.

Accounts are stored inside:

```text
C:\system\users.sys
```

Supported features:

```text
login
logout
passwd
sudo
root
```

Example:

```text
user@edora:C:\> sudo

[sudo] password for user: ******
Authentication successful.
You are now root.

root@edora:C:\#
```

---

# 📦 Command List

```text
================ EDORA OS COMMANDS ================

[BASIC]
  help          Show available commands
  clear         Clear screen
  whoami        Show current user
  pwd           Show current path

[FILESYSTEM]
  drives        Show available drives
  ls            List directory
  dir            List directory
  cd             Change directory
  mkdir         Create directory
  touch         Create file
  rm            Delete file/directory
  cat            Read file

[APPLICATIONS]
  notepad       Text editor
  bin           Binary editor
  binread       Read binary file
  binhex        Show hexadecimal
  edo           EDO editor
  edoread       Read EDO file
  edoraw        Show raw EDO file
  game          Start game

[NETWORK]
  ping          Network ping

[SYSTEM]
  neofetch      System information
  sysinfo       Detailed system info
  date          Current date
  time          Current time

[SECURITY]
  sudo          Enter root mode
  root          Show root status
  passwd        Change password
  logout        Logout user
  panic         Kernel panic

[POWER]
  reboot        Restart EDORA OS
  shutdown      Shutdown EDORA OS

====================================================
```

---

# 🧱 Project Architecture

```text
EDORA-OS/
│
├── main.cpp
├── edora.h
├── CMakeLists.txt
│
├── kernel/
│   ├── kernel.cpp
│   └── kernel.h
│
├── shell/
│   ├── shell.cpp
│   └── shell.h
│
├── filesystem/
│   ├── filesystem.cpp
│   └── filesystem.h
│
├── commands/
│   ├── basic.cpp
│   ├── basic.h
│   ├── file.cpp
│   ├── file.h
│   ├── system.cpp
│   ├── system.h
│   ├── security.cpp
│   └── security.h
│
├── apps/
│   ├── notepad.cpp
│   ├── notepad.h
│   ├── binary.cpp
│   ├── binary.h
│   ├── edo.cpp
│   ├── edo.h
│   ├── game.cpp
│   └── game.h
│
├── network/
│   ├── ping.cpp
│   └── ping.h
│
└── login/
    ├── login.cpp
    └── login.h
```

---

# 🚀 Build

### Requirements

* C++17 compiler
* CMake 3.16+
* Windows
* MinGW / GCC or another compatible compiler

### Build

```bash
cmake -S . -B build
cmake --build build
```

The executable will be generated inside the build directory.

---

# ▶️ Running EDORA OS

After building:

```bash
EDORA-OS.exe
```

On the first launch, EDORA OS creates the virtual environment and asks you to create an account.

Example:

```text
============================================
              EDORA OS LOGIN
============================================

No account found.
Create the first EDORA account.

============================================
              CREATE ACCOUNT
============================================

Username: louie
Password: ******
Confirm : ******

[ OK ] Account created.
```

---

# 🗂️ Virtual Filesystem

EDORA OS creates its own isolated filesystem:

```text
EDORA_DRIVES/
│
├── C/
│   ├── system/
│   │   ├── kernel.sys
│   │   ├── config.sys
│   │   ├── users.sys
│   │   ├── security.sys
│   │   ├── services.sys
│   │   ├── version.sys
│   │   └── boot.log
│   │
│   └── programs/
│
├── D/
│   ├── games/
│   └── data/
│
└── E/
    └── backup/
```

EDORA commands operate only inside this virtual environment.

---

# 🛡️ Security

EDORA OS has a simple privilege system:

```text
USER
 │
 └── sudo
      │
      ▼
ROOT
```

User mode:

```text
user@edora:C:\$
```

Root mode:

```text
root@edora:C:\#
```

Dangerous system operations are simulated rather than being allowed to destroy the host operating system.

---

# ⚙️ System Information

Run:

```text
neofetch
```

Example:

```text
       EDORA OS
       -------------------------
       OS       : EDORA OS
       Version  : 1.0
       Kernel   : 1.0
       Shell    : 1.0
       User     : louie
       Drive    : C:
       Path     : C:\system
       Mode     : USER
```

---

# 🎮 Built-in Applications

EDORA OS also contains several small applications.

### 📝 Notepad

```text
notepad
```

Create and save real files inside the EDORA virtual filesystem.

### 🔢 Binary Editor

```text
bin
binread
binhex
```

### 🧩 EDO Editor

```text
edo
edoread
edoraw
```

### 🎮 Game

```text
game
```

---

# 🧠 Technologies

EDORA OS is built with:

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge\&logo=cplusplus\&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-Build-064F8C?style=for-the-badge\&logo=cmake\&logoColor=white)
![Filesystem](https://img.shields.io/badge/std%3A%3Afilesystem-Virtual%20FS-444444?style=for-the-badge)
![Windows](https://img.shields.io/badge/Windows-Supported-0078D6?style=for-the-badge\&logo=windows\&logoColor=white)

</div>

---

# 📌 Development Status

**EDORA OS v1.0** is currently considered the first stable release of the project.

Development is currently **paused**.

The project may return in a future version with more advanced features such as:

```text
EDORA OS 2.0
├── Desktop GUI
├── Window manager
├── Better filesystem
├── Process manager
├── More applications
├── Improved security
└── More system utilities
```

---

# 📜 Version

```text
EDORA OS       : 1.0
EDORA Kernel   : 1.0
EDORA Shell    : 1.0
```

---

# ❤️ Credits

<div align="center">

### MADE BY XIAO LOUIE

**A 12-year-old programmer**

💻 C++ Developer
🐧 Linux Enthusiast
⚙️ EDORA OS Creator
🚀 EDORA STUDIO

<br>

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0072ff,100:00c6ff&height=120&section=footer&animation=fadeIn" width="100%"/>

**EDORA OS — Build. Learn. Create.**

</div>
