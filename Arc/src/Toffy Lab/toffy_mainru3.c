#include "AVL.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 255
#define DATE_SIZE 7
#define PRODUCT_ID_SIZE 7

int history(const char file[], int user_id);

int main() {
    int choice;
    char searchProduct[BUFFER_SIZE];

    AVL_Tree *init = readProductsFromFile("../csv/product.csv");
    if (init == NULL) {
        printf("Error: Unable to read products from file\n");
        return 1;
    }

    printf("Enter your choice: \n1. Search product\n2. Shop\n3. History\n-1. Exit\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter Product You want to find :");
            scanf("%s", searchProduct);
            search(searchProduct, init);
            break;
        case 2:
            shop(init, "../csv/allCategory.csv");
            break;
        case 3:
            if (!history("../csv/userHistory.csv", 2)) {
                printf("file doesn't exist\n");
            } else {
                printf("completely\n");
            }
            break;
        case -1:
            /*exit*/
            break;
        default:
            printf("please enter number between 1-3\n");
    }

    freeAVLTree(init);
    return 0;
}

AVL_Tree *readProductsFromFile(const char file[]) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        return NULL;
    }

    AVL_Tree *init = NULL;
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        AVL_Tree *tmp = (AVL_Tree *)malloc(sizeof(AVL_Tree));
        sscanf(buffer,
               "%6[^,],%6[^,],%100[^,],%d,%7[^,],%7[^,],%50[^,],%d,%d,%d,%d,%d",
               tmp->ID, tmp->stockID, tmp->productName, &tmp->price, tmp->imports,
               tmp->exports, tmp->category, &tmp->stock, &tmp->access,
               &tmp->addToCart, &tmp->buy, &tmp->key);

        init = insertNodeAVL(init, createNode(tmp->ID, tmp->stockID, tmp->productName,
                                             tmp->price, tmp->imports, tmp->exports, tmp->category,
                                             tmp->stock, tmp->access, tmp->addToCart, tmp->buy));
        free(tmp);
    }

    fclose(fp);
    return init;
}

int history(const char file[], int user_id) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("You didn't buy anything.\n");
        return 0;
    }

    int user, id;
    char date[DATE_SIZE];
    char proID[PRODUCT_ID_SIZE];
    while (fscanf(fp, "%d,%d,%7[^,],%6[^,]", &id, &user, date, proID) == 4) {
        if (user_id == user) {
            printf("User: %d\n", user_id);
            printf("Name of product: %s\n", proID);
            printf("------------------------------------------\n");
        }
    }

    fclose(fp);
    return 1;
}

void freeAVLTree(AVL_Tree *root) {
    if (root ==NULL) {
        return;
    }

    freeAVLTree(root->left);
    freeAVLTree(root->right);
    free(root);
}