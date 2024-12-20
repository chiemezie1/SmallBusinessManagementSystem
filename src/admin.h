#ifndef ADMIN_H
#define ADMIN_H

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int is_admin;
} User;

void adminMenu();
void addUser();
void viewUsers();
void backupData();
void restoreData();
int loginUser(char *username, char *password);
void changePassword(char *username);

#endif // ADMIN_H

