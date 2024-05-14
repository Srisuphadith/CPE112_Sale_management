#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCT_FILE "../csv/product.csv"
#define HISTORY_FILE "../csv/userHistory.csv"

// Structure for AVL tree node
typedef struct AVLNode {
    int id;
    char name[50];
    double price;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Function prototypes
AVLNode* loadProducts(const char* filename);
void userMenu();
void adminMenu();
void history(const char* user);

// AVL tree utility functions
AVLNode* insert(AVLNode* node, int id, const char* name, double price);
AVLNode* createNode(int id, const char* name, double price);
int height(AVLNode* node);
int max(int a, int b);
int getBalance(AVLNode* node);
AVLNode* rightRotate(AVLNode* y);
AVLNode* leftRotate(AVLNode* x);

// Main function
int main() {
    AVLNode* root = NULL;

    // Load products into AVL tree
    root = loadProducts(PRODUCT_FILE);
    if (root == NULL) {
        printf("Failed to load products from file.\n");
        return 1;
    }

    char role;
    printf("Enter role (a for admin, u for user): ");
    scanf(" %c", &role);

    if (role == 'a') {
        adminMenu();
    } else if (role == 'u') {
        userMenu();
    } else {
        printf("Invalid role.\n");
    }

    return 0;
}

// Function to load products from CSV file into AVL tree
AVLNode* loadProducts(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        return NULL;
    }

    AVLNode* root = NULL;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        int id;
        char name[50];
        double price;
        sscanf(buffer, "%d,%49[^,],%lf", &id, name, &price);
        root = insert(root, id, name, price);
    }

    fclose(file);
    return root;
}

// Function to display user menu
void userMenu() {
    printf("User Menu:\n");
    printf("1. Search for a product\n");
    printf("2. Shop for products\n");
    printf("3. View purchase history\n");
    // Implementation of menu options can be added here
}

// Function to display admin menu
void adminMenu() {
    printf("Admin Menu:\n");
    printf("Functionality not implemented.\n");
}

// Function to display user purchase history
void history(const char* user) {
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file == NULL) {
        printf("No purchase history found for user: %s\n", user);
        return;
    }

    char buffer[256];
    int found = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        char userInFile[50];
        char history[200];
        sscanf(buffer, "%49[^,],%199[^\n]", userInFile, history);
        if (strcmp(userInFile, user) == 0) {
            printf("Purchase history for %s: %s\n", user, history);
            found = 1;
        }
    }

    if (!found) {
        printf("No purchase history found for user: %s\n", user);
    }

    fclose(file);
}

// AVL tree utility functions implementation

AVLNode* createNode(int id, const char* name, double price) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->id = id;
    strcpy(node->name, name);
    node->price = price;
    node->left = node->right = NULL;
    node->height = 1;  // New node is initially added at leaf
    return node;
}

int height(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

AVLNode* insert(AVLNode* node, int id, const char* name, double price) {
    if (node == NULL) {
        return createNode(id, name, price);
    }

    if (id < node->id) {
        node->left = insert(node->left, id, name, price);
    } else if (id > node->id) {
        node->right = insert(node->right, id, name, price);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && id < node->left->id) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && id > node->right->id) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && id > node->left->id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && id < node->right->id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}
