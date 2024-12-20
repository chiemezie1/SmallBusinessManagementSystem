/*
 * =====================================================================================
 * File: financial.c
 * Description: Provides functionality for generating financial reports, such as 
 *              sales, profit, and inventory value. Reports are generated based 
 *              on a date range or current inventory data, offering detailed 
 *              insights for financial decision-making.
 *
 * Author: Chiemezie Agbo
 * Date: 20-12-2024
 * Version: 1.0
 * =====================================================================================
 */

#include "../include/financial.h"
#include "../include/orders.h"
#include "../include/inventory.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDERS_FILE "data/orders.dat"
#define INVENTORY_FILE "data/inventory.dat"

/**
 * @brief Displays the financial management menu and handles user choices
 */
void financialMenu()
{
    int choice;
    do
    {
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
        choice = validateIntInput(1, 4);

        switch (choice)
        {
        case 1:
        {
            char startDate[11], endDate[11];
            validateDateInput(startDate);
            while (getchar() != '\n')
                ; // This consumes any remaining characters in the buffer
            validateDateInput(endDate);
            SalesReport report;
            generateSalesReport(startDate, endDate, &report);
        }
        break;
        case 2:
        {
            char startDate[11], endDate[11];

            validateDateInput(startDate);
            printf("Start Date: %s\n", startDate);
            while (getchar() != '\n')
                ; 

            validateDateInput(endDate);
            printf("End Date: %s\n", endDate);
            while (getchar() != '\n')
                ; 
            ProfitReport report;
            generateProfitReport(startDate, endDate, &report);
        }
        break;
        case 3:
        {
            InventoryValueReport report;
            generateInventoryValue(&report);
        }
        break;
        case 4:
            return;
        }
    } while (1);
}

/**
 * @brief Generates a sales report for a given date range
 * @param startDate The start date of the report period
 * @param endDate The end date of the report period
 * @param report Pointer to the SalesReport struct to store the generated report
 */
void generateSalesReport(const char *startDate, const char *endDate, SalesReport *report)
{
    FILE *file = fopen(ORDERS_FILE, "rb");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    report->totalSales = 0;
    report->orderCount = 0;
    report->averageOrderValue = 0;

    Order order;
    time_t start = parseDate(startDate);
    time_t end = parseDate(endDate);

    while (fread(&order, sizeof(Order), 1, file))
    {
        if (order.orderDate >= start && order.orderDate <= end)
        {
            report->totalSales += order.totalAmount;
            report->orderCount++;
        }
    }

    fclose(file);

    if (report->orderCount > 0)
    {
        report->averageOrderValue = report->totalSales / report->orderCount;
    }

    printf("\033[1;34m");
    printf("Sales Report from %s to %s\n", startDate, endDate);
    printf("====================================================================================\n");
    printf("Total Sales: $%.2f\n", report->totalSales);
    printf("Total Orders: %d\n", report->orderCount);
    printf("Average Order Value: $%.2f\n", report->averageOrderValue);
    printf("\033[0m");
}

/**
 * @brief Generates a profit report for a given date range
 * @param startDate The start date of the report period
 * @param endDate The end date of the report period
 * @param report Pointer to the ProfitReport struct to store the generated report
 */
void generateProfitReport(const char *startDate, const char *endDate, ProfitReport *report)
{
    FILE *file = fopen(ORDERS_FILE, "rb");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    report->totalRevenue = 0;
    report->totalCost = 0;
    report->totalProfit = 0;
    report->profitMargin = 0;

    Order order;
    time_t start = parseDate(startDate);
    time_t end = parseDate(endDate);

    printf("\033[1;34m");
    printf("Profit Report from %s to %s\n", startDate, endDate);
    printf("====================================================================================\n");
    printf("%-5s %-15s %-20s %-15s %-15s\n", "ID", "Order Date", "Revenue", "Cost", "Profit");
    printf("====================================================================================\n");
    printf("\033[0m");

    while (fread(&order, sizeof(Order), 1, file))
    {
        if (order.orderDate >= start && order.orderDate <= end)
        {
            char date[20];
            strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", localtime(&order.orderDate));
            double orderCost = order.totalAmount - order.profit;
            printf("%-5d %-15s $%-14.2f $%-14.2f $%-14.2f\n", order.id, date, order.totalAmount, orderCost, order.profit);
            report->totalRevenue += order.totalAmount;
            report->totalCost += orderCost;
            report->totalProfit += order.profit;
        }
    }

    fclose(file);

    if (report->totalRevenue > 0)
    {
        report->profitMargin = (report->totalProfit / report->totalRevenue) * 100;
    }

    printf("\033[1;32m");
    printf("====================================================================================\n");
    printf("Total Revenue: $%.2f\n", report->totalRevenue);
    printf("Total Cost: $%.2f\n", report->totalCost);
    printf("Total Profit: $%.2f\n", report->totalProfit);
    printf("Profit Margin: %.2f%%\n", report->profitMargin);
    printf("\033[0m");
}

/**
 * @brief Generates an inventory value report
 * @param report Pointer to the InventoryValueReport struct to store the generated report
 */
void generateInventoryValue(InventoryValueReport *report)
{
    FILE *file = fopen(INVENTORY_FILE, "rb");
    if (file == NULL)
    {
        printf("Error opening inventory file!\n");
        return;
    }

    report->totalItems = 0;
    report->totalCost = 0;
    report->totalValue = 0;

    InventoryItem item;
    printf("\033[1;34m");
    printf("Inventory Value Report\n");
    printf("====================================================================================\n");
    printf("%-5s %-30s %-10s %-15s %-15s %-15s\n", "ID", "Name", "Quantity", "Cost", "Price", "Total Value");
    printf("====================================================================================\n");
    printf("\033[0m");

    while (fread(&item, sizeof(InventoryItem), 1, file))
    {
        double itemTotalCost = item.cost * item.quantity;
        double itemTotalValue = item.price * item.quantity;

        printf("%-5d %-30s %-10d $%-14.2f $%-14.2f $%-14.2f\n",
               item.id, item.name, item.quantity, item.cost, item.price, itemTotalValue);

        report->totalItems += item.quantity;
        report->totalCost += itemTotalCost;
        report->totalValue += itemTotalValue;
    }

    fclose(file);

    double potentialProfit = report->totalValue - report->totalCost;
    double profitMargin = (report->totalValue > 0) ? (potentialProfit / report->totalValue) * 100 : 0;

    printf("\033[1;32m");
    printf("====================================================================================\n");
    printf("Total Items: %d\n", report->totalItems);
    printf("Total Cost: $%.2f\n", report->totalCost);
    printf("Total Value: $%.2f\n", report->totalValue);
    printf("Potential Profit: $%.2f\n", potentialProfit);
    printf("Potential Profit Margin: %.2f%%\n", profitMargin);
    printf("\033[0m");
}
