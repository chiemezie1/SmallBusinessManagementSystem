/*
 * =====================================================================================
 * File: main.c
 * Description: Contains the main entry point for the Small Business Management 
 *              System (SBMS), enabling users to manage inventory, orders, 
 *              customers, finances, and system settings. It includes an admin 
 *              interface for managing users and settings.
 *
 * Author: Chiemezie Agbo
 * Date: 20-12-2024
 * Version: 1.0
 * =====================================================================================
 */

#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "../include/common.h"
#include "../include/admin.h"
#include "../include/inventory.h"
#include "../include/orders.h"
#include "../include/customers.h"
#include "../include/financial.h"
#include "../include/utils.h"

#define USERS_FILE "data/users.dat"

#define CLEAR_SCREEN() printf("\033[H\033[J")

/**
 * @brief Displays the application logo
 */
void displayLogo() {
    printf("\033[1;36m");
    printf("   _____ __  __  _____ _____ \n");
    printf("  / ____|  \\/  |/ ____|  __ \\\n");
    printf(" | (___ | \\  / | (___ | |__) |\n");
    printf("  \\___ \\| |\\/| |\\___ \\|  _  / \n");
    printf("  ____) | |  | |____) | | \\ \\ \n");
    printf(" |_____/|_|  |_|_____/|_|  \\_\\\n");
    printf("\033[0m");
    printf("\nSmall Business Management System\n\n");
}

/**
 * @brief Displays the main menu based on user access level
 * @param is_admin 1 if the user is an admin, 0 otherwise
 */
void displayMenu(int is_admin) {
    printf("\033[1;33m");
    printf("╔════════════════════════════╗\n");
    printf("║           MENU             ║\n");
    printf("╠════════════════════════════╣\n");
    if (is_admin) {
        printf("║ 1. Admin                   ║\n");
    }
    printf("║ 2. Inventory Management    ║\n");
    printf("║ 3. Order Management        ║\n");
    printf("║ 4. Customer Management     ║\n");
    printf("║ 5. Financial Management    ║\n");
    printf("║ 6. Change Password         ║\n");
    printf("║ 7. Logout                  ║\n");
    printf("╚════════════════════════════╝\n");
    printf("\033[0m");
}

/**
 * @brief Displays a loading animation
 */
void displayLoadingAnimation() {
    const char* frames[] = {"|", "/", "-", "\\"};
    for (int i = 0; i < 20; i++) {
        printf("\rLoading %s", frames[i % 4]);
        fflush(stdout);
        struct timespec ts = {0, 100000000};
        nanosleep(&ts, NULL);
    }
    printf("\n");
}

/**
 * @brief The main function of the application
 * @return int 0 on successful execution
 */
int main(void) {
    initializeSystem();
    
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int login_status = 0;

    // Create default admin user if it doesn't exist
    FILE *file = fopen(USERS_FILE, "rb");
    if (file == NULL) {
        file = fopen(USERS_FILE, "wb");
        if (file != NULL) {
            User admin = {"admin", "0000", 1};
            fwrite(&admin, sizeof(User), 1, file);
            fclose(file);
        }
    } else {
        fclose(file);
    }

    while (login_status == 0) {
        validateStringInput(username, MAX_USERNAME_LENGTH, "Enter username: ");
        validateStringInput(password, MAX_PASSWORD_LENGTH, "Enter password: ");
        login_status = loginUser(username, password);
        if (login_status == 0) {
            printf("Invalid username or password. Please try again.\n");
        }
    }

    int choice;
    do {
        CLEAR_SCREEN();
        displayLogo();
        displayMenu(login_status == 2);
        printf("Enter your choice: ");
        choice = validateIntInput(1, 7);

        switch (choice) {
            case 1:
                if (login_status == 2) {
                    displayLoadingAnimation();
                    adminMenu();
                } else {
                    printf("Access denied. Admin privileges required.\n");
                }
                break;
            case 2:
                displayLoadingAnimation();
                inventoryMenu();
                break;
            case 3:
                displayLoadingAnimation();
                orderMenu();
                break;
            case 4:
                displayLoadingAnimation();
                customerMenu();
                break;
            case 5:
                displayLoadingAnimation();
                financialMenu();
                break;
            case 6:
                changePassword(username);
                break;
            case 7:
                printf("Thank you for using SBMS. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        if (choice != 7) {
            printf("Press Enter to continue...");
            getchar();
            getchar();
        }
    } while (choice != 7);

    return 0;
}

