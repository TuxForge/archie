# Archie
Fast & easy package management for Arch Linux.

## Dependencies
Make sure you have git, gcc or llvm.
```sh
pacman -S git gcc # or clang (llvm)
```
## Installation
Paste the following commands in a terminal
```sh
$ git clone https://github.com/zackychann/archie
$ cd archie
$ sudo make install
```
**Check notes for more information.**
## Usage
```
    printf("u - Update the system\n");
    printf("i - Install a package\n");
    printf("r - Remove a package\n");
    printf("p - Purge a package\n");
    printf("c - Clean cache\n");
    printf("o - Clean orphaned packages\n");
    printf("s - Search for a package\n");
    printf("h - Help\n");
    printf("q - Quit\n");
