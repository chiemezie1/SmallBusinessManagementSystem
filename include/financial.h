#ifndef FINANCIAL_H
#define FINANCIAL_H

#include "common.h"

typedef struct {
    double totalSales;
    int orderCount;
    double averageOrderValue;
} SalesReport;

typedef struct {
    double totalRevenue;
    double totalCost;
    double totalProfit;
    double profitMargin;
} ProfitReport;

typedef struct {
    int totalItems;
    double totalCost;
    double totalValue;
} InventoryValueReport;

void financialMenu();
void generateSalesReport(const char *startDate, const char *endDate, SalesReport *report);
void generateProfitReport(const char *startDate, const char *endDate, ProfitReport *report);
void generateInventoryValue(InventoryValueReport *report);

#endif // FINANCIAL_H

