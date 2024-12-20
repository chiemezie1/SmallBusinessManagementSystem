#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include "common.h"

void customerMenu();
void addCustomer();
void updateCustomer();
void deleteCustomer();
void viewAllCustomers();
void searchCustomer();
int getCustomerById(int id, Customer *customer);
int generateUniqueCustomerId();

#endif // CUSTOMERS_H

