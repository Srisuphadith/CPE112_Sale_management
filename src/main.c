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

int history(char file[], int user_id);

int main() {
  int choice;

  if (/*registerfunction == True*/ 1) {
    char username[20], date[7];
    AVL_Tree *init = NULL, *tmp = (AVL_Tree *)malloc(sizeof(AVL_Tree));
    // struct Node_LL_Key *head = NULL;
    //เปิดไฟล์
    FILE *fp = fopen("../csv/product.csv", "r");
    char buffer[255];
    while (fgets(buffer, 255, fp)) {
      // printf("debug1\n");
      //  printf("--%s--",buffer);
      sscanf(buffer,
             "%6[^,],%6[^,],%100[^,],%d,%7[^,],%7[^,],%50[^,],%d,%d,%d,%d,%d",
             tmp->ID, tmp->stockID, tmp->productName, &tmp->price, tmp->imports,
             tmp->exports, tmp->category, &tmp->stock, &tmp->access,
             &tmp->addToCart, &tmp->buy, &tmp->key);

      // printf("%d\n" , tmp->key);
      // printf("debug2\n");
      init = insertNodeAVL(init, createNode(tmp->ID, tmp->stockID, tmp->productName,
                        tmp->price, tmp->imports, tmp->exports, tmp->category,
                        tmp->stock, tmp->access, tmp->addToCart, tmp->buy));
                        
      // printf("debug3\n");
      printf("%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d\n", tmp->ID, tmp->stockID,
             tmp->productName, tmp->price, tmp->imports, tmp->exports,
             tmp->category, tmp->stock, tmp->access, tmp->addToCart, tmp->buy,
             tmp->key);
    }
    fclose(fp);
    free(tmp);

    scanf("%d", &choice);
    // user part
    if (/*user*/ 1) {

      switch (choice) {
      case 1:
        char searchProduct[50];
        printf("Enter Product You want to find :");
        scanf("%s", searchProduct);
        search(searchProduct, init);
        // buying_from_id("userHistory.csv", username, date, "product.csv");
        break;

      case 2:
        shop(init, "allCategory.csv");

        // buying_from_id("userHistory.csv", username, date, "product.csv");
        break;

      case 3:
        /*history*/
        //วิธีใช้ เเละวิธีเช็ค
        if (!history("userHistory.csv",2))
        {
            printf("file doesnt exits");
        }
        else
        {
            printf("completly");
        }
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

// int history_sh(char file_name[], int user_id) {
//   FILE *fp = fopen(file_name, "r");
//   if (fp == NULL) {
//     return 0;
//   }
//   char buffer[255][255];
//   int i = 0;
//   while (fgets(buffer[i], 255, fp)) {
//     i++;
//   }
  // for(int j = 0;j<=i;j++){
  //     printf("%s",bff[j]);
  // }
//   fclose(fp);
//   return 1;
// }

int history(char file[], int user_id)
{
    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("You didn't buy anything.\n");
        return 0;
    }

    // struct AVL_Tree *newNode = NULL;
    int user,id;
    char date[7];
    char proID[7];
    while (fscanf(fp, "%d,%d,%7[^,],%6[^,]",&id,&user,date,proID) != EOF)
    {
      if(user_id == user){
        printf("User: %d\n", user_id);
        printf("Name of product: %s\n",proID);
        printf("------------------------------------------\n");
      }
    }

    fclose(fp);
    return 1;
}