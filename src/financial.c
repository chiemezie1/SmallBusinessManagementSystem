#include "financial.h"
#include "inventory.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ORDERS_FILE "data/orders.dat"
#define INVENTORY_FILE "data/inventory.dat"

void financialMenu() {
    int choice;
    do {
        printf("\033[1;36m");
        printf("╔════════════════════════════╗\n");
        printf("║   Financial Management     ║\n");
        printf("╠════════════════════════════╣\n");
        printf("║ 1. Generate Sales Report   ║\n");
        printf("║ 2. Generate Profit Report  ║\n");
        printf("║ 3. Generate Inventory Value║\n");
        printf("║ 4. Back to Main Menu       ║\n");
        printf("╚════════════════════════════╝\n");
        printf("\033[0m");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generateSalesReport();
                break;
            case 2:
                generateProfitReport();
                break;
            case 3:
                generateInventoryValue();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}

void generateSalesReport() {
    FILE *file = fopen(ORDERS_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Order order;
    double totalSales = 0;
    int orderCount = 0;
    time_t startDate, endDate;

    printf("Enter start date (YYYY-MM-DD): ");
    char dateStr[11];
    scanf("%s", dateStr);
    startDate = parseDate(dateStr);

    printf("Enter end date (YYYY-MM-DD): ");
    scanf("%s", dateStr);
    endDate = parseDate(dateStr);

    printf("\033[1;34m");
    printf("Sales Report from %s to %s\n", formatDate(startDate), formatDate(endDate));
    printf("====================================================================================\n");
    printf("%-5s %-15s %-20s %-15s\n", "ID", "Customer ID", "Order Date", "Total Amount");
    printf("====================================================================================\n");
    printf("\033[0m");

    while (fread(&order, sizeof(Order), 1, file)) {
        if (order.orderDate >= startDate && order.orderDate <= endDate) {
            char date[20];
            strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", localtime(&order.orderDate));
            printf("%-5d %-15d %-20s $%-14.2f\n", order.id, order.customerId, date, order.totalAmount);
            totalSales += order.totalAmount;
            orderCount++;
        }
    }

    printf("\033[1;32m");
    printf("====================================================================================\n");
    printf("Total Sales: $%.2f\n", totalSales);
    printf("Total Orders: %d\n", orderCount);
    printf("Average Order Value: $%.2f\n", orderCount > 0 ? totalSales / orderCount : 0);
    printf("\033[0m");

    fclose(file);
}

void generateProfitReport() {
    FILE *file = fopen(ORDERS_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Order order;
    double totalRevenue = 0;
    double totalProfit = 0;
    int orderCount = 0;
    time_t startDate, endDate;

    printf("Enter start date (YYYY-MM-DD): ");
    char dateStr[11];
    scanf("%s", dateStr);
    startDate = parseDate(dateStr);

    printf("Enter end date (YYYY-MM-DD): ");
    scanf("%s", dateStr);
    endDate = parseDate(dateStr);

    printf("\033[1;34m");
    printf("Profit Report from %s to %s\n", formatDate(startDate), formatDate(endDate));
    printf("====================================================================================\n");
    printf("%-5s %-15s %-20s %-15s %-15s\n", "ID", "Order Date", "Revenue", "Cost", "Profit");
    printf("====================================================================================\n");
    printf("\033[0m");

    while (fread(&order, sizeof(Order), 1, file)) {
        if (order.orderDate >= startDate && order.orderDate <= endDate) {
            char date[20];
            strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", localtime(&order.orderDate));
            double orderCost = order.totalAmount - order.profit;
            printf("%-5d %-15s $%-14.2f $%-14.2f $%-14.2f\n", order.id, date, order.totalAmount, orderCost, order.profit);
            totalRevenue += order.totalAmount;
            totalProfit += order.profit;
            orderCount++;
        }
    }

    fclose(file);

    double profitMargin = (totalRevenue > 0) ? (totalProfit / totalRevenue) * 100 : 0;

    printf("\033[1;32m");
    printf("====================================================================================\n");
    printf("Total Revenue: $%.2f\n", totalRevenue);
    printf("Total Cost: $%.2f\n", totalRevenue - totalProfit);
    printf("Total Profit: $%.2f\n", totalProfit);
    printf("Total Orders: %d\n", orderCount);
    printf("Actual Profit Margin: %.2f%%\n", profitMargin);
    printf("\033[0m");
}


void generateInventoryValue() {
    FILE *file = fopen(INVENTORY_FILE, "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    InventoryItem item;
    double totalValue = 0;
    int itemCount = 0;
    int validItemCount = 0;

    printf("\033[1;34m");
    printf("Inventory Value Report\n");
    printf("====================================================================================\n");
    printf("%-5s %-20s %-10s %-15s %-15s\n", "ID", "Name", "Quantity", "Unit Price", "Total Value");
    printf("====================================================================================\n");
    printf("\033[0m");

    while (fread(&item, sizeof(InventoryItem), 1, file)) {
        itemCount++;
        if (item.quantity > 0 && item.price > 0) {
            double itemValue = item.price * item.quantity;
            printf("%-5d %-20s %-10d $%-14.2f $%-14.2f\n", item.id, item.name, item.quantity, item.price, itemValue);
            totalValue += itemValue;
            validItemCount++;
        }
    }

    fclose(file);

    printf("\033[1;32m");
    printf("====================================================================================\n");
    printf("Total Inventory Value: $%.2f\n", totalValue);
    printf("Total Items: %d\n", itemCount);
    printf("Items with Value: %d\n", validItemCount);
    if (validItemCount > 0) {
        printf("Average Item Value: $%.2f\n", totalValue / validItemCount);
    } else {
        printf("Average Item Value: $0.00\n");
    }
    printf("\033[0m");
}

