# PortScanner

## Desciption
- This is a simple port scanner using the [QTFramework](https://www.qt.io/product/framework).
- This project was created to learn about basic networking with QT.
- This project was made public as part of an effort to document more of my work.
- Scans a given range of ports on a target IP address concurrently, utilizing QFutureSynchronizer and QFutures.

## Installation
- To compile the program ensure you have a C++ compiler or an IDE with C++ support, personally I use [g++](https://gcc.gnu.org/) compiler.
- Additionally ensure you have the QT Framework installed and properly linked to your environment as well.
- For example to install the dependies with the dnf package manager:
```bash
dnf install g++ qt5-qtbase-devel
```
- To compile:
```bash
g++ -I/Path/To/qt5-qtbase -o port-scanner main.cpp QtPortScanner.cpp
```

## Usage
- When ran, the user will be prompted to enter the the target IP address and the number of ports to scan, beginning from port 0.
- NOTE: no command line arguments are used. 
