#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include "../include/common.h"

void customerMenu();
void addCustomer(Customer *customer);
void updateCustomer(Customer *customer);
void deleteCustomer(int id);
void viewAllCustomers();
void searchCustomer();
int getCustomerById(int id, Customer *customer);
int generateUniqueCustomerId();
void clearInputBuffer();

#endif // CUSTOMERS_H

