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

void test_add_inventory_item(void) {
    InventoryItem item = {0, "Test Item", "Test Description", 10.99, 100};
    addInventoryItem(&item);

    // Verify the item was added
    InventoryItem retrieved_item;
    int found = getInventoryItemById(item.id, &retrieved_item);

    TEST_ASSERT_TRUE(found);
    TEST_ASSERT_EQUAL_STRING(item.name, retrieved_item.name);
    TEST_ASSERT_EQUAL_STRING(item.description, retrieved_item.description);
    TEST_ASSERT_EQUAL_FLOAT(item.price, retrieved_item.price);
    TEST_ASSERT_EQUAL_INT(item.quantity, retrieved_item.quantity);
}

void test_update_inventory_item(void) {
    InventoryItem item = {0, "Test Item", "Test Description", 10.99, 100};
    addInventoryItem(&item);

    // Update the item
    item.price = 15.99;
    item.quantity = 150;
    updateInventoryItem(&item);

    // Verify the item was updated
    InventoryItem retrieved_item;
    int found = getInventoryItemById(item.id, &retrieved_item);

    TEST_ASSERT_TRUE(found);
    TEST_ASSERT_EQUAL_FLOAT(15.99, retrieved_item.price);
    TEST_ASSERT_EQUAL_INT(150, retrieved_item.quantity);
}

void test_delete_inventory_item(void) {
    InventoryItem item = {0, "Test Item", "Test Description", 10.99, 100};
    addInventoryItem(&item);

    // Delete the item
    deleteInventoryItem(item.id);

    // Verify the item was deleted
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

