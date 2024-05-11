#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 100
#define MAX_PASSWORD 100

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User users[100]; // Array of users, you can replace 100 with the maximum number of users you want to support
int userCount = 0; // Number of registered users

void registerUser() {
    User newUser;

    printf("Enter username: ");
    fgets(newUser.username, MAX_USERNAME, stdin);
    newUser.username[strcspn(newUser.username, "\n")] = 0; // Remove newline character from fgets

    printf("Enter password: ");
    fgets(newUser.password, MAX_PASSWORD, stdin);
    newUser.password[strcspn(newUser.password, "\n")] = 0; // Remove newline character from fgets

    users[userCount++] = newUser; // Add new user to the array and increment the user count

    printf("User registered successfully!\n");
}

int main() {
    int choice;

    printf("1. Register\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        registerUser();
        break;
    default:
        printf("Invalid choice\n");
    }

    return 0;
}