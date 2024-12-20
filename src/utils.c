#define _XOPEN_SOURCE
#include <time.h>
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

void initializeSystem() {
    // Create data directory if it doesn't exist
    system("mkdir -p data");
    
    // Create backup directory if it doesn't exist
    system("mkdir -p data/backup");
}

time_t parseDate(const char *dateStr) {
    struct tm tm = {0};
    strptime(dateStr, "%Y-%m-%d", &tm);
    return mktime(&tm);
}

char* formatDate(time_t timestamp) {
    static char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&timestamp));
    return buffer;
}

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

