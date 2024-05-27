#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCT_FILE_PATH "../csv/product.csv"
#define USER_HISTORY_FILE_PATH "../csv/userHistory.csv"
#define CATEGORY_FILE_PATH "../csv/category.csv"

typedef struct Product {
    char id[10];
    char name[100];
    int price;
    int stock;
    char category[50];
} Product;

typedef struct AVLNode {
    Product product;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

typedef AVLNode *AVLTree;

AVLTree createNode(Product product);
int height(AVLNode *node);
int max(int a, int b);
AVLNode *newNode(Product product);
AVLNode *rightRotate(AVLNode *y);
AVLNode *leftRotate(AVLNode *x);
int getBalance(AVLNode *N);
AVLNode *insertNodeAVL(AVLNode *root, Product product);
AVLNode *minValueNode(AVLNode *node);
AVLNode *deleteNodeAVL(AVLNode *root, char *id);
void freeAVLTree(AVLNode *root);

AVLTree loadProducts();
void userMenu(AVLTree tree);
void adminMenu();
void history(int user_id);

int main() {
    AVLTree tree = loadProducts();
    int user_id;
    printf("Enter user ID: ");
    scanf("%d", &user_id);

    if (user_id == 1) {
        userMenu(tree);
    } else {
        adminMenu();
    }

    return 0;
}

AVLTree loadProducts() {
    FILE *fp = fopen(PRODUCT_FILE_PATH, "r");
    if (fp == NULL) {
        printf("Error: Unable to open product file\n");
        exit(1);
    }

    AVLTree tree = NULL;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        Product product;
        sscanf(buffer, "%[^,],%[^,],%d,%d,%s\n", product.id, product.name, &product.price, &product.stock, product.category);
        tree = insertNodeAVL(tree, product);
    }

    fclose(fp);
    return tree;
}

void userMenu(AVLTree tree) {
    int choice;
    printf("\nUser Menu:\n");
    printf("1. Search product\n");
    printf("2. Shop\n");
    printf("3. History\n");
    printf("4. Logout\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Search product functionality
            break;
        case 2:
            // Shop functionality
            break;
        case 3:
            history(1);
            break;
        case 4:
            // Logout functionality
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
}

void adminMenu() {
    // Placeholder for admin-specific functionalities
}

void history(int user_id) {
    FILE *fp = fopen(USER_HISTORY_FILE_PATH, "r");
    if (fp == NULL) {
        printf("User hasn't bought anything.\n");
        return;
    }

    char id[10];
    fscanf(fp, "%s", id);
    if (atoi(id) != user_id) {
        printf("User hasn't bought anything.\n");
        fclose(fp);
        return;
    }

    char productId[10];
    while (fscanf(fp, "%s", productId)== 1) {
        printf("Product ID: %s\n", productId);
    }

    fclose(fp);
}

// AVL tree functions
AVLTree createNode(Product product) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->product = product;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode *newNode(Product product) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    node->product = product;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVLNode *N) {
    if (N == NULL) {
        return 0;
    }
    return height(N->left) - height(N->right);
}

AVLNode *insertNodeAVL(AVLNode *root, Product product) {
    if (root == NULL) {
        return createNode(product);
    }

    if (strcmp(product.id, root->product.id) < 0) {
        root->left = insertNodeAVL(root->left, product);
    } else if (strcmp(product.id, root->product.id) > 0) {
        root->right = insertNodeAVL(root->right, product);
    } else {
        // Product already exists
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && strcmp(product.id, root->left->product.id) < 0) {
        return rightRotate(root);
    }

    if (balance < -1 && strcmp(product.id, root->right->product.id) > 0) {
        return leftRotate(root);
    }

    if (balance > 1 && strcmp(product.id, root->left->product.id) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && strcmp(product.id, root->right->product.id) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

AVLNode *minValueNode(AVLNode *node) {
    AVLNode *current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

AVLNode *deleteNodeAVL(AVLNode *root, char *id) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(id, root->product.id) < 0) {
        root->left = deleteNodeAVL(root->left, id);
    } else if (strcmp(id, root->product.id) > 0) {
        root->right = deleteNodeAVL(root->right, id);
    } else {
        if (root->left == NULL || root->right == NULL) {
            AVLNode *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            AVLNode *temp = minValueNode(root->right);
            root->product = temp->product;
            root->right = deleteNodeAVL(root->right, temp->product.id);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void freeAVLTree(AVLNode *root) {
    if (root == NULL) {
        return;
    }

    freeAVLTree(root->left);
    freeAVLTree(root->right);
    free(root);
}