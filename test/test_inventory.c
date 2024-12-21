#include "../include/common.h"
#include "../include/inventory.h"
#include "unity.h"
#include <stdio.h>
#include <string.h>

void setUp(void) {
    // Set up test environment
    remove(INVENTORY_FILE);
}

void tearDown(void) {
    // Clean up test environment
    remove(INVENTORY_FILE);
}

void test_add_inventory_item(void) {
    InventoryItem item = {0, "Test Item", "Test Description", 10.99, 19.99, 100};
    addInventoryItem(&item);

    InventoryItem retrieved_item;
    int found = getInventoryItemById(item.id, &retrieved_item);

    TEST_ASSERT_TRUE(found);
    TEST_ASSERT_EQUAL_STRING(item.name, retrieved_item.name);
    TEST_ASSERT_EQUAL_STRING(item.description, retrieved_item.description);
    TEST_ASSERT_EQUAL_FLOAT(item.cost, retrieved_item.cost);
    TEST_ASSERT_EQUAL_FLOAT(item.price, retrieved_item.price);
    TEST_ASSERT_EQUAL_INT(item.quantity, retrieved_item.quantity);
}

void test_update_inventory_item(void) {
    InventoryItem item = {0, "Test Item", "Test Description", 10.99, 19.99, 100};
    addInventoryItem(&item);

    item.price = 24.99;
    item.quantity = 150;
    updateInventoryItemById(&item);

    InventoryItem retrieved_item;
    int found = getInventoryItemById(item.id, &retrieved_item);

    TEST_ASSERT_TRUE(found);
    TEST_ASSERT_EQUAL_FLOAT(24.99, retrieved_item.price);
    TEST_ASSERT_EQUAL_INT(150, retrieved_item.quantity);
}

void test_delete_inventory_item(void) {
    InventoryItem item = {0, "Test Item", "Test Description", 10.99, 19.99, 100};
    addInventoryItem(&item);

    deleteInventoryItem(item.id);

    InventoryItem retrieved_item;
    int found = getInventoryItemById(item.id, &retrieved_item);

    TEST_ASSERT_FALSE(found);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_add_inventory_item);
    RUN_TEST(test_update_inventory_item);
    RUN_TEST(test_delete_inventory_item);
    return UNITY_END();
}

