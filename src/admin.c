/*
 * =====================================================================================
 * File: admin.c
 * Description: This file contains the implementation of administrative functions for
 *              managing user accounts, backups, and system data. The functions include
 *              displaying the admin menu, adding and viewing users, changing user
 *              passwords, creating backups of system data, and restoring data from
 *              backups.
 *
 *              The system stores user data in a binary file (data/users.dat) and
 *              supports backup and restoration of multiple system data files.
 *
 * Author: Chiemezie Agbo
 * Date: 20-12-2024
 * Version: 1.0
 *
 * =====================================================================================
 */

#include "../include/admin.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define USERS_FILE "data/users.dat"
#define BACKUP_DIR "data/backup/"

/**
 * @brief Displays the admin menu and handles user choices
 */
void adminMenu() {
    int choice;
    do {
        printf("\033[1;31m");
        printf("╔════════════════════════════╗\n");
        printf("║     Admin Management       ║\n");
        printf("╠════════════════════════════╣\n");
        printf("║ 1. Add User                ║\n");
        printf("║ 2. View Users              ║\n");
        printf("║ 3. Change User Password    ║\n");
        printf("║ 4. Backup Data             ║\n");
        printf("║ 5. Restore Data            ║\n");
        printf("║ 6. Back to Main Menu       ║\n");
        printf("╚════════════════════════════╝\n");
        printf("\033[0m");
        printf("Enter your choice: ");
        choice = validateIntInput(1, 6);

        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                viewUsers();
                break;
            case 3:
                {
                    char username[MAX_USERNAME_LENGTH];
                    validateStringInput(username, MAX_USERNAME_LENGTH, "Enter username to change password: ");
                    changePassword(username);
                }
                break;
            case 4:
                backupData();
                break;
            case 5:
                restoreData();
                break;
            case 6:
                return;
        }
    } while (1);
}

/**
 * @brief Adds a new user to the system
 */
void addUser() {
    User user;
    validateStringInput(user.username, MAX_USERNAME_LENGTH, "Enter username: ");
    validateStringInput(user.password, MAX_PASSWORD_LENGTH, "Enter password: ");
    printf("Is this user an admin? (1 for Yes, 0 for No): ");
    user.is_admin = validateIntInput(0, 1);

    FILE *file = fopen(USERS_FILE, "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&user, sizeof(User), 1, file);
    fclose(file);

    printf("User added successfully!\n");
}

/**
 * @brief Displays all users in the system
 */
void viewUsers() {
    FILE *file = fopen(USERS_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    User user;
    printf("\033[1;34m");
    printf("%-20s %-10s\n", "Username", "Admin");
    printf("==============================\n");
    printf("\033[0m");
    while (fread(&user, sizeof(User), 1, file)) {
        printf("%-20s %-10s\n", user.username, user.is_admin ? "Yes" : "No");
    }

    fclose(file);
}

/**
 * @brief Creates a backup of the system data
 */
void backupData() {
    char timestamp[20];
    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", localtime(&now));

    char command[256];
    snprintf(command, sizeof(command), "mkdir -p %s%s", BACKUP_DIR, timestamp);
    system(command);

    const char *files[] = {"inventory.dat", "orders.dat", "customers.dat", "users.dat"};
    int num_files = sizeof(files) / sizeof(files[0]);

    for (int i = 0; i < num_files; i++) {
        snprintf(command, sizeof(command), "cp data/%s %s%s/", files[i], BACKUP_DIR, timestamp);
        system(command);
    }

    printf("Backup created successfully in %s%s/\n", BACKUP_DIR, timestamp);
}

/**
 * @brief Restores system data from a backup
 */
void restoreData() {
    char backup_dir[256];
    validateStringInput(backup_dir, sizeof(backup_dir), "Enter the backup directory name (YYYYMMDD_HHMMSS): ");

    char full_backup_path[512];
    snprintf(full_backup_path, sizeof(full_backup_path), "%s%s/", BACKUP_DIR, backup_dir);

    const char *files[] = {"inventory.dat", "orders.dat", "customers.dat", "users.dat"};
    int num_files = sizeof(files) / sizeof(files[0]);

    for (int i = 0; i < num_files; i++) {
        char command[512];
        snprintf(command, sizeof(command), "cp %.200s%.50s data/", full_backup_path, files[i]);
        system(command);
    }

    printf("Data restored successfully from %s\n", full_backup_path);
}

/**
 * @brief Authenticates a user and returns their access level
 * @param username The username to authenticate
 * @param password The password to authenticate
 * @return int 0 for failed login, 1 for regular user, 2 for admin
 */
int loginUser(char *username, char *password) {
    FILE *file = fopen(USERS_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            return user.is_admin ? 2 : 1; // 2 for admin, 1 for regular user
        }
    }

    fclose(file);
    return 0; // Login failed
}

/**
 * @brief Changes the password for a given user
 * @param username The username of the user whose password is to be changed
 */
void changePassword(char *username) {
    FILE *file = fopen(USERS_FILE, "rb+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    User user;
    int found = 0;
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.username, username) == 0) {
            validateStringInput(user.password, MAX_PASSWORD_LENGTH, "Enter new password: ");
            fseek(file, -sizeof(User), SEEK_CUR);
            fwrite(&user, sizeof(User), 1, file);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("Password changed successfully!\n");
    } else {
        printf("User not found!\n");
    }
}

