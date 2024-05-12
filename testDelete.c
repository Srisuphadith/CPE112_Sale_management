#include "AVL.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new AVL tree node
struct AVL_Tree *createNode(const char *ID, const char *stockID, const char *productName, int price, const char *imports, const char *exports, const char *category, int stock, int access, int addToCart, int buy)
{
    struct AVL_Tree *newNode = (struct AVL_Tree *)malloc(sizeof(struct AVL_Tree));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(newNode->ID, ID);
    strcpy(newNode->stockID, stockID);
    strcpy(newNode->productName, productName);
    newNode->price = price;
    strcpy(newNode->imports, imports);
    strcpy(newNode->exports, exports);
    strcpy(newNode->category, category);
    newNode->stock = stock;
    newNode->access = access;
    newNode->addToCart = addToCart;
    newNode->buy = buy;
    newNode->heightOfTree = 1; // Initialize height

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Function to get the height of a node
int height(struct AVL_Tree *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->heightOfTree;
}

// Function to calculate the maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Function to update the height of a node
void updateHeight(struct AVL_Tree *node)
{
    node->heightOfTree = 1 + max(height(node->left), height(node->right));
}

// Function to perform a right rotation
struct AVL_Tree *rightRotate(struct AVL_Tree *y)
{
    struct AVL_Tree *x = y->left;
    struct AVL_Tree *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Function to perform a left rotation
struct AVL_Tree *leftRotate(struct AVL_Tree *x)
{
    struct AVL_Tree *y = x->right;
    struct AVL_Tree *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Function to balance the AVL tree
struct AVL_Tree *balance(struct AVL_Tree *node)
{
    // Update height of current node
    updateHeight(node);

    // Check balance factor
    int balanceFactor = height(node->left) - height(node->right);

