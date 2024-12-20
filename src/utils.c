/*
 * =====================================================================================
 * File: utils.c
 * Description: Provides utility functions for system operations, including 
 *              system initialization, date handling, user input validation, 
 *              and buffer clearing. These utilities simplify common tasks 
 *              for more efficient system development.
 *
 * Author: Chiemezie Agbo
 * Date: 20-12-2024
 * Version: 1.0
 * =====================================================================================
 */

#define _XOPEN_SOURCE
#include <time.h>
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/**
 * @brief Initializes the system by creating necessary directories
 */
void initializeSystem() {
    // Create data directory if it doesn't exist
    system("mkdir -p data");
    
    // Create backup directory if it doesn't exist
    system("mkdir -p data/backup");
}

/**
 * @brief Parses a date string into a time_t value
 * @param dateStr The date string to parse (format: YYYY-MM-DD)
 * @return time_t The parsed date as a time_t value
 */
time_t parseDate(const char *dateStr) {
    struct tm tm = {0};
    strptime(dateStr, "%Y-%m-%d", &tm);
    return mktime(&tm);
}

/**
 * @brief Formats a time_t value into a date string
 * @param timestamp The time_t value to format
 * @return char* The formatted date string (format: YYYY-MM-DD)
 */
char* formatDate(time_t timestamp) {
    static char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&timestamp));
    return buffer;
}


/**
 * @brief In utils.c or another source file
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Validates and gets an integer input within a specified range
 * @param min The minimum allowed value
 * @param max The maximum allowed value
 * @return int The validated input
 */
int validateIntInput(int min, int max) {
    int input;
    char buffer[100];
    
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        
        if (sscanf(buffer, "%d", &input) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        
        if (input < min || input > max) {
            printf("Input out of range. Please enter a number between %d and %d.\n", min, max);
            continue;
        }
        
        return input;
    }
}

/**
 * @brief Validates and gets a double input within a specified range
 * @param min The minimum allowed value
 * @param max The maximum allowed value
 * @return double The validated input
 */
double validateDoubleInput(double min, double max) {
    double input;
    char buffer[100];
    
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        
        if (sscanf(buffer, "%lf", &input) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        
        if (input < min || input > max) {
            printf("Input out of range. Please enter a number between %.2f and %.2f.\n", min, max);
            continue;
        }
        
        return input;
    }
}

/**
 * @brief Validates and gets a string input
 * @param output The buffer to store the validated input
 * @param maxLength The maximum allowed length of the input
 * @param prompt The prompt to display to the user
 */
void validateStringInput(char *output, int maxLength, const char *prompt) {
    char buffer[1000];
    
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = 0;
        
        if (strlen(buffer) == 0) {
            printf("Input cannot be empty. Please try again.\n");
            continue;
        }
        
        if (strlen(buffer) > (size_t)maxLength) {
            printf("Input too long. Maximum length is %d characters. Please try again.\n", maxLength);
            continue;
        }
        
        strcpy(output, buffer);
        break;
    }
}

/**
 * @brief Validates and gets a date input
 * @param output The buffer to store the validated date string
 * @return int 1 if input is valid, 0 otherwise
 */
int validateDateInput(char *output) {
    char buffer[11];
    struct tm tm;
    
    while (1) {
        printf("Enter date (YYYY-MM-DD): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = 0;
        
        if (strlen(buffer) != 10) {
            printf("Invalid date format. Please use YYYY-MM-DD.\n");
            continue;
        }
        
        if (strptime(buffer, "%Y-%m-%d", &tm) == NULL) {
            printf("Invalid date. Please enter a valid date in the format YYYY-MM-DD.\n");
            continue;
        }
        
        strcpy(output, buffer);
        return 1;
    }
}

