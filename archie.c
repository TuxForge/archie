#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 256
#define COMMAND_BUFFER_SIZE 512

int check_package_manager() {
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

void update_system(const char *package_manager) {
    char command[COMMAND_BUFFER_SIZE];
    snprintf(command, sizeof(command), "%s -Syu", package_manager);
    system(command);
}

void install_package(const char *package_manager, const char *package) {
    char command[COMMAND_BUFFER_SIZE];
    snprintf(command, sizeof(command), "%s -S %s", package_manager, package);
    system(command);
}

void remove_package(const char *package_manager, const char *package) {
    char command[COMMAND_BUFFER_SIZE];
    snprintf(command, sizeof(command), "%s -R %s", package_manager, package);
    system(command);
}

void purge_package(const char *package_manager, const char *package) {
    char command[COMMAND_BUFFER_SIZE];
    snprintf(command, sizeof(command), "%s -Rns %s", package_manager, package);
    system(command);
}

void clean_cache(const char *package_manager) {
    char command[COMMAND_BUFFER_SIZE];
    snprintf(command, sizeof(command), "%s -Sc", package_manager);
    system(command);
}

void clean_orphans(const char *package_manager) {
    char command[COMMAND_BUFFER_SIZE];
    snprintf(command, sizeof(command), "%s -Rns $(pacman -Qdtq)", package_manager);
    system(command);
}

void search_package(const char *package_manager, const char *package) {
    char command[COMMAND_BUFFER_SIZE];
    snprintf(command, sizeof(command), "%s -Ss %s", package_manager, package);
    system(command);
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
    scanf("%s", response);

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
    fgets(input, MAX_INPUT_LENGTH, stdin);
    input[strcspn(input, "\n")] = 0;

    if (strlen(input) == 0) {
        printf("Please input something, not air.\n");
        get_input(input, prompt);
    }
}

int is_valid_command(char command) {
    return command == 'u' || command == 'i' || command == 'r' ||
    command == 'p' || command == 'c' || command == 'o' ||
    command == 's' || command == 'h' || command == 'q';
}

void handle_command(const char *input, const char *package_manager) {
    char choice = input[0];
    if (strlen(input) == 1 && is_valid_command(choice)) {
        switch (choice) {
            case 'u':
                update_system(package_manager);
                break;
            case 'i':
                printf("Enter package name to install: ");
                char package[MAX_INPUT_LENGTH];
                get_input(package, "");
                install_package(package_manager, package);
                break;
            case 'r':
                printf("Enter package name to remove: ");
                get_input(package, "");
                remove_package(package_manager, package);
                break;
            case 'p':
                printf("Enter package name to purge: ");
                get_input(package, "");
                purge_package(package_manager, package);
                break;
            case 'c':
                clean_cache(package_manager);
                break;
            case 'o':
                clean_orphans(package_manager);
                break;
            case 's':
                printf("Enter package name to search: ");
                get_input(package, "");
                search_package(package_manager, package);
                break;
            case 'h':
                display_help();
                break;
            case 'q':
                exit(0);
            default:
                printf("Invalid option. Please correct your grammar and type a valid option.\n");
        }
    } else {
        if (is_valid_command(choice)) {
            printf("Did you mean \"%c\"? (y/n): ", choice);
            char response[10];
            get_input(response, "");
            if (strcmp(response, "y") == 0 || strcmp(response, "yes") == 0) {
                switch (choice) {
                    case 'u':
                        update_system(package_manager);
                        break;
                    case 'i':
                        printf("Enter package name to install: ");
                        char package[MAX_INPUT_LENGTH];
                        get_input(package, "");
                        install_package(package_manager, package);
                        break;
                    case 'r':
                        printf("Enter package name to remove: ");
                        get_input(package, "");
                        remove_package(package_manager, package);
                        break;
                    case 'p':
                        printf("Enter package name to purge: ");
                        get_input(package, "");
                        purge_package(package_manager, package);
                        break;
                    case 'c':
                        clean_cache(package_manager);
                        break;
                    case 'o':
                        clean_orphans(package_manager);
                        break;
                    case 's':
                        printf("Enter package name to search: ");
                        get_input(package, "");
                        search_package(package_manager, package);
                        break;
                    case 'h':
                        display_help();
                        break;
                    case 'q':
                        exit(0);
                    default:
                        printf("Invalid option. Please correct your grammar and type a valid option.\n");
                }
            } else {
                display_help();
            }
        } else {
            printf("Invalid input. Please input a valid command.\n");
            display_help();
        }
    }
}

void display_version() {
    printf("    __     \n"
    " .:--.'.   Archie v1.1 - Fast & easy package management for Arch Linux\n"
    "/ |   \\ |  Written in C, powered by YAY and pacman.\n"
    "`\" __ | |  This program may be freely redistributed under\n"
    " .'.''| |  the terms of the GNU General Public License.\n"
    "/ /   | |_ Coded with love by Gurov and maintained by scklss AKA skulls\n"
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
