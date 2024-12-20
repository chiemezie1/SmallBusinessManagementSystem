#include "../src/customers.h"
#include "unity.h"
#include <stdio.h>
#include <string.h>

void setUp(void) {
    // Set up test environment
}

void tearDown(void) {
    // Clean up test environment
}

void test_add_customer(void) {
    Customer customer = {0, "John Doe", "john@example.com", "1234567890", "123 Main St"};
    addCustomer(&customer);

    // Verify the customer was added
    Customer retrieved_customer;
    int found = getCustomerById(customer.id, &retrieved_customer);

    TEST_ASSERT_TRUE(found);
    TEST_ASSERT_EQUAL_STRING(customer.name, retrieved_customer.name);
    TEST_ASSERT_EQUAL_STRING(customer.email, retrieved_customer.email);
    TEST_ASSERT_EQUAL_STRING(customer.phone, retrieved_customer.phone);
    TEST_ASSERT_EQUAL_STRING(customer.address, retrieved_customer.address);
}

void test_update_customer(void) {
    Customer customer = {0, "John Doe", "john@example.com", "1234567890", "123 Main St"};
    addCustomer(&customer);

    // Update the customer
    strcpy(customer.email, "johndoe@example.com");
    strcpy(customer.phone, "9876543210");
    updateCustomer(&customer);

    // Verify the customer was updated
    Customer retrieved_customer;
    int found = getCustomerById(customer.id, &retrieved_customer);

    TEST_ASSERT_TRUE(found);
    TEST_ASSERT_EQUAL_STRING("johndoe@example.com", retrieved_customer.email);
    TEST_ASSERT_EQUAL_STRING("9876543210", retrieved_customer.phone);
}

void test_delete_customer(void) {
    Customer customer = {0, "John Doe", "john@example.com", "1234567890", "123 Main St"};
    addCustomer(&customer);

    // Delete the customer
    deleteCustomer(customer.id);

    // Verify the customer was deleted
    Customer retrieved_customer;
    int found = getCustomerById(customer.id, &retrieved_customer);

    TEST_ASSERT_FALSE(found);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_add_customer);
    RUN_TEST(test_update_customer);
    RUN_TEST(test_delete_customer);
    return UNITY_END();
}

