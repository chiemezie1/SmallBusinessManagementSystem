/*
 * =====================================================================================
 * File: order_management.c
 * Description: Implements the order management system, including placing, 
 *              updating, and viewing orders. It handles inventory management 
 *              and profit calculation based on order data, and manages order 
 *              IDs and statuses.
 *
 * Author: Chiemezie Agbo
 * Date: 20-12-2024
 * Version: 1.0
 * =====================================================================================
 */

#include <limits.h>
#include "../include/orders.h"
#include "../include/customers.h"
#include "../include/inventory.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ORDERS_FILE "data/orders.dat"
#define INVENTORY_FILE "data/inventory.dat"

/**
 * @brief Displays the order management menu and handles user choices
 */
void orderMenu() {
    int choice;
    do {
        printf("\033[1;35m");
        printf("╔════════════════════════════╗\n");
        printf("║     Order Management       ║\n");
        printf("╠════════════════════════════╣\n");
        printf("║ 1. Place Order             ║\n");
        printf("║ 2. Update Order Status     ║\n");
        printf("║ 3. View All Orders         ║\n");
        printf("║ 4. Search Order            ║\n");
        printf("║ 5. Back to Main Menu       ║\n");
        printf("╚════════════════════════════╝\n");
        printf("\033[0m");
        printf("Enter your choice: ");
        choice = validateIntInput(1, 5);

        switch (choice) {
            case 1:
                {
                    Order newOrder = {0};
                    placeOrder(&newOrder);
                }
                break;
            case 2:
                updateOrderStatus();
                break;
            case 3:
                viewAllOrders();
                break;
            case 4:
                searchOrder();
                break;
            case 5:
                return;
        }
    } while (1);
}

/**
 * @brief Places a new order in the system
 * @param order Pointer to the Order struct to be added
 */
void placeOrder(Order *order) {
    Customer customer;

    // Get customer ID and validate
    do {
        printf("Enter customer ID: ");
        order->customerId = validateIntInput(1, INT_MAX);

        if (!getCustomerById(order->customerId, &customer)) {
            printf("Error: Customer with ID %d not found. Please try again.\n", order->customerId);
        } else {
            break;
        }
    } while (1);

    order->id = generateUniqueOrderId();
    order->orderDate = time(NULL);
    order->totalAmount = 0;
    order->profit = 0;
    strcpy(order->status, "Pending");

    int numItems;
    printf("Enter the number of items in this order: ");
    numItems = validateIntInput(1, 100);

    for (int i = 0; i < numItems; i++) {
        int inventoryId, quantity;
        InventoryItem item;

        do {
            printf("Enter inventory item ID for item %d: ", i + 1);
            inventoryId = validateIntInput(1, INT_MAX);

            if (!getInventoryItemById(inventoryId, &item)) {
                printf("Error: Inventory item with ID %d not found. Please try again.\n", inventoryId);
            } else {
                break;
            }
        } while (1);

        do {
            printf("Enter quantity for item %d: ", i + 1);
            quantity = validateIntInput(1, item.quantity);

            if (quantity > item.quantity) {
                printf("Error: Not enough stock. Available quantity: %d. Please try again.\n", item.quantity);
            } else {
                break;
            }
        } while (1);

        // Update inventory
        item.quantity -= quantity;
        updateInventoryItemById(&item);

        // Update order total and profit
        double itemRevenue = item.price * quantity;
        double itemCost = item.cost * quantity;
        order->totalAmount += itemRevenue;
        order->profit += (itemRevenue - itemCost);
    }

    FILE *file = fopen(ORDERS_FILE, "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(order, sizeof(Order), 1, file);
    fclose(file);

    printf("Order placed successfully for customer %s (ID: %d)!\n", customer.name, customer.id);
    printf("Order ID: %d\n", order->id);
    printf("Total amount: $%.2f\n", order->totalAmount);
}

/**
 * @brief Updates the status of an existing order
 */
void updateOrderStatus() {
    int id;
    printf("Enter order ID to update: ");
    id = validateIntInput(1, INT_MAX);

    FILE *file = fopen(ORDERS_FILE, "rb+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Order order;
    int found = 0;
    while (fread(&order, sizeof(Order), 1, file)) {
        if (order.id == id) {
            printf("Current status: %s\n", order.status);
            printf("Choose new order status:\n");
            printf("1. Pending\n");
            printf("2. Shipped\n");
            printf("3. Completed\n");
            int statusChoice = validateIntInput(1, 3);

            switch (statusChoice) {
                case 1:
                    strcpy(order.status, "Pending");
                    break;
                case 2:
                    strcpy(order.status, "Shipped");
                    break;
                case 3:
                    strcpy(order.status, "Completed");
                    break;
            }

            fseek(file, -sizeof(Order), SEEK_CUR);
            fwrite(&order, sizeof(Order), 1, file);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("Order status updated successfully!\n");
    } else {
        printf("Order not found!\n");
    }
}

/**
 * @brief Displays all orders in the system
 */
void viewAllOrders() {
    FILE *file = fopen(ORDERS_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Order order;
    printf("\033[1;34m");
    printf("%-5s %-15s %-20s %-15s %-10s %-10s\n", "ID", "Customer ID", "Order Date", "Total Amount", "Status", "Profit");
    printf("==============================================================================\n");
    printf("\033[0m");
    while (fread(&order, sizeof(Order), 1, file)) {
        char date[20];
        strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", localtime(&order.orderDate));
        printf("%-5d %-15d %-20s $%-14.2f %-10s $%-9.2f\n", order.id, order.customerId, date, order.totalAmount, order.status, order.profit);
    }

    fclose(file);
}

/**
 * @brief Searches for an order by its ID
 */
void searchOrder() {
    int id;
    printf("Enter order ID to search: ");
    id = validateIntInput(1, INT_MAX);

    FILE *file = fopen(ORDERS_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Order order;
    int found = 0;
    while (fread(&order, sizeof(Order), 1, file)) {
        if (order.id == id) {
            printf("\033[1;34m");
            printf("%-5s %-15s %-20s %-15s %-10s %-10s\n", "ID", "Customer ID", "Order Date", "Total Amount", "Status", "Profit");
            printf("==============================================================================\n");
            printf("\033[0m");
            char date[20];
            strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", localtime(&order.orderDate));
            printf("%-5d %-15d %-20s $%-14.2f %-10s $%-9.2f\n", order.id, order.customerId, date, order.totalAmount, order.status, order.profit);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Order not found!\n");
    }
}

/**
 * @brief Generates a unique order ID
 * @return int The generated unique ID
 */
int generateUniqueOrderId() {
    static int lastId = 0;
    FILE *file = fopen(ORDERS_FILE, "rb");
    if (file != NULL) {
        Order order;
        while (fread(&order, sizeof(Order), 1, file)) {
            if (order.id > lastId) {
                lastId = order.id;
            }
        }
        fclose(file);
    }
    return ++lastId;
}

/**
 * @brief Retrieves an order by its ID
 * @param id The ID of the order to retrieve
 * @param order Pointer to the Order struct to store the retrieved information
 * @return int 1 if order found, 0 otherwise
 */
int getOrderById(int id, Order *order) {
    FILE *file = fopen(ORDERS_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    int found = 0;
    while (fread(order, sizeof(Order), 1, file)) {
        if (order->id == id) {
            found = 1;
            break;
        }
    }

    fclose(file);
    return found;
}

