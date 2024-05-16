#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <stdio.h>

struct Product
{
    // char ID[6]; //1 , 2 ,3 ,4 ,5
    // char StockID[6]; //S001 , S002 , S003
    // char ProductName[100];
    // char ImportDate[7];
    // char ExportDate[7];
    // char Categories[50];
    // int Inventories;
    // int NumVisits;
    // int NumPurchases;
    char ID[6];            //key                    // ไอดีสินค้า
    char stockID[6];                                // ไอดีสต็อก
    char productName[100];                          // ชื่อสินค้า
    int price;                                      // ราตาสินค้า
    char imports[7];                                // วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]
    char exports[7];                                // วันสินค้าออก[รูปแบบวันที่ DDMMYY]
    char category[50];                              // หมวดหมู่
    int stock;                                      // จำนวนสินค้าคงคลัง
    int access;                                     // จำนวนการกดดูสินค้านั้นๆ
    int addToCart;                                  // จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า
    int buy;                                        // จำนวนการซื้อ(ครั้ง)
    int key;              //Key                     // ค่าที่เอาไว้วัดระดับการ insert มาจาก access + addToCart + buy
    struct Product *next;
};

struct User
{
    int UserID; //Key
    char Username[100]; //Key
    char Password[100];
    char Role[20]; //admin  //user
    
    struct User *next;
};

struct History
{
    // char Timestamp[20];
    // char User[100];
    // char Action[100];
    // char Details[100];
    int id; //Key
    int user_id; //Key
    char date[7];
    char pro_id[6];
    struct History *next;
};

struct PurchaseHistory
{
    int UserID; //Key
    char StockID[20]; //Key
    int Quantity; 
    struct PurchaseHistory *next;
};

struct CartItem
{
    int key; //Key
    int quantity;
    char IDstock[20]; 
    struct CartItem *next;
};

// current session
struct ProductSales
{
    /*------------------LL-------------------*/
    struct Product *products;
    struct User *users;
    struct History *user_history;
    struct PurchaseHistory *purchase_history;
    struct CartItem *cart;
    /*---------------------------------------*/
    struct User *current_user;
    int product_count;
    int user_count;
    int user_history_count;
    int user_category_history_count;
    int purchase_history_count;
    int cart_count;
};

#endif