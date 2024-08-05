# Archie - Fast & Easy Package Management for Arch Linux

Archie is a command-line tool for managing packages on Arch Linux, providing a simple interface for common package management tasks using `yay` or `paru`.

## Features

- Update the system
- Install packages
- Remove packages
- Purge packages
- Clean cache
- Clean orphaned packages
- Search for packages

## Installation

1. **Clone the repository:**

    ```sh
    git clone https://github.com/yourusername/archie.git
    cd archie
    ```

2. **Compile the program:**

    ```sh
    gcc -o archie archie.c
    ```

3. **Run the program:**

    ```sh
    ./archie
    ```

## Usage

When you run `archie`, you will see the following prompt:

    ```
    Welcome to Archie, type "h" for help
    $
    ```

You can then use the following commands:

- `u` - Update the system
- `i` - Install a package
- `r` - Remove a package
- `p` - Purge a package
- `c` - Clean cache
- `o` - Clean orphaned packages
- `s` - Search for a package
- `h` - Display help
- `q` - Quit the application

### Example

To install a package, type `i` and follow the prompt:

    ```
    $ i
    Enter package name to install:
    ```

## Command-Line Arguments

You can also use the following command-line argument:

- `--version` - Display the version information:

    ```sh
    ./archie --version
    ```

    Output:

    ```
        __     
     .:--.'.   Archie v1.1 - Fast & easy package management for Arch Linux
    / |   \ |  Written in C, powered by YAY and pacman.
    `" __ | |  This program may be freely redistributed under
     .'.''| |  the terms of the GNU General Public License.
    / /   | |_ Coded with love by Gurov and maintained by scklss AKA skulls
    \ \._,\ '/ Have fun <3
     `--'  `" 
    ```

## Dependencies

- `gcc` - GNU Compiler Collection
- `yay` or `paru` - AUR helpers for Arch Linux
- `git` - For installing `yay` if it is not already installed