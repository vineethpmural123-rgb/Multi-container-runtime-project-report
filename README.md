# MiniDocker-OS

This project implements a lightweight container runtime similar to Docker using Linux namespaces and a kernel module for memory monitoring and scheduling analysis.

---

## 👨‍💻 1. Team Information

| Name                     | SRN           |
| ------------------------ | ------------- |
| SIDDU SANGANNA SHIRASAGI | PES1UG25CS846 |
| Shravanakumar Patil      | PES1UG24CS692 |

---

## ⚙️ 2. Build, Load, and Run Instructions

### 📌 Prerequisites

Ubuntu 22.04 or 24.04 VM with **Secure Boot OFF**

```bash
sudo apt update
sudo apt install -y build-essential linux-headers-$(uname -r)
```

**Explanation:**

* `apt update` → updates package list
* `build-essential` → installs compiler tools (gcc, make)
* `linux-headers` → required to build kernel module

---

### 🔨 Build

```bash
cd boilerplate
make
```

**Explanation:**

* Compiles the project
* Generates:

  * `engine` (container runtime)
  * `monitor.ko` (kernel module)
  * `memory_hog`, `cpu_hog`, `io_pulse` (test programs)

---

### 📦 Prepare Root Filesystem

```bash
mkdir rootfs-base
wget https://dl-cdn.alpinelinux.org/alpine/v3.20/releases/x86_64/alpine-minirootfs-3.20.3-x86_64.tar.gz
tar -xzf alpine-minirootfs-3.20.3-x86_64.tar.gz -C rootfs-base
```

**Explanation:**

* Downloads minimal Alpine Linux filesystem
* Used as container environment

---

### 🧩 Load Kernel Module

```bash
sudo insmod monitor.ko
ls /dev/container_monitor
```

**Explanation:**

* Loads kernel module into kernel
* Enables memory monitoring for containers

---

### 🚀 Start Supervisor

```bash
sudo ./engine supervisor ./rootfs-base
```

**Explanation:**

* Starts container manager (supervisor)
* Handles container lifecycle and prevents zombie processes

👉 Keep this running and open another terminal

---

### 🐳 Launch Containers

```bash
cp -a ./rootfs-base ./rootfs-alpha
cp -a ./rootfs-base ./rootfs-beta

sudo ./engine start alpha ./rootfs-alpha /bin/sh --soft-mib 48 --hard-mib 80
sudo ./engine start beta  ./rootfs-beta  /bin/sh --soft-mib 64 --hard-mib 96
```

**Explanation:**

* Creates container instances
* Applies memory limits (soft & hard)

---

### 🖥️ CLI Commands

```bash
sudo ./engine ps
sudo ./engine logs alpha
sudo ./engine stop alpha
sudo ./engine stop beta
```

**Explanation:**

* `ps` → list containers
* `logs` → view output
* `stop` → terminate container

---

### ▶️ Run Container and Wait

```bash
cp -a ./rootfs-base ./rootfs-test
sudo ./engine run test ./rootfs-test "echo hello from container"
sudo ./engine logs test
```

**Explanation:**

* Runs container and waits for completion
* Useful for short tasks

---

### 🧠 Memory Limit Test

```bash
cp -a ./rootfs-base ./rootfs-mem
cp ./memory_hog ./rootfs-mem/

sudo ./engine run memtest ./rootfs-mem /memory_hog --soft-mib 10 --hard-mib 20
sudo dmesg | tail -10
```

**Explanation:**

* Tests memory usage
* Soft limit → warning
* Hard limit → container killed

---

### ⚡ Scheduler Experiment

```bash
cp -a ./rootfs-base ./rootfs-c1
cp -a ./rootfs-base ./rootfs-c2

cp ./cpu_hog ./rootfs-c1/
cp ./cpu_hog ./rootfs-c2/

sudo ./engine start c1 ./rootfs-c1 "/cpu_hog 20" --nice 10
sudo ./engine start c2 ./rootfs-c2 "/cpu_hog 20" --nice -5

sleep 22

sudo ./engine logs c1
sudo ./engine logs c2
```

**Explanation:**

* Demonstrates CPU scheduling
* Lower nice value → higher priority

---

### 🧹 Cleanup

```bash
# Stop supervisor using Ctrl+C
sudo rmmod monitor
sudo dmesg | tail -5
```

**Explanation:**

* Removes kernel module
* Cleans system

---

### ✅ CI Safe Build

```bash
make -C boilerplate ci
```

---

## 📸 3. Demo Screenshots

Add screenshots in `screenshot/` folder:

```md
![Screenshot](screenshot/image1.png)
```

---

## 🧠 4. Engineering Concepts

* Process Isolation using namespaces
* Inter-process communication (pipes & sockets)
* Memory monitoring using kernel module
* Scheduling using Linux CFS

---

## ⚖️ 5. Key Features

* Lightweight container runtime
* Multi-container support
* Memory limits (soft & hard)
* Logging system
* CLI interface

---

## 🚀 Conclusion

This project demonstrates core OS concepts including:

* Containers
* Kernel modules
* Scheduling
* Memory management

A complete mini Docker-like system built from scratch.
