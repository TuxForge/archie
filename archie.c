#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdarg.h>

#define MAX_INPUT_LENGTH 256
#define COMMAND_BUFFER_SIZE 512

int check_archie_file() {
    const char *home = getenv("HOME");
    char path[MAX_INPUT_LENGTH];
    snprintf(path, sizeof(path), "%s/.archie-use-paru", home);
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

int check_package_manager() {
    if (check_archie_file()) {
        return 2;
    }
    if (system("command -v yay > /dev/null 2>&1") == 0) {
        return 1;
    }
    if (system("command -v paru > /dev/null 2>&1") == 0) {
        return 2;
    }
    return 0;
}

int check_git() {
    return system("command -v git > /dev/null 2>&1") == 0;
}

void install_git() {
    printf("Installing git...\n");
    system("sudo pacman -S --noconfirm git");
}

void install_yay() {
    printf("Installing yay...\n");
    system("mkdir -p $HOME/.cache/archie/made-by-gurov && "
           "cd $HOME/.cache/archie/made-by-gurov && "
           "git clone https://aur.archlinux.org/yay-bin.git && "
           "cd yay-bin && "
           "makepkg -scCi && "
           "cd && "
           "rm -rf $HOME/.cache/archie/");
    printf("Installation of yay is complete. Please restart your shell and relaunch the script.\n");
}

void execute_command(const char *format, ...) {
    char command[COMMAND_BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(command, sizeof(command), format, args);
    va_end(args);
    system(command);
}

void update_system(const char *package_manager) {
    execute_command("%s -Syu", package_manager);
}

void install_package(const char *package_manager, const char *package) {
    execute_command("%s -S %s", package_manager, package);
}

void remove_package(const char *package_manager, const char *package) {
    execute_command("%s -R %s", package_manager, package);
}

void purge_package(const char *package_manager, const char *package) {
    execute_command("%s -Rns %s", package_manager, package);
}

void clean_cache(const char *package_manager) {
    execute_command("%s -Sc", package_manager);
}

void clean_orphans(const char *package_manager) {
    execute_command("%s -Rns $(pacman -Qdtq)", package_manager);
}

void search_package(const char *package_manager, const char *package) {
    execute_command("%s -Ss %s", package_manager, package);
}

void display_help() {
    printf("Available options are:\n");
    printf("u - Update the system\n");
    printf("i - Install a package\n");
    printf("r - Remove a package\n");
    printf("p - Purge a package\n");
    printf("c - Clean cache\n");
    printf("o - Clean orphaned packages\n");
    printf("s - Search for a package\n");
    printf("h - Help\n");
    printf("q - Quit\n");
}

void prompt_install_yay() {
    char response[10];
    printf("Error: Neither yay nor paru is installed.\n");
    sleep(3);
    printf("Do you want to install yay? (y/n): ");
    scanf("%9s", response);

    if (strcmp(response, "y") == 0 || strcmp(response, "yes") == 0) {
        if (!check_git()) {
            install_git();
        }
        install_yay();
    } else {
        printf("Exiting the program.\n");
        exit(0);
    }
}

void get_input(char *input, const char *prompt) {
    printf("%s", prompt);
    if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        exit(1);
    }
    input[strcspn(input, "\n")] = 0;

    if (strlen(input) == 0) {
        printf("Please input something, not air.\n");
        get_input(input, prompt);
    }
}

int is_valid_command(char command) {
    return strchr("uirpcoshq", command) != NULL;
}

void handle_command(const char *input, const char *package_manager) {
    char choice = input[0];
    if (strlen(input) == 1 && is_valid_command(choice)) {
        char package[MAX_INPUT_LENGTH];
        switch (choice) {
            case 'u':
                update_system(package_manager);
                break;
            case 'i':
                get_input(package, "Enter package name to install: ");
                install_package(package_manager, package);
                break;
            case 'r':
                get_input(package, "Enter package name to remove: ");
                remove_package(package_manager, package);
                break;
            case 'p':
                get_input(package, "Enter package name to purge: ");
                purge_package(package_manager, package);
                break;
            case 'c':
                clean_cache(package_manager);
                break;
            case 'o':
                clean_orphans(package_manager);
                break;
            case 's':
                get_input(package, "Enter package name to search: ");
                search_package(package_manager, package);
                break;
            case 'h':
                display_help();
                break;
            case 'q':
                exit(0);
            default:
                fprintf(stderr, "Invalid option. Please type a valid option.\n");
        }
    } else {
        fprintf(stderr, "Invalid input. Please input a valid command.\n");
        display_help();
    }
}

void display_version() {
    printf("    __     \n"
           " .:--.'.   Archie v1.1 - Fast & easy package management for Arch Linux\n"
           "/ |   \\ |  Written in C, powered by YAY and pacman.\n"
           "`\" __ | |  This program may be freely redistributed under\n"
           " .'.''| |  the terms of the GNU General Public License.\n"
           "/ /   | |_ Coded with love by Gurov and maintained by scklss & Keiran\n"
           "\\ \\._,\\ '/ Have fun <3\n"
           " `--'  `\" \n");
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--version") == 0) {
        display_version();
        return 0;
    }

    char input[MAX_INPUT_LENGTH];
    const char *package_manager;

    int pm_check = check_package_manager();
    if (pm_check == 1) {
        package_manager = "yay";
    } else if (pm_check == 2) {
        package_manager = "paru";
    } else {
        prompt_install_yay();
        return 1;
    }

    printf("Welcome to Archie, type \"h\" for help\n");

    while (1) {
        get_input(input, "$ ");
        handle_command(input, package_manager);
    }

    return 0;
}
