#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#define Catagories 4

/*----------------------------AVL_Tree----------------------------*/
typedef struct AVL_Tree {
  char ID[6];            // ไอดีสินค้า
  char stockID[6];       // ไอดีสต็อก
  char productName[100]; // ชื่อสินค้า
  int price;             // ราตาสินค้า
  char imports[7]; // วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]
  char exports[7]; // วันสินค้าออก[รูปแบบวันที่ DDMMYY]
  char category[50]; // หมวดหมู่
  int stock;         // จำนวนสินค้าคงคลัง
  int access; // จำนวนการกดดูสินค้านั้นๆ
  int addToCart; // จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า
  int buy;       // จำนวนการซื้อ(ครั้ง)
  int heightOfTree; // สำหรับความสูงของต้นไม้
  int key; // ค่าที่เอาไว้วัดระดับการ insert มาจาก access + addToCart + buy
  struct AVL_Tree *left, *right;
} AVL_Tree;

/*----------------------------out_of_stock_list----------------------------*/
typedef struct out_of_stock_list {
  char ID[6];
  struct out_of_stock_list *next;
} out_of_stock_list;

/*----------------------------Catagories----------------------------*/
char catagories[Catagories][50] = {"A", "B", "C", "D"};

// Initialize the matrix to zero
void init(int arr[][Catagories]) {
  int i, j;
  for (i = 0; i < Catagories; i++)
    for (j = 0; j < Catagories; j++)
      arr[i][j] = 0;
}
/*0 1 2 3 4 5
0   5 6
1 5
2 6
3
4
5
*/

// Add edges
void addEdge(int arr[][Catagories], int i, int j, int edgeValue) {
  arr[i][j] = edgeValue;
  arr[j][i] = edgeValue;
}


/*-----------------------------------------------*/
struct Node_LL_Key {
    int data_key;
    struct AVL_Tree* node;
    struct Node_LL_Key* next;  // Now using Node_LL_Key for next pointer
};
#endif // AVL_H