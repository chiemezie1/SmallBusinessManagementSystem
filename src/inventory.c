/*
 * =====================================================================================
 * File: inventory.c
 * Description: Manages inventory items, including adding, updating, deleting, 
 *              viewing, and searching. Inventory data is stored in a binary file 
 *              (data/inventory.dat) and manipulated through various functions 
 *              for persistence and inventory management.
 *
 * Author: Chiemezie Agbo
 * Date: 20-12-2024
 * Version: 1.0
 * =====================================================================================
 */

#include "../include/inventory.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INVENTORY_FILE "data/inventory.dat"

/**
 * @brief Displays the inventory management menu and handles user choices
 */
void inventoryMenu() {
    int choice;
    do {
        printf("\033[1;32m");
        printf("╔════════════════════════════╗\n");
        printf("║    Inventory Management    ║\n");
        printf("╠════════════════════════════╣\n");
        printf("║ 1. Add Item                ║\n");
        printf("║ 2. Update Item             ║\n");
        printf("║ 3. Delete Item             ║\n");
        printf("║ 4. View All Items          ║\n");
        printf("║ 5. Search Item             ║\n");
        printf("║ 6. Back to Main Menu       ║\n");
        printf("╚════════════════════════════╝\n");
        printf("\033[0m");
        printf("Enter your choice: ");
        choice = validateIntInput(1, 6);

        switch (choice) {
            case 1:
                addInventoryItem();
                break;
            case 2:
                updateInventoryItem();
                break;
            case 3:
                deleteInventoryItem();
                break;
            case 4:
                viewAllInventoryItems();
                break;
            case 5:
                searchInventoryItem();
                break;
            case 6:
                return;
        }
    } while (1);
}

/**
 * @brief Adds a new inventory item to the system
 */
void addInventoryItem() {
    InventoryItem item;
    item.id = generateUniqueInventoryId();
    validateStringInput(item.name, MAX_NAME_LENGTH, "Enter item name: ");
    validateStringInput(item.description, MAX_DESCRIPTION_LENGTH, "Enter item description: ");
    printf("Enter item cost: ");
    item.cost = validateDoubleInput(0, 1000000);
    printf("Enter item selling price: ");
    item.price = validateDoubleInput(item.cost, 1000000);
    printf("Enter item quantity: ");
    item.quantity = validateIntInput(0, 1000000);

    FILE *file = fopen(INVENTORY_FILE, "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&item, sizeof(InventoryItem), 1, file);
    fclose(file);

    printf("Item added successfully!\n");
}

/**
 * @brief Updates an existing inventory item
 */
void updateInventoryItem() {
    int id;
    printf("Enter item ID to update: ");
    id = validateIntInput(1, INT_MAX);

    InventoryItem item;
    if (getInventoryItemById(id, &item)) {
        validateStringInput(item.name, MAX_NAME_LENGTH, "Enter new item name: ");
        validateStringInput(item.description, MAX_DESCRIPTION_LENGTH, "Enter new item description: ");
        printf("Enter new item cost: ");
        item.cost = validateDoubleInput(0, 1000000);
        printf("Enter new item selling price: ");
        item.price = validateDoubleInput(item.cost, 1000000);
        printf("Enter new item quantity: ");
        item.quantity = validateIntInput(0, 1000000);

        updateInventoryItemById(&item);
        printf("Item updated successfully!\n");
    } else {
        printf("Item not found!\n");
    }
}

/**
 * @brief Deletes an inventory item from the system
 */
void deleteInventoryItem() {
    int id;
    printf("Enter item ID to delete: ");
    id = validateIntInput(1, INT_MAX);

    FILE *file = fopen(INVENTORY_FILE, "rb");
    FILE *tempFile = fopen("data/temp_inventory.dat", "wb");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    InventoryItem item;
    int found = 0;
    while (fread(&item, sizeof(InventoryItem), 1, file)) {
        if (item.id != id) {
            fwrite(&item, sizeof(InventoryItem), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(INVENTORY_FILE);
    rename("data/temp_inventory.dat", INVENTORY_FILE);

    if (found) {
        printf("Item deleted successfully!\n");
    } else {
        printf("Item not found!\n");
    }
}

/**
 * @brief Displays all inventory items in the system
 */
void viewAllInventoryItems() {
    FILE *file = fopen(INVENTORY_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    InventoryItem item;
    printf("\033[1;34m");
    printf("%-5s %-20s %-30s %-10s %-10s %-10s\n", "ID", "Name", "Description", "Cost", "Price", "Quantity");
    printf("====================================================================================\n");
    printf("\033[0m");
    while (fread(&item, sizeof(InventoryItem), 1, file)) {
        printf("%-5d %-20s %-30s $%-9.2f $%-9.2f %-10d\n", item.id, item.name, item.description, item.cost, item.price, item.quantity);
    }

    fclose(file);
}

/**
 * @brief Searches for inventory items based on a search term
 */
void searchInventoryItem() {
    char searchTerm[MAX_NAME_LENGTH];
    validateStringInput(searchTerm, MAX_NAME_LENGTH, "Enter search term: ");

    FILE *file = fopen(INVENTORY_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    InventoryItem item;
    int found = 0;
    printf("\033[1;34m");
    printf("%-5s %-20s %-30s %-10s %-10s %-10s\n", "ID", "Name", "Description", "Cost", "Price", "Quantity");
    printf("====================================================================================\n");
    printf("\033[0m");
    while (fread(&item, sizeof(InventoryItem), 1, file)) {
        if (strstr(item.name, searchTerm) || strstr(item.description, searchTerm)) {
            printf("%-5d %-20s %-30s $%-9.2f $%-9.2f %-10d\n", item.id, item.name, item.description, item.cost, item.price, item.quantity);
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("No items found matching the search term.\n");
    }
}

/**
 * @brief Retrieves an inventory item by its ID
 * @param id The ID of the inventory item to retrieve
 * @param item Pointer to the InventoryItem struct to store the retrieved information
 * @return int 1 if item found, 0 otherwise
 */
int getInventoryItemById(int id, InventoryItem *item) {
    FILE *file = fopen(INVENTORY_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    int found = 0;
    while (fread(item, sizeof(InventoryItem), 1, file)) {
        if (item->id == id) {
            found = 1;
            break;
        }
    }

    fclose(file);
    return found;
}

/**
 * @brief Generates a unique inventory item ID
 * @return int The generated unique ID
 */
int generateUniqueInventoryId() {
    static int lastId = 0;
    FILE *file = fopen(INVENTORY_FILE, "rb");
    if (file != NULL) {
        InventoryItem item;
        while (fread(&item, sizeof(InventoryItem), 1, file)) {
            if (item.id > lastId) {
                lastId = item.id;
            }
        }
        fclose(file);
    }
    return ++lastId;
}

/**
 * @brief Updates an inventory item by its ID
 * @param item Pointer to the InventoryItem struct with updated information
 */
void updateInventoryItemById(InventoryItem *item) {
    FILE *file = fopen(INVENTORY_FILE, "rb+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    InventoryItem temp;
    while (fread(&temp, sizeof(InventoryItem), 1, file)) {
        if (temp.id == item->id) {
            fseek(file, -sizeof(InventoryItem), SEEK_CUR);
            fwrite(item, sizeof(InventoryItem), 1, file);
            break;
        }
    }

    fclose(file);
}

