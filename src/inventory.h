#ifndef INVENTORY_H
#define INVENTORY_H

#include "common.h"

void inventoryMenu();
void addInventoryItem();
void updateInventoryItem();
void deleteInventoryItem();
void viewAllInventoryItems();
void searchInventoryItem();
int getInventoryItemById(int id, InventoryItem *item);
int generateUniqueInventoryId();
void updateInventoryItemById(InventoryItem *item);

#endif // INVENTORY_H


