#include <stdio.h>
#include <AVL.h>
#include <stdlib.h>
#include<math.h>
#include "Manage_Stock_Func.c"
//การจัดการสต็อกสินค้า

// ตรวจสอบจำนวนสินค้า
int check_counting_stock(struct AVL_Tree *node, char ID[6]/*ไอดีสินค้า*/){
    if(search_AVL(node , ID) == 1){
        return node->stock;
    }
}


// การแจ้งเตือนสินค้าคงคลัง: แจ้งเตือนเมื่อสินค้าใกล้หมดสต็อก [เหลือ 10 ชิ้น] ***แจ้งเป็น stock id (return arr IDs)***
/*
- ต้องทราบค่าสินค้าทั้งหมดที่มี แล้ว assume สินค้าใกล้หมดพร้อมกัน 5% ของทั้งหมด
*/
int assume_out_of_stock_product(struct AVL_Tree *node){
    return (int)((5/100)*(pow((double)2 , (double)height(node))));
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
//         out_of_stock_ID[i] = (char *)malloc(6/*stock id have only 5 character*/ * sizeof(char)); // +1 for the null terminator
//         if (out_of_stock_ID[i] == NULL) {
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
//เก็บในรูปเเบบ linked list ของ out of stock เพิ่ม datatype ใหม่ใน AVL.h ชื่อ out_of_stock_list
void stock_alert(AVL_Tree *tree, out_of_stock_list *head)
{

    if (tree->right != NULL)
    {
        stock_alert(tree->right, head);
    }
    if (tree->stock <= 5)
    {
        printf("Out of stock ID = %s\n", tree->ID);
        if (head == NULL)
        {
            out_of_stock_list *newNode = (out_of_stock_list *)malloc(sizeof(out_of_stock_list));
            newNode->next = NULL;
            strcpy(newNode->ID, tree->ID);
            head = newNode;
        }
        else
        {
            out_of_stock_list *ptr = head;
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            out_of_stock_list *newNode = (out_of_stock_list *)malloc(sizeof(out_of_stock_list));
            newNode->next = NULL;
            strcpy(newNode->ID, tree->ID);
            ptr->next = newNode;
        }
    }
    if (tree->left != NULL)
    {
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
void import_date(){}