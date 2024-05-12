// shop (การแสดงข้อมูล)
#include "AVL.c"
#include "Manage_Stock_Func.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// search เพื่อหาของนั้นเลย คือการ search

// shop คือการเข้ามาดูของ ให้เลือกคือ ฮิต หรือ การเลือกประเภทเอง
// ถ้าเลือกประเภทและแสดงของในประเภท เมื่อหมดก็แสดงประเภทใกล้เคียง

void searchProduct(struct AVL_Tree *node, char *category) {
  if (node == NULL) {
    return;
  }

  reverse_inOrder(node->right);
  if (strcmp(node->category, category) == 0) {
    displayNode(node);
  }
  reverse_inOrder(node->left);
}

void shop(struct AVL_Tree *node, char *file) {
  int choice, userChoice, i = -1;
  char category[50], switchCat[10][50];
  FILE *allCategories = fopen(file, "r");

  if (allCategories == NULL)
    printf("Error! opening file");

  printf("Categories\n");
  while (fscanf(allCategories, "%d,%[^,]", &choice, category) != EOF) {
    strcpy(*switchCat+(i++), category);
    printf("%d,%s,%s\n", choice, category,switchCat[i]);
  }

  printf("-1 : Go backward\n");
  printf("What Category you want:\n");
  scanf("%d", &choice);

  if (choice > 0 && choice < i) {
    filter_from_cat(node, switchCat[i]);
  } else {
    printf("please enter number between 0 to %d or -1 to exit \n", i);
  }
}

void buying_from_id(struct AVL_Tree *node, char *file) {}

// int main()
// {
// }


// ตรวจสอบจำนวนสินค้า
int check_counting_stock(struct AVL_Tree *node, char ID[6]) {

  if (node == NULL) {
    return 0;
  }
  struct AVL_Tree *temp = searchAVL(node, ID);
  if (temp == NULL)
    return 0;
  else
    return temp->stock;
}

// การแจ้งเตือนสินค้าคงคลัง: แจ้งเตือนเมื่อสินค้าใกล้หมดสต็อก [เหลือ 10 ชิ้น] ***แจ้งเป็น stock id
// (return arr IDs)***
/*
- ต้องทราบค่าสินค้าทั้งหมดที่มี แล้ว assume สินค้าใกล้หมดพร้อมกัน 5% ของทั้งหมด
*/
int assume_out_of_stock_product(struct AVL_Tree *node) {
  return (int)((5 / 100) * (pow((double)2, (double)height(node))));
}

/*
- ต้อง traversal พร้อมเช็คเรื่อยๆ ถ้าใช่ก็ใส่ลงใน arr
- return เมื่อ traversal ครบเท่านั้น
*/
// char **stock_alert(struct AVL_Tree *node){
//     //check end
//     if( node == NULL)
//         return;

//     //2D array with char
//     /*
//     format out_of_stock_ID : {{AAAAA},{BBBBB}}
//     meaning stock AAAAA , BBBBB product in stock less than 10
//     */
//     int rows =assume_out_of_stock_product(node);
//     char **out_of_stock_ID = (char **)malloc(rows * sizeof(char *));
//     if (out_of_stock_ID == NULL) {
//         printf("Memory allocation failed.\n");
//         return NULL;
//     }

//     for (int i = 0; i < rows; i++) {
//         out_of_stock_ID[i] = (char *)malloc(6/*stock id have only 5
//         character*/ * sizeof(char)); // +1 for the null terminator if
//         (out_of_stock_ID[i] == NULL) {
//             printf("Memory allocation failed.\n");
//             // Free previously allocated memory to avoid memory leaks
//             for (int j = 0; j < i; j++) {
//                 free(out_of_stock_ID[j]);
//             }
//             free(out_of_stock_ID);
//             return NULL;
//         }
//     }

//     // check less than 10 to add to arr
//     if( node->stock <= 10){
//     }

// }
//เก็บในรูปเเบบ linked list ของ out of stock เพิ่ม datatype ใหม่ใน AVL.h ชื่อ
//out_of_stock_list
void stock_alert(AVL_Tree *tree, out_of_stock_list *head) {

  if (tree->right != NULL) {
    stock_alert(tree->right, head);
  }
  if (tree->stock <= 5) {
    printf("Out of stock ID = %s\n", tree->ID);
    if (head == NULL) {
      out_of_stock_list *newNode =
          (out_of_stock_list *)malloc(sizeof(out_of_stock_list));
      newNode->next = NULL;
      strcpy(newNode->ID, tree->ID);
      head = newNode;
    } else {
      out_of_stock_list *ptr = head;
      while (ptr->next != NULL) {
        ptr = ptr->next;
      }
      out_of_stock_list *newNode =
          (out_of_stock_list *)malloc(sizeof(out_of_stock_list));
      newNode->next = NULL;
      strcpy(newNode->ID, tree->ID);
      ptr->next = newNode;
    }
  }
  if (tree->left != NULL) {
    stock_alert(tree->left, head);
  }
  return;
}

//การแจ้งเตือนวันที่ที่แต่ละ vender จะนำสินค้ามาลงในโกดังเรา
/*
- เป้นลิสไว้ว่า
    - A Company 12/05/67
    - B Company 13/05/67
*/
void import_date() {}

// #endif // Manage_Stock_Func_c

int findStringLength(char str[])
{
  int i = 0, lenght = 0;
  while (*str != '\0')
  {
    lenght++;
    str++;
  }
  return lenght;
}

int findSubString(char *string1, char *string2)
{
  int count = 0, j;
  char *output;
  output = NULL;
  for (j = 0; string1[j] != '\0'; j++)
  {
    if (string2[count] != '\0')
    {
      if (string1[j] == string2[count])
      {
        count++;
        if (count == 1)
          output = &string1[j];
      }
      else
        count = 0;
    }
    if (count == findStringLength(string2))
      break;
  }
  if (output != NULL)
    return output - string1;
  else
  {
    return 0;
  }
}

// int main()
// {
//     char *string1, *string2;
//     char *output;

//     string1 = "I love CPE";
//     string2 = "love";
//     if (findSubString(string1, string2) != 0)
//         printf("Index of the first occurance = %ld\n", findSubString(string1,
//         string2));
//     else
//         printf("string2 is not a substring of string1\n");

//     return 0;
// }

void search(char *productName, AVL_Tree *node)
{
  if (node == NULL)
    node = node->right;
  if (findSubString(productName, node->productName) != 0)
  {
    show_shop_item(node);
  }
  node = node->left;
}

int main(void)
{
  AVL_Tree *root = NULL;
  char userSearch[100];
  scanf("%s", userSearch);
  search(userSearch, root);
  return 0;
}