#include "AVL.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sell_Product_Func.c"
#include "shop.c"

int history(char file[], int user_id);

int main() {
    int choice;
    char searchProduct[50];

    // Assuming the registration function is always successful for this example.
    if (1) {
        char username[20], date[7];
        AVL_Tree *init = NULL;
        AVL_Tree *tmp = (AVL_Tree *)malloc(sizeof(AVL_Tree));

        // Open product file
        FILE *fp = fopen("../csv/product.csv", "r");
        if (fp == NULL) {
            perror("Failed to open product file");
            return EXIT_FAILURE;
        }

        char buffer[255];
        while (fgets(buffer, sizeof(buffer), fp)) {
            sscanf(buffer, "%6[^,],%6[^,],%100[^,],%d,%7[^,],%7[^,],%50[^,],%d,%d,%d,%d,%d",
                   tmp->ID, tmp->stockID, tmp->productName, &tmp->price, tmp->imports,
                   tmp->exports, tmp->category, &tmp->stock, &tmp->access,
                   &tmp->addToCart, &tmp->buy, &tmp->key);

            init = insertNodeAVL(init, createNode(tmp->ID, tmp->stockID, tmp->productName,
                                                  tmp->price, tmp->imports, tmp->exports, tmp->category,
                                                  tmp->stock, tmp->access, tmp->addToCart, tmp->buy));

            printf("%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d\n", tmp->ID, tmp->stockID,
                   tmp->productName, tmp->price, tmp->imports, tmp->exports,
                   tmp->category, tmp->stock, tmp->access, tmp->addToCart, tmp->buy,
                   tmp->key);
        }
        fclose(fp);
        free(tmp);

        printf("Enter your choice (1-3 or -1 to exit): ");
        scanf("%d", &choice);

        // User part
        if (1) {
            switch (choice) {
                case 1:
                    printf("Enter Product You want to find: ");
                    scanf("%s", searchProduct);
                    search(searchProduct, init);
                    break;

                case 2:
                    shop(init, "../csv/allCategory.csv");
                    break;

                case 3:
                    if (!history("../csv/userHistory.csv", 2)) {
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
        } else {
            // Admin part (assuming the placeholder condition is for admin check)
            switch (choice) {
                case 1:
                    // Stock management
                    break;

                case 2:
                    // Report generation (optional)
                    break;

                case -1:
                    printf("Exiting...\n");
                    break;

                default:
                    printf("Please enter a number between 1-2.\n");
            }
        }
    } else {
        printf("Username or password is not valid.\n");
    }
    return 0;
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
