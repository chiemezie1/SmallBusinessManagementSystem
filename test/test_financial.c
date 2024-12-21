#include "../include/common.h"
#include "../include/financial.h"
#include "../include/orders.h"
#include "../include/inventory.h"
#include "../include/customers.h"
#include "unity.h"
#include <stdio.h>
#include <string.h>

void setUp(void) {
    // Set up test environment
    remove(ORDERS_FILE);
    remove(INVENTORY_FILE);
    remove(CUSTOMERS_FILE);
}

void tearDown(void) {
    // Clean up test environment
    remove(ORDERS_FILE);
    remove(INVENTORY_FILE);
    remove(CUSTOMERS_FILE);
}

void test_generate_sales_report(void) {
    Customer customer = {0, "John Doe", "john@example.com", "1234567890", "123 Main St"};
    addCustomer(&customer);

    InventoryItem item = {0, "Test Item", "Test Description", 10.99, 19.99, 100};
    addInventoryItem(&item);

    Order order1 = {0};
    order1.customerId = customer.id;
    order1.orderDate = 1609459200; // 2021-01-01
    order1.totalAmount = 100.00;
    placeOrder(&order1);

    Order order2 = {0};
    order2.customerId = customer.id;
    order2.orderDate = 1609545600; // 2021-01-02
    order2.totalAmount = 150.00;
    placeOrder(&order2);

    SalesReport report;
    generateSalesReport("2021-01-01", "2021-01-02", &report);

    TEST_ASSERT_EQUAL_FLOAT(250.00, report.totalSales);
    TEST_ASSERT_EQUAL_INT(2, report.orderCount);
    TEST_ASSERT_EQUAL_FLOAT(125.00, report.averageOrderValue);
}

void test_generate_profit_report(void) {
    Customer customer = {0, "John Doe", "john@example.com", "1234567890", "123 Main St"};
    addCustomer(&customer);

    InventoryItem item = {0, "Test Item", "Test Description", 10.99, 19.99, 100};
    addInventoryItem(&item);

    Order order = {0};
    order.customerId = customer.id;
    order.orderDate = 1609459200; // 2021-01-01
    order.totalAmount = 100.00;
    order.profit = 50.00;
    placeOrder(&order);

    ProfitReport report;
    generateProfitReport("2021-01-01", "2021-01-01", &report);

    TEST_ASSERT_EQUAL_FLOAT(100.00, report.totalRevenue);
    TEST_ASSERT_EQUAL_FLOAT(50.00, report.totalCost);
    TEST_ASSERT_EQUAL_FLOAT(50.00, report.totalProfit);
    TEST_ASSERT_EQUAL_FLOAT(50.0, report.profitMargin);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_generate_sales_report);
    RUN_TEST(test_generate_profit_report);
    return UNITY_END();
}

