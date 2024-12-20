#include "../include/orders.h"
#include "unity.h"
#include <stdio.h>
#include <string.h>

void setUp(void) {
    // Set up test environment
}

void tearDown(void) {
    // Clean up test environment
}

void test_place_order(void) {
    Order order = {0, 1, 0, 100.00, "Pending"};
    placeOrder(&order);

    // Verify the order was placed
    Order retrieved_order;
    int found = getOrderById(order.id, &retrieved_order);

    TEST_ASSERT_TRUE(found);
    TEST_ASSERT_EQUAL_INT(order.customerId, retrieved_order.customerId);
    TEST_ASSERT_EQUAL_FLOAT(order.totalAmount, retrieved_order.totalAmount);
    TEST_ASSERT_EQUAL_STRING(order.status, retrieved_order.status);
}

void test_update_order_status(void) {
    Order order = {0, 1, 0, 100.00, "Pending"};
    placeOrder(&order);

    // Update the order status
    updateOrderStatus(order.id, "Shipped");

    // Verify the order status was updated
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

