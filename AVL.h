#include<stdio.h>

typedef struct AVL_Tree{
    char ID[6]/*ไอดีสินค้า*/ , stockID[6]/*ไอ่ดีสต็อค*/ , imports[7]/*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/ , exports[7]/*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/;
    int stock/*ของคงคลัง*/ , access/*จำนวนการกดดูสินค้านั้นๆ*/ , addToCart/*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/ , buy/*จำนวนการซื้อ(ครั้ง)*/ , heightOfTree/*สำหรับหมุนต้นไม้*/;
    int key;/*ค่าที่เอาไว้วัดระดับการinsert มาจากaccess+addToCart+buy*/
    struct AVL_Tree* left , * right;
}AVL_Tree;