    // Left Heavy
    if (balanceFactor > 1)
    {
        if (height(node->left->left) >= height(node->left->right))
        {
            return rightRotate(node);
        }
        else
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    // Right Heavy
    else if (balanceFactor < -1)
    {
        if (height(node->right->right) >= height(node->right->left))
        {
            return leftRotate(node);
        }
        else
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    // Balanced
    return node;
}

// Function to insert a node into the AVL tree
struct AVL_Tree *insertNodeAVL(struct AVL_Tree *root, struct AVL_Tree *newNode)
{
    // Perform standard BST insertion
    if (root == NULL)
    {
        return newNode;
    }

    if (strcmp(newNode->ID, root->ID) < 0)
    {
        root->left = insertNodeAVL(root->left, newNode);
    }
    else if (strcmp(newNode->ID, root->ID) > 0)
    {
        root->right = insertNodeAVL(root->right, newNode);
    }
    else
    { // Duplicate keys not allowed
        return root;
    }

    // Update height of current node
    updateHeight(root);

    // Balance the tree
    return balance(root);
}

// Function to delete a node from the AVL tree
struct AVL_Tree *deleteNodeF(struct AVL_Tree *root, const char *ID)
{
    if (root == NULL)
    {
        return root;
    }

    // Search for the node to be deleted
    if (strcmp(ID, root->ID) < 0)
    {
        root->left = deleteNodeF(root->left, ID);
    }
    else if (strcmp(ID, root->ID) > 0)
    {
        root->right = deleteNodeF(root->right, ID);
    }
    else
    {
        // Node found, delete it
        if (root->left == NULL)
        {
            struct AVL_Tree *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct AVL_Tree *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children, get the inorder successor (smallest in the right subtree)
        struct AVL_Tree *temp = root->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }

        // Copy the inorder successor's content to this node
        strcpy(root->ID, temp->ID);
        strcpy(root->stockID, temp->stockID);
        strcpy(root->productName, temp->productName);
        root->price = temp->price;
        strcpy(root->imports, temp->imports);
        strcpy(root->exports, temp->exports);
        strcpy(root->category, temp->category);
        root->stock = temp->stock;
        root->access = temp->access;
        root->addToCart = temp->addToCart;
        root->buy = temp->buy;

        // Delete the inorder successor
        root->right = deleteNodeF(root->right, temp->ID);
    }
    return root;
}

// Function to search for a node by its ID
struct AVL_Tree *searchNode(struct AVL_Tree *root, const char *ID)
{
    if (root == NULL || strcmp(root->ID, ID) == 0)
    {
        return root;
    }

    if (strcmp(ID, root->ID) < 0)
    {
        return searchNode(root->left, ID);
    }
    else
    {
        return searchNode(root->right, ID);
    }
}

// Function to display the details of a node
void displayNode(struct AVL_Tree *node)
{
    printf("ID: %s\n", node->ID);
    printf("Stock ID: %s\n", node->stockID);
    printf("Product Name: %s\n", node->productName);
    printf("Price: %d\n", node->price);
    printf("Import: %s\n", node->imports);
    printf("Export: %s\n", node->exports);
    printf("Category: %s\n", node->category);
    printf("Stock: %d\n", node->stock);
    printf("Access: %d\n", node->access);
    printf("Add To Cart: %d\n", node->addToCart);
    printf("Buy: %d\n", node->buy);
    printf("-------------------\n");
}

void reverse_inOrder(struct AVL_Tree *node)
{
    if (node == NULL)
    {
        return;
    }

    reverse_inOrder(node->right);
    displayNode(node);
    reverse_inOrder(node->left);
}

void displayTree(struct AVL_Tree *root)
{
    if (root == NULL)
    {
        return;
    }

    displayTree(root->right);
    displayNode(root);
    displayTree(root->left);
}

int main()
{
    // Create an empty AVL tree
    struct AVL_Tree *root = NULL;

    char ID[6], stockID[6], productName[50], imports[7], exports[7], category[50];
    int stock, access, addToCart, buy, price;

    int number;
    scanf("%d", &number);
    for (int i = 0; i < number; i++)
    {
        scanf("%s %s %s %d %s %s %s %d %d %d %d", ID, stockID, productName, &price, imports, exports,category, &stock, &access, &addToCart, &buy);
        root = insertNodeAVL(root, createNode(ID, stockID, productName, price, imports, exports, category, stock, access, addToCart, buy));
    }
    

    // // Insert nodes into the AVL tree
    // root = insertNodeAVL(root, createNode("56849", "00001", "แจกัน", 349, "100567", "140567", "อุปโภค", 10, 0, 0, 4));
    // root = insertNodeAVL(root, createNode("12345", "00002", "ตาชั่ง", 199, "50000", "100000", "เครื่องใช้ไฟฟ้า", 20, 0, 1, 2));
    // root = insertNodeAVL(root, createNode("67890", "00003", "เสื้อยืด", 299, "80000", "90000", "เสื้อผ้า", 30, 0, 1, 3));
    // root = insertNodeAVL(root, createNode("24680", "00004", "รองเท้า", 499, "30000", "40000", "เสื้อผ้า", 40, 0, 0, 5));
    // root = insertNodeAVL(root, createNode("13579", "00005", "กระเป๋า", 599, "60000", "70000", "เครื่องใช้ในบ้าน", 50, 0, 1, 6));
    // root = insertNodeAVL(root, createNode("11111", "00006", "เสื้อกันหนาว", 799, "20000", "30000", "เสื้อผ้า", 60, 0, 0, 7));
    // root = insertNodeAVL(root, createNode("22222", "00007", "กางเกงยีนส์", 899, "70000", "80000", "เสื้อผ้า", 70, 0, 1, 8));
    // root = insertNodeAVL(root, createNode("33333", "00008", "หมวก", 299, "10000", "15000", "เครื่องใช้ในบ้าน", 80, 0, 0, 9));
    // root = insertNodeAVL(root, createNode("44444", "00009", "นาฬิกาข้อมือ", 1999, "500000", "600000", "เครื่องใช้ไฟฟ้า", 90, 0, 1, 10));

    // Show the AVL tree nodes before deletion
    printf("AVL tree nodes before deletion:\n");
    reverse_inOrder(root);
    printf("\n");

    // Delete a node from the AVL tree (for example, with ID "12345")
    const char *deleteID = "12345";
    struct AVL_Tree *deleteNode = searchNode(root, deleteID);
    if (deleteNode != NULL)
    {
        root = deleteNodeF(root, deleteID);
        printf("Node with ID %s deleted successfully.\n\n", deleteID);
    }
    else
    {
        printf("Node with ID %s not found.\n\n", deleteID);
    }

    // Show the AVL tree nodes after deletion
    printf("AVL tree nodes after deletion:\n");
    reverse_inOrder(root);

    return 0;
}
