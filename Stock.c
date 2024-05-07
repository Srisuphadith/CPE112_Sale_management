#include <stdio.h>
#include <AVL.h>
#include <stdlib.h>
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
- ต้อง traversal พร้อมเช็คเรื่อยๆ ถ้าใช่ก็ใส่ลงใน arr
- return เมื่อ traversal ครบเท่านั้น
*/

char **stock_alert(struct AVL_Tree *node){
    if( node == NULL)
        return;
    if( node->stock <= 10){
        char 
    }
}

//การแจ้งเตือนวันที่ที่แต่ละ vender จะนำสินค้ามาลงในโกดังเรา เพื่อเป็นการบอก heads up ล่วงหน้า เพื่อให้เรา manage ว่าจะให้เขาลงสินค้ากี่ชิ้น เพื่อไม่ให้เกิดเหตุการณ์สินค้าล้นโกดัง ...or other incidents?
void noti_over_stock(){}