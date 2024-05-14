#include "AVL.c"
#include "Sell_Product_Func.c"
#include "shop.c"
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
    userMenu(productTree);
    return 0;
}

void loadProducts(AVL_Tree **productTree) {
    AVL_Tree *tmp = (AVL_Tree *)malloc(sizeof(AVL_Tree));
    FILE *fp = fopen(PRODUCT_FILE_PATH, "r");
    if (fp == NULL) {
        perror("Failed to open product file");
        exit(EXIT_FAILURE);
    }

    char buffer[255];
    while (fgets(buffer, sizeof(buffer), fp)) {
        sscanf(buffer, "%6[^,],%6[^,],%100[^,],%d,%7[^,],%7[^,],%50[^,],%d,%d,%d,%d,%d",
               tmp->ID, tmp->stockID, tmp->productName, &tmp->price, tmp->imports,
               tmp->exports, tmp->category, &tmp->stock, &tmp->access,
               &tmp->addToCart, &tmp->buy, &tmp->key);
        *productTree = insertNodeAVL(*productTree, createNode(tmp->ID, tmp->stockID, tmp->productName,
                                                              tmp->price, tmp->imports, tmp->exports,
                                                              tmp->category, tmp->stock, tmp->access,
                                                              tmp->addToCart, tmp->buy));
    }
    fclose(fp);
    free(tmp);
}

void userMenu(AVL_Tree *productTree) {
    int choice;
    char searchProduct[50];

    do {
        printf("Enter your choice (1-3 or -1 to exit): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Product You want to find: ");
                scanf("%s", searchProduct);
                search(searchProduct, productTree);
                break;
            case 2:
                shop(productTree, ALL_CATEGORY_FILE_PATH);
                break;
            case 3:
                if (!history(USER_HISTORY_FILE_PATH, 2)) {
                    printf("File doesn't exist.\n");
                } else {
                    printf("Completed.\n");
                }
                break;
            case -1:
                printf("Exiting...\n");
                break;
            default:
                printf("Please enter a number between 1-3.\n");
        }
    } while (choice != -1);
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
