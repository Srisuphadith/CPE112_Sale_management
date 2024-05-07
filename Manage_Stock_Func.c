#include <stdio.h>
#include <AVL.h>
#include <stdlib.h>
#include <string.h>

struct AVL_Tree*createnode(char ID[6]/*ไอดีสินค้า*/, char stockID[6]/*ไอ่ดีสต็อค*/, char imports[7]/*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, char exports[7]/*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, int stock, int access/*จำนวนการกดดูสินค้านั้นๆ*/ ,int addToCart/*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/ ,int buy/*จำนวนการซื้อ(ครั้ง)*/ ,int heightOfTree/*สำหรับหมุนต้นไม้*/){
    struct AVL_Tree* newnode = (struct AVL_Tree*)malloc(sizeof(struct AVL_Tree));
    strcmp(newnode->ID,ID);
    strcmp(newnode->stockID,stockID);
    strcmp(newnode->imports,imports);
    strcmp(newnode->exports,exports);
    newnode->stock=stock;
    newnode->access=access;
    newnode->addToCart=addToCart;
    newnode->buy=buy;
    newnode->heightOfTree=1;

    newnode->left=NULL;
    newnode->right=NULL;
    
    return newnode;
}

int height(struct AVL_Tree *N){
    if(N == NULL)
        return 0;
    return N->heightOfTree;
}

int maxof(int a, int b){
    return (a>b) ? a:b;
}

//เพิ่มสินค้าใน AVL Tree
// เพิ่ม
// กรอกข้อมูลสินค้า เช่น ชื่อ รหัส
// ุจำนวนสินค้าคงคลัง

struct AVL_Tree *add_AVL(struct AVL_Tree*node, char ID[6]/*ไอดีสินค้า*/, char stockID[6]/*ไอ่ดีสต็อค*/, char imports[7]/*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, char exports[7]/*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, int stock, int access/*จำนวนการกดดูสินค้านั้นๆ*/ ,int addToCart/*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/ ,int buy/*จำนวนการซื้อ(ครั้ง)*/ ,int heightOfTree/*สำหรับหมุนต้นไม้*/){
    if(node == NULL)
        return createnode(ID[6]/*ไอดีสินค้า*/, stockID[6]/*ไอ่ดีสต็อค*/, imports[7]/*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, exports[7]/*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, stock, access/*จำนวนการกดดูสินค้านั้นๆ*/ , addToCart/*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/ , buy/*จำนวนการซื้อ(ครั้ง)*/ , heightOfTree/*สำหรับหมุนต้นไม้*/);

    //if()
}


//แก้ไขสินค้าใน BS Tree
// แก้ไขสินค้า
// แก้ไขข้อมูลสินค้า
// เปลี่ยนแปลงจำนวนสินค้า
void edit_BS(){}

//ลบสินค้าใน BS Tree
void del_BS(){}

//ค้นหาสินค้าใน BS_Tree
// ค้นหาสินค้า
// ค้นหาสินค้าตามชื่อ รายละเอียด หมวดหมู่
// ค้นหาสินค้าตามราคา
// ค้นหาสินค้าตามจำนวนสินค้า
void search_BS(){}

//กรองสินค้าใน BS_Tree
// กรองสินค้า
// กรองสินค้าตามหมวดหมู่/ราคา/จำนวนสินค้า
void filter_BS(){}

//หมุน BS_Tree
void rotate_BS(){}

//Traversal BS_Tree To show suggestion right->root->left
void reverse_inorder(){}
