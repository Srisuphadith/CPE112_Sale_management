#include "AVL.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------
//#include "admin_report.c"
// #include "Manage_Stock_Func.c"
#include "Sell_Product_Func.c"
// #include "Stock.c"
#include "shop.c"

int history_sh(char file_name[], int user_id);

int main() {
  int choice;

  if (/*registerfunction == True*/ 1) {
    AVL_Tree *init = NULL, *tmp = (AVL_Tree*)malloc(sizeof(AVL_Tree));
    //เปิดไฟล์
    FILE *fp = fopen("product.csv", "r");
    while (
        fscanf(
            fp,
            "%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%d,%d,%d,%d,%d",
            tmp->ID, tmp->stockID, tmp->productName, &tmp->price, tmp->imports,
            tmp->exports, tmp->category, &tmp->stock, &tmp->access,
            &tmp->addToCart, &tmp->buy, &tmp->key) != EOF) {

      init = insert_AVL(init, tmp->ID, tmp->stockID, tmp->productName,
                        tmp->price, tmp->imports, tmp->exports, tmp->category,
                        tmp->stock, tmp->access, tmp->addToCart, tmp->buy);
    }
    fclose(fp);
    free(tmp);

    scanf("%d", &choice);
    // user part
    if (/*user*/ 1) {

      switch (choice) {
      case 1:
        /* search */
        break;

      case 2:
        shop(init, "allCategory.csv");
        break;

      case 3:
        /*history*/
        //วิธีใช้ เเละวิธีเช็ค
        // if (!history_sh("user.txt",12))
        // {
        //     printf("file doesnt exits");
        // }
        // else
        // {
        //     printf("completly");
        // }
        break;

      case -1:
        /*exit*/
        break;

      default:
        printf("please enter number between 1-3");
      }
      /*shop function*/

      // admin part
    } else /*admin*/
    {

      switch (choice) {
      case 1:
        /* stock manage */
        break;

      case 2:
        /*report ***optional*/
        break;

      case -1:
        /*exit*/
        break;

      default:
        printf("please enter number between 1-2");
      }
    }
  } else {
    printf("username or password is not valid.");
  }
}

int history_sh(char file_name[], int user_id) {
  FILE *fp = fopen(file_name, "r");
  if (fp == NULL) {
    return 0;
  }
  char buffer[255][255];
  int i = 0;
  while (fgets(buffer[i], 255, fp)) {
    i++;
  }
  // for(int j = 0;j<=i;j++){
  //     printf("%s",bff[j]);
  // }
  fclose(fp);
  return 1;
}

// int history(struct AVL_Tree *root, const char file[], int user_id, int buy)
// {
//     FILE *fp = fopen(file, "r");
//     if (fp == NULL)
//     {
//         printf("You didn't buy anything.\n");
//         return 0;
//     }

//     struct AVL_Tree *newNode = NULL;
//     while (fscanf(fp, " %s %s %d", newNode->ID, newNode->NameofProduct,
//     &newNode->buy) != EOF)
//     {
//         printf("User: %d\n", user_id);
//         printf("Name of product: %s, ID: %s, Quantity: %d\n",
//         newNode->NameofProduct, newNode->ID, newNode->buy);
//         printf("------------------------------------------\n");
//     }

//     fclose(fp);
//     return 1;
// }
