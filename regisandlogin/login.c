#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 100
#define MAX_PASSWORD 100
#define MAX_LINE 200

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User users[100]; // Array of users, you can replace 100 with the maximum number of users you want to support
int userCount = 0; // Number of registered users

void loadUsers() {
    FILE *file = fopen("users.csv", "r");
    if (file == NULL) {
        printf("Could not open users.csv\n");
        return;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%s", users[userCount].username, users[userCount].password);
        userCount++;
    }

    fclose(file);
}

void loginUser() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character from fgets

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character from fgets

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            return;
        }
    }

    printf("Invalid username or password\n");
}

int main() {
    int choice;

    loadUsers();

    printf("1. Login\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Consume newline character left by scanf

    switch (choice) {
    case 1:
        loginUser();
        break;
    default:
        printf("Invalid choice\n");
    }

    return 0;
}