#include <stdio.h>
#include "AVL.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct AVL_Tree *createnode(char ID[6] /*ไอดีสินค้า*/, char stockID[6] /*ไอ่ดีสต็อค*/, char imports[7] /*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, char exports[7] /*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, char category[50], int stock, int access /*จำนวนการกดดูสินค้านั้นๆ*/, int addToCart /*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/, int buy /*จำนวนการซื้อ(ครั้ง)*/)
{
    struct AVL_Tree *newnode = (struct AVL_Tree *)malloc(sizeof(struct AVL_Tree));
    strcpy(newnode->ID, ID);
    strcpy(newnode->stockID, stockID);
    strcpy(newnode->imports, imports);
    strcpy(newnode->exports, exports);
    strcpy(newnode->category, category);
    newnode->stock = stock;
    newnode->access = access;
    newnode->addToCart = addToCart;
    newnode->buy = buy;
    newnode->heightOfTree = 1;
    newnode->key = access + addToCart + buy;

    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

int height(struct AVL_Tree *N)
{
    if (N == NULL)
        return 0;
    return N->heightOfTree;
}

int maxof(int a, int b)
{
    return (a > b) ? a : b;
}

int getBalance(struct AVL_Tree *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct AVL_Tree *rightRotate(struct AVL_Tree *y)
{
    struct AVL_Tree *x = y->left;
    struct AVL_Tree *temp = x->left;

    // perform rotation
    x->right = y;
    y->left = temp;

    // updateheight
    y->heightOfTree = maxof(height(y->left), height(y->right)) + 1;
    x->heightOfTree = maxof(height(x->left), height(x->right)) + 1;

    return x;
}

struct AVL_Tree *leftRotate(struct AVL_Tree *x)
{
    struct AVL_Tree *y = x->right;
    struct AVL_Tree *temp = y->left;

    // perform rotation
    y->left = x;
    x->right = temp;

    // updateheight
    x->heightOfTree = maxof(height(x->left), height(x->right)) + 1;
    y->heightOfTree = maxof(height(y->left), height(y->right)) + 1;

    return y;
}

// เพิ่มสินค้าใน AVL Tree
//  เพิ่ม
//  กรอกข้อมูลสินค้า เช่น ชื่อ รหัส
//  ุจำนวนสินค้าคงคลัง

struct AVL_Tree *insert_AVL(struct AVL_Tree *node, char ID[6] /*ไอดีสินค้า*/, char stockID[6] /*ไอ่ดีสต็อค*/
                            ,
                            char imports[7] /*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, char exports[7] /*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, char category[50], int stock,
                            int access /*จำนวนการกดดูสินค้านั้นๆ*/, int addToCart /*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/, int buy /*จำนวนการซื้อ(ครั้ง)*/)
{
    if (node == NULL)
        return createnode(ID /*ไอดีสินค้า*/, stockID /*ไอ่ดีสต็อค*/, imports /*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, exports /*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, category, stock, access /*จำนวนการกดดูสินค้านั้นๆ*/, addToCart /*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/, buy /*จำนวนการซื้อ(ครั้ง)*/);

    if ((access + addToCart + buy) <= (node->key))
        node->left = insert_AVL(node->left, ID /*ไอดีสินค้า*/, stockID /*ไอ่ดีสต็อค*/, imports /*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, exports /*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, category, stock, access /*จำนวนการกดดูสินค้านั้นๆ*/, addToCart /*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/, buy /*จำนวนการซื้อ(ครั้ง)*/);
    else if ((access + addToCart + buy) > (node->key))
        node->right = insert_AVL(node->right, ID /*ไอดีสินค้า*/, stockID /*ไอ่ดีสต็อค*/, imports /*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, exports /*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, category, stock, access /*จำนวนการกดดูสินค้านั้นๆ*/, addToCart /*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/, buy /*จำนวนการซื้อ(ครั้ง)*/);

    node->heightOfTree = 1 + maxof(height(node->left), height(node->right));

    int balance = getBalance(node);

    //**Balance checking and rotations**
    // Left Left case(LL)
    if (balance > 1 && ((access + addToCart + buy) <= node->left->key))
        return rightRotate(node);

    // Right Right case(RR)
    if (balance < -1 && ((access + addToCart + buy) > node->right->key))
        return leftRotate(node);

    // Left Right case(LR)
    if (balance > 1 && ((access + addToCart + buy) > node->left->key))
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left case(RL)
    if (balance < -1 && ((access + addToCart + buy) <= node->right->key))
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// แก้ไขสินค้าใน AVL Tree
//  แก้ไขสินค้า
//  แก้ไขข้อมูลสินค้า
//  เปลี่ยนแปลงจำนวนสินค้า
void edit_AVL(struct AVL_Tree *node, char ID[], char newCategory[], char newStockID[])
{
    while (node != NULL)
    {
        if (strcmp(node->ID, ID) == 0)
        {
            strcpy(node->category, newCategory);
            strcpy(node->stockID, newStockID);
            return;
        }
        else if (strcmp(ID, node->ID) < 0)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
}

//ค้นหาสินค้าใน AVL_Tree
// ค้นหาสินค้า
// ค้นหาสินค้าตามชื่อ รายละเอียด หมวดหมู่
// ค้นหาสินค้าตามราคา
// ค้นหาสินค้าตามจำนวนสินค้า
struct AVL_Tree *searchAVL(AVL_Tree *node, char ID[6]) {
    if (node == NULL )
        return NULL;

    if (strcmp(node->ID, ID) == 0)
        return node;

    if (strcmp(ID, node->ID) < 0)
        return searchAVL(node->left, ID);

    return searchAVL(node->right, ID);
}

struct AVL_Tree *minValueNode(struct AVL_Tree *node)
{
    struct AVL_Tree *current = node; 

    // วนลูปลงไปยังโหนดที่มีค่าน้อยที่สุดในส่วนซ้าย
    while (current->left != NULL)
        current = current->left;

    return current;
}


//ลบสินค้าใน AVL Tree
struct AVL_Tree *deleteNode(struct AVL_Tree *root, char ID[6]) {

    struct AVL_Tree *target = searchAVL(root,ID);
    if(target == NULL)
        return root;
    // If the ID is same as root's ID, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct AVL_Tree *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct AVL_Tree *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: get the in-order successor (smallest in the right subtree)
        struct AVL_Tree *temp = minValueNode(root->right);

        // Copy the in-order successor's content to this node
        strcpy(root->ID, temp->ID);
        strcpy(root->stockID, temp->stockID);
        strcpy(root->imports, temp->imports);
        strcpy(root->exports, temp->exports);
        strcpy(root->category, temp->category);
        root->stock = temp->stock;
        root->access = temp->access;
        root->addToCart = temp->addToCart;
        root->buy = temp->buy;
        root->key = temp->key;

        // Delete the in-order successor
        root->right = deleteNode(root->right, temp->ID);
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

///////////////////////////////////////////coco-Manage-Stock
    // Update the height of the current node
    root->heightOfTree = 1 + maxof(height(root->left), height(root->right));

    // Check the balance factor to maintain AVL property
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}



//กรองสินค้าใน AVL_Tree
// กรองสินค้า
// กรองสินค้าตามหมวดหมู่/ราคา/จำนวนสินค้า
=======
// ค้นหาสินค้าใน AVL_Tree
//  ค้นหาสินค้า
//  ค้นหาสินค้าตามชื่อ รายละเอียด หมวดหมู่
//  ค้นหาสินค้าตามราคา
//  ค้นหาสินค้าตามจำนวนสินค้า
struct AVL_Tree *searchAVL(AVL_Tree *node, char ID[6])
{
    if (node == NULL || strcmp(node->ID, ID) == 0)
        return node;

    if (strcmp(ID, node->ID) < 0)
        return searchAVL(node->left, ID);

    return searchAVL(node->right, ID);
}

// กรองสินค้าใน AVL_Tree
//  กรองสินค้า
//  กรองสินค้าตามหมวดหมู่/ราคา/จำนวนสินค้า
///////////////////////// main

void filter_AVL(struct AVL_Tree *node, char category[])
{
    printf("Products in category \"%s\" : \n", category);
    while (node != NULL)
    {
        if (strcmp(node->category, category) == 0)
        {
            printf("ID: %s\n", node->ID);
            printf("Stock ID: %s\n", node->stockID);
            printf("\n");
        }
        node = node->left;
        node = node->right;
    }
}

// สำหรับ test
void displayNode(AVL_Tree *node)
{
    printf("ID: %s\n", node->ID);
    printf("Stock ID: %s\n", node->stockID);
    printf("Imports: %s\n", node->imports);
    printf("Exports: %s\n", node->exports);
    printf("Category: %s\n", node->category);
    printf("Stock: %d\n", node->stock);
    printf("Access: %d\n", node->access);
    printf("Add to Cart: %d\n", node->addToCart);
    printf("Buy: %d\n", node->buy);
    printf("Key: %d\n", node->key);
}

// Traversal AVL_Tree To show suggestion right->root->left
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

int main()
{
    AVL_Tree *root = NULL;
    char ID[6], stockID[6], imports[7], exports[7], category[50];
    int stock, access, addToCart, buy, n;

    // รับจำนวนสินค้า
    scanf("%d", &n);

    // รับข้อมูลสินค้าและเพิ่มลงในต้นไม้ AVL
    for (int i = 0; i < n; ++i)
    {
        scanf("%s %s %s %s %s %d %d %d %d", ID, stockID, imports, exports, category, &stock, &access, &addToCart, &buy);
        root = insert_AVL(root, ID, stockID, imports, exports, category, stock, access, addToCart, buy);
    }


    // รับข้อมูลสินค้าและเพิ่มลงในต้นไม้ AVL
    for (int i = 0; i < n; ++i) {
        scanf("%s %s %s %s %s %d %d %d %d", ID, stockID, imports, exports, category, &stock, &access, &addToCart, &buy);
        root = insert_AVL(root, ID, stockID, imports, exports, category, stock, access, addToCart, buy);
    }
    reverse_inOrder(root);
