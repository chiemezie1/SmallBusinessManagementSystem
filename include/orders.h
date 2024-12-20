#ifndef ORDERS_H
#define ORDERS_H

#include "common.h"

void orderMenu();
void placeOrder();
void updateOrderStatus();
void viewAllOrders();
void searchOrder();
int generateUniqueOrderId();

// Add these function declarations
int getOrderById(int id, Order *order);
void placeOrder(Order *order);

#endif // ORDERS_H

