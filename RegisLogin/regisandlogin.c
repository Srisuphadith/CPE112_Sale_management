#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_LEN 50
#define FILENAME "users.csv"
#define LOGFILE "login_attempts.txt"

typedef struct {
    int userID;
    char username[MAX_LEN];
    char password[MAX_LEN];
    char role[MAX_LEN];
} User;

typedef struct {
    User users[MAX_USERS];
    int total_users;
} UserManager;

void log_attempt(const char *username, int success) {
    FILE *file = fopen(LOGFILE, "a");
    if (!file) {
        perror("Error opening log file");
        return;
    }

    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);

    if (success)
        fprintf(file, "Login successful for user: %s at %s\n", username, buffer);
    else
        fprintf(file, "Login failed for user: %s at %s\n", username, buffer);

    fclose(file);
}

void read_users_from_file(UserManager *um) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("Error opening user file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%d,%[^,],%[^,],%s", &um->users[um->total_users].userID,
                  um->users[um->total_users].username, um->users[um->total_users].password,
                  um->users[um->total_users].role) == 4) {
        um->total_users++;
    }

    fclose(file);
}

void write_users_to_file(const UserManager *um) {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        perror("Error opening user file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < um->total_users; i++) {
        fprintf(file, "%d,%s,%s,%s\n", um->users[i].userID, um->users[i].username,
                um->users[i].password, um->users[i].role);
    }

    fclose(file);
}

int is_username_unique(const UserManager *um, const char *username) {
    for (int i = 0; i < um->total_users; i++) {
        if (strcmp(um->users[i].username, username) == 0) {
            return 0;
        }
    }
    return 1;
}

void register_user(UserManager *um) {
    if (um->total_users >= MAX_USERS) {
        printf("Maximum users reached.\n");
        return;
    }

    char username[MAX_LEN], password[MAX_LEN];
    int role_choice;

    printf("Enter username: ");
    scanf("%s", username);

    if (!is_username_unique(um, username)) {
        printf("Username already exists. Please choose a different username.\n");
        return;
    }

    strcpy(um->users[um->total_users].username, username);
    printf("Enter password: ");
    scanf("%s", um->users[um->total_users].password);
    printf("Enter role (1 for User, 2 for Admin): ");
    scanf("%d", &role_choice);

    switch (role_choice) {
        case 1:
            strcpy(um->users[um->total_users].role, "User");
            break;
        case 2:
            strcpy(um->users[um->total_users].role, "Admin");
            break;
        default:
            printf("Invalid role choice. Defaulting to User.\n");
            strcpy(um->users[um->total_users].role, "User");
    }

    um->users[um->total_users].userID = um->total_users + 1; // Auto-generate userID
    um->total_users++;
}

void login(const UserManager *um) {
    char username[MAX_LEN], password[MAX_LEN];
    printf("Enter username: ");
    scanf("%s", username);
    for (int i = 0; i < um->total_users; i++) {
    if (strcmp(username, um->users[i].username) != 0){
            printf("username not found, please register first\n");
            exit(0);
        }
    }
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < um->total_users; i++) {
        if (strcmp(username, um->users[i].username) == 0 &&
            strcmp(password, um->users[i].password) == 0) {
            printf("Login successful!\n");
            printf("Welcome, %s (%s)\n", um->users[i].username, um->users[i].role);
            log_attempt(username, 1);
            return;
        }
    }

    printf("Invalid username or password.\n");
    log_attempt(username, 0);
}

int main() {
    UserManager um = { .total_users = 0 };

    read_users_from_file(&um);

    int choice;
    do {
        printf("\n1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user(&um);
                break;
            case 2:
                login(&um);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter again.\n");
        }
    } while (choice != 3);

    write_users_to_file(&um);

    return 0;
}
