#include "AVL.c"
#include "Sell_Product_Func.c"
#include "shop.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void loadProducts(AVL_Tree **init);
void userMenu(AVL_Tree *init);
int history(char file[], int user_id);

int main() {
    AVL_Tree *init = NULL;
    loadProducts(&init);
    userMenu(init);
    return 0;
}

void loadProducts(AVL_Tree **init) {
    AVL_Tree *tmp = (AVL_Tree *)malloc(sizeof(AVL_Tree));
    FILE *fp = fopen("../csv/product.csv", "r");
    char buffer[255];
    while (fgets(buffer, 255, fp)) {
        sscanf(buffer, "%6[^,],%6[^,],%100[^,],%d,%7[^,],%7[^,],%50[^,],%d,%d,%d,%d,%d",
               tmp->ID, tmp->stockID, tmp->productName, &tmp->price, tmp->imports,
               tmp->exports, tmp->category, &tmp->stock, &tmp->access,
               &tmp->addToCart, &tmp->buy, &tmp->key);
        *init = insertNodeAVL(*init, createNode(tmp->ID, tmp->stockID, tmp->productName,
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

void userMenu(AVL_Tree *init) {
    int choice;
    char searchProduct[50];
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
