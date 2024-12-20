/*
 * =====================================================================================
 * File: customers.c
 * Description: Implements customer management functions including adding, updating, 
 *              deleting, and searching for customers. The customer data is stored 
 *              in a binary file (data/customers.dat) and accessed through 
 *              read/write operations. Functions also handle generating unique 
 *              customer IDs and managing customer information.
 *
 * Author: Chiemezie Agbo
 * Date: 20-12-2024
 * Version: 1.0
 * =====================================================================================
 */

#include "../include/customers.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define CUSTOMERS_FILE "data/customers.dat"

/**
 * @brief Generates a unique customer ID
 * @return int The generated unique ID
 */
int generateUniqueCustomerId() {
    static int lastId = 0;
    FILE *file = fopen(CUSTOMERS_FILE, "rb");
    if (file != NULL) {
        Customer customer;
        while (fread(&customer, sizeof(Customer), 1, file)) {
            if (customer.id > lastId) {
                lastId = customer.id;
            }
        }
        fclose(file);
    }
    return ++lastId;
}

/**
 * @brief Displays the customer management menu and handles user choices
 */
void customerMenu() {
    int choice;
    do {
        printf("\033[1;33m");
        printf("╔════════════════════════════╗\n");
        printf("║    Customer Management     ║\n");
        printf("╠════════════════════════════╣\n");
        printf("║ 1. Add Customer            ║\n");
        printf("║ 2. Update Customer         ║\n");
        printf("║ 3. Delete Customer         ║\n");
        printf("║ 4. View All Customers      ║\n");
        printf("║ 5. Search Customer         ║\n");
        printf("║ 6. Back to Main Menu       ║\n");
        printf("╚════════════════════════════╝\n");
        printf("\033[0m");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCustomer(NULL);
                break;
            case 2:
                {
                    int id;
                    printf("Enter customer ID to update: ");
                    id = validateIntInput(1, INT_MAX);
                    Customer customer;
                    if (getCustomerById(id, &customer)) {
                        updateCustomer(&customer);
                    } else {
                        printf("Customer not found!\n");
                    }
                }
                break;
            case 3:
                {
                    int id;
                    printf("Enter customer ID to delete: ");
                    id = validateIntInput(1, INT_MAX);
                    deleteCustomer(id);
                }
                break;
            case 4:
                viewAllCustomers();
                break;
            case 5:
                searchCustomer();
                break;
            case 6:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}

/**
 * @brief Adds a new customer to the system
 * @param customer Pointer to the Customer struct to be added
 */
void addCustomer(Customer *customer) {
    Customer newCustomer;
    if (customer == NULL) {
        customer = &newCustomer;
    }

    customer->id = generateUniqueCustomerId();
    
    // Clear the buffer before taking input
    clearInputBuffer();

    validateStringInput(customer->name, MAX_NAME_LENGTH, "Enter customer name: ");
    validateStringInput(customer->email, MAX_EMAIL_LENGTH, "Enter customer email: ");
    validateStringInput(customer->phone, MAX_PHONE_LENGTH, "Enter customer phone: ");
    validateStringInput(customer->address, MAX_ADDRESS_LENGTH, "Enter customer address: ");

    FILE *file = fopen(CUSTOMERS_FILE, "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(customer, sizeof(Customer), 1, file);
    fclose(file);

    printf("Customer added successfully with ID: %d!\n", customer->id);
}


/**
 * @brief Updates an existing customer's information
 * @param customer Pointer to the Customer struct with updated information
 */
void updateCustomer(Customer *customer) {
    FILE *file = fopen(CUSTOMERS_FILE, "rb+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Customer tempCustomer;
    int found = 0;

    // Locate the specific customer in the file
    while (fread(&tempCustomer, sizeof(Customer), 1, file)) {
        if (tempCustomer.id == customer->id) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Customer not found in the file!\n");
        fclose(file);
        return;
    }

    // Prompt for new details
    validateStringInput(customer->name, MAX_NAME_LENGTH, "Enter new customer name: ");
    validateStringInput(customer->email, MAX_EMAIL_LENGTH, "Enter new customer email: ");
    validateStringInput(customer->phone, MAX_PHONE_LENGTH, "Enter new customer phone: ");
    validateStringInput(customer->address, MAX_ADDRESS_LENGTH, "Enter new customer address: ");

    // Move file pointer back to the position of the found customer
    fseek(file, -sizeof(Customer), SEEK_CUR);

    // Write the updated customer details back to the file
    fwrite(customer, sizeof(Customer), 1, file);

    fclose(file);

    printf("Customer updated successfully!\n");
}
 

/**
 * @brief Deletes a customer from the system
 * @param id The ID of the customer to be deleted
 */
void deleteCustomer(int id) {
    FILE *file = fopen(CUSTOMERS_FILE, "rb");
    FILE *tempFile = fopen("data/temp_customers.dat", "wb");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Customer customer;
    int found = 0;
    while (fread(&customer, sizeof(Customer), 1, file)) {
        if (customer.id != id) {
            fwrite(&customer, sizeof(Customer), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(CUSTOMERS_FILE);
    rename("data/temp_customers.dat", CUSTOMERS_FILE);

    if (found) {
        printf("Customer deleted successfully!\n");
    } else {
        printf("Customer not found!\n");
    }
}

/**
 * @brief Displays all customers in the system
 */
void viewAllCustomers() {
    FILE *file = fopen(CUSTOMERS_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Customer customer;
    printf("\033[1;34m");
    printf("%-5s %-20s %-30s %-15s %-30s\n", "ID", "Name", "Email", "Phone", "Address");
    printf("====================================================================================\n");
    printf("\033[0m");
    while (fread(&customer, sizeof(Customer), 1, file)) {
        printf("%-5d %-20s %-30s %-15s %-30s\n", customer.id, customer.name, customer.email, customer.phone, customer.address);
    }

    fclose(file);
}

/**
 * @brief Searches for customers based on a search term
 */
void searchCustomer() {
    char searchTerm[MAX_NAME_LENGTH];
    printf("Enter search term: ");
    scanf("%s", searchTerm);

    FILE *file = fopen(CUSTOMERS_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Customer customer;
    int found = 0;
    printf("\033[1;34m");
    printf("%-5s %-20s %-30s %-15s %-30s\n", "ID", "Name", "Email", "Phone", "Address");
    printf("====================================================================================\n");
    printf("\033[0m");
    while (fread(&customer, sizeof(Customer), 1, file)) {
        if (strstr(customer.name, searchTerm) || strstr(customer.email, searchTerm)) {
            printf("%-5d %-20s %-30s %-15s %-30s\n", customer.id, customer.name, customer.email, customer.phone, customer.address);
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("No customers found matching the search term.\n");
    }
}

/**
 * @brief Retrieves a customer by their ID
 * @param id The ID of the customer to retrieve
 * @param customer Pointer to the Customer struct to store the retrieved information
 * @return int 1 if customer found, 0 otherwise
 */
int getCustomerById(int id, Customer *customer) {
    FILE *file = fopen(CUSTOMERS_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    int found = 0;
    while (fread(customer, sizeof(Customer), 1, file)) {
        if (customer->id == id) {
            found = 1;
            break;
        }
    }

    fclose(file);
    return found;
}

