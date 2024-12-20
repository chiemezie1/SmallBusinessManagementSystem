#include "../include/financial.h"
#include "../include/orders.h"
#include "../include/inventory.h"
#include "unity.h"
#include <stdio.h>
#include <string.h>

void setUp(void) {
    // Set up test environment
}

void tearDown(void) {
    // Clean up test environment
}

void test_generate_sales_report(void) {
    // Add some test orders
    Order order1 = {0, 1, 1609459200, 100.00, "Completed", 50.00};
    Order order2 = {0, 2, 1609545600, 150.00, "Completed", 75.00};
    placeOrder(&order1);
    placeOrder(&order2);

    // Generate sales report
    SalesReport report;
    generateSalesReport("2021-01-01", "2021-01-02", &report);

    TEST_ASSERT_EQUAL_FLOAT(250.00, report.totalSales);
    TEST_ASSERT_EQUAL_INT(2, report.orderCount);
    TEST_ASSERT_EQUAL_FLOAT(125.00, report.averageOrderValue);
}

void test_generate_profit_report(void) {
    // Add some test orders and inventory items
    Order order = {0, 1, 1609459200, 100.00, "Completed", 50.00};
    placeOrder(&order);

    InventoryItem item = {0, "Test Item", "Test Description", 50.00, 100.00, 10};
    addInventoryItem(&item);

    // Generate profit report
    ProfitReport report;
    generateProfitReport("2021-01-01", "2021-01-01", &report);

    TEST_ASSERT_EQUAL_FLOAT(100.00, report.totalRevenue);
    TEST_ASSERT_EQUAL_FLOAT(50.00, report.totalCost);
    TEST_ASSERT_EQUAL_FLOAT(50.00, report.totalProfit);
    TEST_ASSERT_EQUAL_FLOAT(0.5, report.profitMargin);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_generate_sales_report);
    RUN_TEST(test_generate_profit_report);
    return UNITY_END();
}

