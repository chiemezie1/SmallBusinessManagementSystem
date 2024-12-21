#include "../include/common.h"
#include "../include/orders.h"
#include "../include/customers.h"
#include "../include/inventory.h"
#include "unity.h"
#include <stdio.h>
#include <string.h>

void setUp(void) {
    // Set up test environment
    remove(ORDERS_FILE);
    remove(CUSTOMERS_FILE);
    remove(INVENTORY_FILE);
}

void tearDown(void) {
    // Clean up test environment
    remove(ORDERS_FILE);
    remove(CUSTOMERS_FILE);
    remove(INVENTORY_FILE);
}

void test_place_order(void) {
    Customer customer = {0, "John Doe", "john@example.com", "1234567890", "123 Main St"};
    addCustomer(&customer);

    InventoryItem item = {0, "Test Item", "Test Description", 10.99, 19.99, 100};
    addInventoryItem(&item);

    Order order = {0};
    order.customerId = customer.id;
    placeOrder(&order);

    Order retrieved_order;
    int found = getOrderById(order.id, &retrieved_order);

    TEST_ASSERT_TRUE(found);
    TEST_ASSERT_EQUAL_INT(customer.id, retrieved_order.customerId);
    TEST_ASSERT_EQUAL_STRING("Pending", retrieved_order.status);
}

void test_update_order_status(void) {
    Customer customer = {0, "John Doe", "john@example.com", "1234567890", "123 Main St"};
    addCustomer(&customer);

    InventoryItem item = {0, "Test Item", "Test Description", 10.99, 19.99, 100};
    addInventoryItem(&item);

    Order order = {0};
    order.customerId = customer.id;
    placeOrder(&order);

    updateOrderStatus(order.id, "Shipped");

    Order retrieved_order;
    int found = getOrderById(order.id, &retrieved_order);

    TEST_ASSERT_TRUE(found);
    TEST_ASSERT_EQUAL_STRING("Shipped", retrieved_order.status);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_place_order);
    RUN_TEST(test_update_order_status);
    return UNITY_END();
}

