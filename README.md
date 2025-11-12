# 🧠 Markix — A Modular Educational Operating System

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Architecture](https://img.shields.io/badge/arch-x86-blue)
![Language](https://img.shields.io/badge/language-C%20%2B%20Assembly-green)

Markix is a modular **educational operating system** designed to demonstrate the internal mechanisms of an OS — from the **bootloader** to **protected mode**, **interrupt handling**, **memory management**, and **process scheduling**.

Developed by **Marco Paviotti**, Markix is inspired by **MINIX** and **Tanenbaum’s educational approach**, focusing on clarity and completeness rather than performance.  
It is written entirely in **C and x86 assembly** and is designed to run on **Bochs** or **QEMU** emulators.

---

## 🧩 Project Overview

Markix is built in incremental stages. Each milestone corresponds to a **Git tag**, and improvements to that module are developed on **dedicated branches**.

| Tag | Component | Description |
|-----|------------|-------------|
| `Bootloader` | Bootloader | Initializes the CPU in real mode, loads the kernel, and switches to protected mode |
| `Interrupts` | Interrupt System | Implements the 8259 PIC, IDT setup, and interrupt service routines (ISRs) |
| `Keyboard` | PS/2 Driver | Handles keyboard input and interrupt handling |
| `Scheduler` | Process Scheduler | Round-robin scheduling and context switching |
| `Paging` | Memory Management | GDT, paging tables, and memory protection setup |
| `FilesystemGRUB` | File System | Basic FAT filesystem and GRUB integration |

Each of these tags represents a development phase; refinements are maintained in associated branches.

---

## ⚙️ Features

- 🧭 **Boots from MBR (floppy/disk image)**
- 🔒 **Switches from real to protected mode**
- ⚡ **PIC8259 remapping and full interrupt handling**
- 🔁 **Round-robin scheduler with context switching**
- 🧮 **Custom `kmalloc` memory allocator**
- ⌨️ **Keyboard and screen I/O support**
- 📦 **Basic FAT filesystem & GRUB compatibility**
- 🧱 **Written from scratch in C + NASM**

---

## 🧱 System Architecture

# 🧠 Markix — A Modular Educational Operating System

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Architecture](https://img.shields.io/badge/arch-x86-blue)
![Language](https://img.shields.io/badge/language-C%20%2B%20Assembly-green)

Markix is a modular **educational operating system** designed to demonstrate the internal mechanisms of an OS — from the **bootloader** to **protected mode**, **interrupt handling**, **memory management**, and **process scheduling**.

Developed by **Marco Paviotti**, Markix is inspired by **MINIX** and **Tanenbaum’s educational approach**, focusing on clarity and completeness rather than performance.  
It is written entirely in **C and x86 assembly** and is designed to run on **Bochs** or **QEMU** emulators.

---

## 🧩 Project Overview

Markix is built in incremental stages. Each milestone corresponds to a **Git tag**, and improvements to that module are developed on **dedicated branches**.

| Tag | Component | Description |
|-----|------------|-------------|
| `Bootloader` | Bootloader | Initializes the CPU in real mode, loads the kernel, and switches to protected mode |
| `Interrupts` | Interrupt System | Implements the 8259 PIC, IDT setup, and interrupt service routines (ISRs) |
| `Keyboard` | PS/2 Driver | Handles keyboard input and interrupt handling |
| `Scheduler` | Process Scheduler | Round-robin scheduling and context switching |
| `Paging` | Memory Management | GDT, paging tables, and memory protection setup |
| `FilesystemGRUB` | File System | Basic FAT filesystem and GRUB integration |

Each of these tags represents a development phase; refinements are maintained in associated branches.

---

## ⚙️ Features

- 🧭 **Boots from MBR (floppy/disk image)**
- 🔒 **Switches from real to protected mode**
- ⚡ **PIC8259 remapping and full interrupt handling**
- 🔁 **Round-robin scheduler with context switching**
- 🧮 **Custom `kmalloc` memory allocator**
- ⌨️ **Keyboard and screen I/O support**
- 📦 **Basic FAT filesystem & GRUB compatibility**
- 🧱 **Written from scratch in C + NASM**


