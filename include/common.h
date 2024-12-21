#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INVENTORY_FILE "data/inventory.dat"
#define ORDERS_FILE "data/orders.dat"
#define CUSTOMERS_FILE "data/customers.dat"
#define USERS_FILE "data/users.dat"
#define BACKUP_DIR "data/backup/"

#define MAX_NAME_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_EMAIL_LENGTH 100
#define MAX_PHONE_LENGTH 20
#define MAX_ADDRESS_LENGTH 200

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    double cost;
    double price;
    int quantity;
} InventoryItem;

typedef struct {
    int id;
    int customerId;
    time_t orderDate;
    double totalAmount;
    char status[20];
    double profit;
} Order;

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
} Customer;

#endif // COMMON_H

