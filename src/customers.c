#include "customers.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define CUSTOMERS_FILE "data/customers.dat"

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
                addCustomer();
                break;
            case 2:
                updateCustomer();
                break;
            case 3:
                deleteCustomer();
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

void addCustomer() {
    Customer customer;
    customer.id = generateUniqueCustomerId();
    validateStringInput(customer.name, MAX_NAME_LENGTH, "Enter customer name: ");
    validateStringInput(customer.email, MAX_EMAIL_LENGTH, "Enter customer email: ");
    validateStringInput(customer.phone, MAX_PHONE_LENGTH, "Enter customer phone: ");
    validateStringInput(customer.address, MAX_ADDRESS_LENGTH, "Enter customer address: ");

    FILE *file = fopen(CUSTOMERS_FILE, "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&customer, sizeof(Customer), 1, file);
    fclose(file);

    printf("Customer added successfully with ID: %d!\n", customer.id);
}

void updateCustomer() {
    int id;
    printf("Enter customer ID to update: ");
    id = validateIntInput(1, INT_MAX);

    FILE *file = fopen(CUSTOMERS_FILE, "rb+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Customer customer;
    int found = 0;
    while (fread(&customer, sizeof(Customer), 1, file)) {
        if (customer.id == id) {
            printf("Enter new customer name: ");
            scanf("%s", customer.name);
            printf("Enter new customer email: ");
            scanf("%s", customer.email);
            printf("Enter new customer phone: ");
            scanf("%s", customer.phone);
            printf("Enter new customer address: ");
            scanf("%s", customer.address);

            fseek(file, -sizeof(Customer), SEEK_CUR);
            fwrite(&customer, sizeof(Customer), 1, file);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("Customer updated successfully!\n");
    } else {
        printf("Customer not found!\n");
    }
}

void deleteCustomer() {
    int id;
    printf("Enter customer ID to delete: ");
    id = validateIntInput(1, INT_MAX);

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

