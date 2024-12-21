#include "../include/customers.h"
#include "../include/common.h"
#include "unity.h"
#include <stdio.h>
#include <string.h>

void setUp(void) {
    // Set up test environment
    remove(CUSTOMERS_FILE);
}

void tearDown(void) {
    // Clean up test environment
    remove(CUSTOMERS_FILE);
}

void test_add_customer(void) {
    Customer customer = {0, "John Doe", "john@example.com", "1234567890", "123 Main St"};
    addCustomer(&customer);

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

    strcpy(customer.email, "johndoe@example.com");
    strcpy(customer.phone, "9876543210");
    updateCustomer(&customer);

    Customer retrieved_customer;
    int found = getCustomerById(customer.id, &retrieved_customer);

    TEST_ASSERT_TRUE(found);
    TEST_ASSERT_EQUAL_STRING("johndoe@example.com", retrieved_customer.email);
    TEST_ASSERT_EQUAL_STRING("9876543210", retrieved_customer.phone);
}

void test_delete_customer(void) {
    Customer customer = {0, "John Doe", "john@example.com", "1234567890", "123 Main St"};
    addCustomer(&customer);

    deleteCustomer(customer.id);

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

