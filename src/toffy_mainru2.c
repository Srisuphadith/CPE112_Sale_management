#include "AVL.c"
#include "Sell_Product_Func.c"
#include "shop.c"
#include "regisandlogin.c" // Include the regisandlogin.c file
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for file paths
#define PRODUCT_FILE_PATH "../csv/product.csv"
#define USER_HISTORY_FILE_PATH "../csv/userHistory.csv"
#define ALL_CATEGORY_FILE_PATH "../csv/allCategory.csv"

// Function prototypes
void loadProducts(AVL_Tree **productTree);
void userMenu(AVL_Tree *productTree);
int history(char file[], int user_id);

int main() {
    AVL_Tree *productTree = NULL;
    loadProducts(&productTree);

    char *role = main_login(); // Call the login function

    if (strcmp(role, "Admin") == 0) {
        adminMenu(productTree); // Call the adminMenu function if the user is an Admin
    } else {
        userMenu(productTree); // Call the userMenu function if the user is a User
    }

    userMenu(productTree);
    return 0;
}

void loadProducts(AVL_Tree **productTree) {
    AVL_Tree *tmp = (AVL_Tree *)malloc(sizeof(AVL_Tree));
    FILE *fp = fopen(PRODUCT_FILE_PATH, "r");
    if (fp == NULL) {
        printf("Failed to open product file.\n");
        return;
    }

    char buffer[255];
    while (fgets(buffer, 255, fp)) {
        sscanf(buffer, "%6[^,],%6[^,],%100[^,],%d,%7[^,],%7[^,],%50[^,],%d,%d,%d,%d,%d",
               tmp->ID, tmp->stockID, tmp->productName, &tmp->price, tmp->imports,
               tmp->exports, tmp->category, &tmp->stock, &tmp->access,
               &tmp->addToCart, &tmp->buy, &tmp->key);
        *productTree = insertNodeAVL(*productTree, createNode(tmp->ID, tmp->stockID, tmp->productName,
                                                 tmp->price, tmp->imports, tmp->exports, 
                                                 tmp->category, tmp->stock, tmp->access, 
                                                 tmp->addToCart, tmp->buy));
        printf("%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d\n", tmp->ID, tmp->stockID,
               tmp->productName, tmp->price, tmp->imports, tmp->exports,
               tmp->category, tmp->stock, tmp->access, tmp->addToCart, tmp->buy,
               tmp->key);
    }
    fclose(fp);
    free(tmp);
}

void userMenu(AVL_Tree *productTree) {
    int choice;
    char searchProduct[50];
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter Product You want to find :");
            scanf("%s", searchProduct);
            search(searchProduct, productTree);
            break;
        case 2:
            shop(productTree, ALL_CATEGORY_FILE_PATH);
            break;
        case 3:
            if (!history(USER_HISTORY_FILE_PATH, 2)) {
                printf("file doesn't exist");
            } else {
                printf("complete");
            }
            break;
        case -1:
            break;
        default:
            printf("please enter a number between 1-3");
    }
}

int history(char file[], int user_id) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        printf("You didn't buy anything.\n");
        return 0;
    }

    int user, id;
    char date[7];
    char proID[7];
    while (fscanf(fp, "%d,%d,%7[^,],%6[^,]", &id, &user, date, proID) != EOF) {
        if (user_id == user) {
            printf("User: %d\n", user_id);
            printf("Name of product: %s\n", proID);
            printf("------------------------------------------\n");
        }
    }

    fclose(fp);
    return 1;
}