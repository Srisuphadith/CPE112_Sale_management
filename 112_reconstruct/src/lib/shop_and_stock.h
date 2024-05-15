#ifndef SHOP_AND_STOCK_H
#define SHOP_AND_STOCK_H
#include "AVL.c"
#include "Manage_Stock_Func.c"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

buying_from_id(char file, int user, char date, char stockFile);

int buying_from_id(const char *file, int user, const char *date, const char *stockFile) {
    char buyItem[7];
    int i = 0, isSuccess = 0;
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return -1;
    }
    
    char last_buffer[255];
    int x = 0;

    // Read the last line to get the last ID
    while (fgets(last_buffer, sizeof(last_buffer), fp)) {
        if (sscanf(last_buffer, "%d", &x) != 1) {
            x = 0;
        }
    }
    fclose(fp);

    printf("Please Enter Product ID : ");
    scanf("%6s", buyItem); // Ensure only 6 characters are read

    fp = fopen(file, "a+");
    if (fp == NULL) {
        perror("Failed to open file");
        return -1;
    }
    x++;
    fprintf(fp, "\n%d,%d,%s,%s", x, user, date, buyItem);
    fclose(fp);

    AVL_Tree *tmp = (AVL_Tree *)malloc(1000 * sizeof(AVL_Tree));
    if (!tmp) {
        perror("Failed to allocate memory");
        return -1;
    }

    fp = fopen(stockFile, "r");
    if (!fp) {
        perror("Failed to open stock file");
        free(tmp);
        return -1;
    }

    while (fgets(last_buffer, sizeof(last_buffer), fp)) {
        if (sscanf(last_buffer,
                   "%5[^,],%5[^,],%99[^,],%d,%6[^,],%6[^,],%49[^,],%d,%d,%d,%d,%d",
                   tmp[i].ID, tmp[i].stockID, tmp[i].productName, &tmp[i].price,
                   tmp[i].imports, tmp[i].exports, tmp[i].category, &tmp[i].stock,
                   &tmp[i].access, &tmp[i].addToCart, &tmp[i].buy, &tmp[i].key) == 12) {

            if (strcmp(tmp[i].ID, buyItem) == 0 && tmp[i].stock > 0 && isSuccess != 1) {
                isSuccess = 1;
                tmp[i].stock--;
            }
            i++;
        }
    }
    fclose(fp);

    fp = fopen(stockFile, "w");
    if (!fp) {
        perror("Failed to open stock file for writing");
        free(tmp);
        return -1;
    }

    for (int j = 0; j < i; j++) {
        fprintf(fp, "%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d\n", 
                tmp[j].ID, tmp[j].stockID, tmp[j].productName, tmp[j].price,
                tmp[j].imports, tmp[j].exports, tmp[j].category, tmp[j].stock,
                tmp[j].access, tmp[j].addToCart, tmp[j].buy, tmp[j].key);
    }

    free(tmp);
    fclose(fp);

    return isSuccess;
}


#endif