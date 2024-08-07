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
    git clone https://github.com/zackychann/archie.git
    cd archie
    ```

2. **Compile the program:**

    ```sh
    make
    ```

3. **Install the binary to `/usr/bin`** (requires root permissions):

    ```sh
    sudo make install
    ```

4. **AUR**

    Archie is also available on the [AUR](https://aur.archlinux.org/packages/archie). You can install it using your preferred AUR helper. For example, with `yay`:

    ```sh
    yay -S archie
    ```

    Note: if Archie fails to upgrade to a newer version, try cleaning cache using Archie and installing it again, example given:

   ```sh
   yay -Scc --noconfirm && yay -S archie --noconfirm
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

- `--exec <command>` - Execute a specific command without entering the interactive prompt. The `<command>` can be one of the following:

   - `u` - Update the system
   - `i` - Install a package
   - `r` - Remove a package
   - `p` - Purge a package
   - `c` - Clean cache
   - `o` - Clean orphaned packages
   - `s` - Search for a package
   - `h` - Display help

   Example:

   ```sh
   archie --exec u
   ```

   This command will update the system directly from the command line. If you run `archie --exec` without specifying a command, you will be prompted to enter a command interactively.

- `--version` - Display the version information:

    ```sh
    archie --version
    ```

    Output:

    ```
        __     Archie v1.3 - Fast & easy package management for Arch Linux
     .:--.'.   Written in C, powered by YAY and Pacman.
    / |   \ |  paru v2.0.3 - libalpm v14.0.0
    `" __ | |  
     .'.''| |  
    / /   | |_ This program may be freely redistributed under the terms of the GNU General Public License.
    \ \._,\ '/ Created & maintained by Gurov
     `--'  `"  With the help of scklss and Keiran
    ```

## Dependencies

- `gcc` - GNU Compiler Collection
- `yay` or `paru` - AUR helpers for Arch Linux
- `git` - For installing `yay` if it is not already installed
- `readline` - A library for command-line input, probably preinstalled
- `ncurses` - A library for text-based user interfaces, probably preinstalled

## Notes
Archie uses yay by default, but if you only have paru installed it'll use it. If you have both and you want to use `paru` instead of `yay` create a file in `$HOME` called `.archie-use-paru`, and it will install `paru` instead of `yay`

```sh
touch $HOME/.archie-use-paru
```

## License

This program is licensed under the GNU General Public License. See the [LICENSE](https://gurov.likes.cat/6ppr9lvz.mp4) file for details.
