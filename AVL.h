#include<stdio.h>

typedef struct AVL_Tree{
    char ID[6]; // ไอดีสินค้า
    char stockID[6]; // ไอดีสต็อก
    char imports[7]; // วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]
    char exports[7]; // วันสินค้าออก[รูปแบบวันที่ DDMMYY]
    char category[50]; // หมวดหมู่
    int stock; // จำนวนสินค้าคงคลัง
    int access; // จำนวนการกดดูสินค้านั้นๆ
    int addToCart; // จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า
    int buy; // จำนวนการซื้อ(ครั้ง)
    int heightOfTree; // สำหรับความสูงของต้นไม้
    int key; // ค่าที่เอาไว้วัดระดับการ insert มาจาก access + addToCart + buy
    struct AVL_Tree *left, *right;
}AVL_Tree;