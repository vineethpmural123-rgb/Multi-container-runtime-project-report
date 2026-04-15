MiniDocker-OS

This project implements a lightweight container runtime similar to Docker using Linux namespaces and a kernel module for memory monitoring and scheduling analysis.
## 👨‍💻 1. Team Information

| Name | SRN |
|------|-----|
| Shantinath Baligra | PES1UG25CS691 |
| Vineeth | PES1UG24CS698 |
## 2. Build, Load, and Run Instructions
### 📌 Prerequisites

Ubuntu 22.04 or 24.04 VM with Secure Boot OFF.

Install required packages:

```bash
sudo apt update
sudo apt install -y build-essential linux-headers-$(uname -r)
### Build
```bash
cd boilerplate
make

