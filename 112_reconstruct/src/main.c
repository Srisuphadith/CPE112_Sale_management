#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Structure.h"

/**
 * @file main.c
 * @brief This file contains the definitions of various maximum limits used in the program.
 *
 * This file defines the maximum limits for products, users, history, cart items, and line length.
 * These limits are used throughout the program to ensure that arrays and buffers are not exceeded.
 */
#define MAX_PRODUCTS 100         /**< The maximum number of products */
#define MAX_USERS 100            /**< The maximum number of users */
#define MAX_HISTORY 100          /**< The maximum number of history entries */
#define MAX_CART_ITEMS 100       /**< The maximum number of items in a cart */
#define MAX_LINE_LENGTH 1024     /**< The maximum length of a line */
#define BUFFER_SIZE 255

//Function prototypes
void clear_terminal();
void load_data(struct ProductSales *ps);
struct Product *createNode_StrProduct(char ID[], char stockID[], char productName[], int price,char imports[], char exports[], char category[],int stock, int access, int addToCart, int buy, int key);
struct User* createNode_User(char Username[], char Password[], char Role[], int UserID);
struct History* createNode_History(int id,int user_id,char date[7],char pro_id[6]);
struct PurchaseHistory* createNode_PurchaseHistory(int UserID, char StockID[], int Quantity);
struct CartItem* createNode_CartItem(int key, int quantity);
void insertNode(struct Product **head, struct Product *newNode);
struct User* searchUserByUsername(struct User *head, char Username[]);
struct User* searchUserByID(struct User *head, int UserID);
struct User *searchUserByUsernameAndPassword(struct User *head, char *username, char *password);
struct History* searchHistoryById(struct History *head, int id);
struct History* searchHistoryByuser_id(struct History *head, int user_id);
struct PurchaseHistory* searchPurchaseHistoryByUserID(struct PurchaseHistory *head, int UserID);
struct PurchaseHistory* searchPurchaseHistoryByStockID(struct PurchaseHistory *head, char StockID[]);
struct CartItem* searchCartItemByKey(struct CartItem *head, int key);
void log_activity(struct ProductSales *ps, char *action, char *details);
void remove_newline(char *str);
void login(struct ProductSales *ps);
void register_user(struct ProductSales *ps , char *userLoginFile);
void main_menu(struct ProductSales *ps);
void admin_menu(struct ProductSales *ps);
void manage_products(struct ProductSales *ps);
void view_products(struct ProductSales *ps, char outputFileName[]);
void add_product(struct ProductSales *ps);
void update_product(struct ProductSales *ps);
void delete_product(struct ProductSales *ps);
void view_orders(struct ProductSales *ps);
void generate_report(struct ProductSales *ps);
void customer_menu(struct ProductSales *ps);
void swap(struct Product **a, struct Product **b);
void printNode(struct Product **start);
void view_recommended_products(struct ProductSales *ps);
void product_detail(struct ProductSales *ps , char *stockId);
void add_to_cart(struct ProductSales *ps);
void add_to_cart_to(struct ProductSales *ps);
void view_cart(struct ProductSales *ps);
void checkout(struct ProductSales *ps);
void view_all_products(struct ProductSales *ps);
void run(struct ProductSales *ps);

void clear_terminal()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}
// load_data ดีเเล้ว------------------------------------------------------------------------------------------------------------------------------------------------
void load_data(struct ProductSales *ps)
{
    // Load data from CSV files here
    FILE *fp1 = fopen("csv/product.csv", "r");
    FILE *fp2 = fopen("csv/userHistory.csv", "r");
    FILE *fp3 = fopen("csv/login.csv", "r");
    
    // Check if the files were opened successfully
    if (!fp1 || !fp2 || !fp3) {
        printf("Failed to open one or more files.\n");
        return;
    }

    char buffer[BUFFER_SIZE];
    struct Product *head = NULL;
    struct Product *tail = NULL;

    while (fgets(buffer, BUFFER_SIZE, fp1))
    {
        struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
        if (!newNode) {
            printf("Memory allocation failed.\n");
            return;
        }
        sscanf(buffer, "%6[^,],%6[^,],%100[^,],%d,%7[^,],%7[^,],%50[^,],%d,%d,%d,%d,%d",
               newNode->ID, newNode->stockID, newNode->productName, &newNode->price, newNode->imports,
               newNode->exports, newNode->category, &newNode->stock, &newNode->access,
               &newNode->addToCart, &newNode->buy, &newNode->key);
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    ps->products = head;

    struct History *head1 = NULL;
    struct History *tail1 = NULL;

    while (fgets(buffer, BUFFER_SIZE, fp2))
    {
        struct History *newNode = (struct History *)malloc(sizeof(struct History));
        if (!newNode) {
            printf("Memory allocation failed.\n");
            return;
        }
        sscanf(buffer, "%d,%d,%7[^,],%6[^,]", &newNode->id, &newNode->user_id, newNode->date, newNode->pro_id);
        newNode->next = NULL;

        if (head1 == NULL)
        {
            head1 = newNode;
            tail1 = newNode;
        }
        else
        {
            tail1->next = newNode;
            tail1 = newNode;
        }
    }

    ps->user_history = head1;

    struct User *head2 = NULL;
    struct User *tail2 = NULL;

    while(fgets(buffer,BUFFER_SIZE,fp3)){
        struct User *newNode = (struct User *)malloc(sizeof(struct User));
        if (!newNode) {
            printf("Memory allocation failed.\n");
            return;
        }
        sscanf(buffer,"%d,%100[^,],%100[^,],%20[^,]",&newNode->UserID,newNode->Username,newNode->Password,newNode->Role);
        newNode->next = NULL;

        if (head2 == NULL)
        {
            head2 = newNode;
            tail2 = newNode;
        }
        else
        {
            tail2->next = newNode;
            tail2 = newNode;
        }
    }

    ps->users = head2;
    
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}


struct Product *createNode_StrProduct(char ID[], char stockID[], char productName[], int price,
                                      char imports[], char exports[], char category[],
                                      int stock, int access, int addToCart, int buy, int key)
{
    struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->ID, ID);
    strcpy(newNode->stockID, stockID);
    strcpy(newNode->productName, productName);
    newNode->price = price;
    strcpy(newNode->imports, imports);
    strcpy(newNode->exports, exports);
    strcpy(newNode->category, category);
    newNode->stock = stock;
    newNode->access = access;
    newNode->addToCart = addToCart;
    newNode->buy = buy;
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

/*-------------------------------------------------------------------------------------------*/
struct User* createNode_User(char Username[], char Password[], char Role[], int UserID) {
    struct User *newNode = (struct User*)malloc(sizeof(struct User));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newNode->Username, Username);
    strcpy(newNode->Password, Password);
    strcpy(newNode->Role, Role);
    newNode->UserID = UserID;
    newNode->next = NULL;
    return newNode;
}
/*------------------------------------------------------------------------------------------*/
struct History* createNode_History(int id,int user_id,char date[7],char pro_id[6]) {
    struct History *newNode = (struct History*)malloc(sizeof(struct History));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->id = id;
    newNode->user_id = user_id;
    strcpy(newNode->date, date);
    strcpy(newNode->pro_id, pro_id);
    return newNode;
}

/*------------------------------------------------------------------------------------------*/
struct PurchaseHistory* createNode_PurchaseHistory(int UserID, char StockID[], int Quantity) {
    struct PurchaseHistory *newNode = (struct PurchaseHistory*)malloc(sizeof(struct PurchaseHistory));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->UserID = UserID;
    strcpy(newNode->StockID, StockID);
    newNode->Quantity = Quantity;
    newNode->next = NULL;
    return newNode;
}
/*------------------------------------------------------------------------------------------*/
struct CartItem* createNode_CartItem(int key, int quantity) {
    struct CartItem *newNode = (struct CartItem*)malloc(sizeof(struct CartItem));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->key = key;
    newNode->quantity = quantity;
    newNode->next = NULL;
    return newNode;
}
/*------------------------------------------------------------------------------------*/

// ฟังก์ชันสำหรับเพิ่มโหนดใหม่ไปยัง linked list
void insertNode(struct Product **head, struct Product *newNode)
{
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct Product *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void insertNodeUser(struct User **head , struct User *newNode){
        if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct User *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

//ฟังก์ชันสำหรับsearch

// ฟังก์ชันสำหรับค้นหาผู้ใช้จาก Username และ IDUsername password
struct User* searchUserByUsername(struct User *head, char Username[]) {
    struct User *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->Username, Username) == 0) {
            return temp; 
        }
        temp = temp->next;
    }
    return NULL;
}

struct User* searchUserByID(struct User *head, int UserID) {
    struct User *temp = head;
    while (temp != NULL) {
        if (temp->UserID== UserID) {
            return temp; 
        }
        temp = temp->next;
    }
    return NULL;
}

struct User *searchUserByUsernameAndPassword(struct User *head, char *username, char *password) {
    struct User *current = head;

    while (current != NULL) {
        if (strcmp(current->Username, username) == 0 && strcmp(current->Password, password) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; 
}
/*----------------------------------------------------------*/

// ฟังก์ชันสำหรับค้นหาประวัติการใช้งานโดยใช้ id user_id
struct History* searchHistoryById(struct History *head, int id) {
    struct History *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; 
}

struct History* searchHistoryByuser_id(struct History *head, int user_id) {
    struct History *temp = head;
    while (temp != NULL) {
        if (temp->user_id == user_id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL; 
}
/*--------------------------------------------------------------------*/

// ฟังก์ชันสำหรับค้นหาประวัติการซื้อสินค้าโดยใช้ UserID ,StockID[20]

struct PurchaseHistory* searchPurchaseHistoryByUserID(struct PurchaseHistory *head, int UserID) {
    struct PurchaseHistory *temp = head;
    while (temp != NULL) {
        if (temp->UserID == UserID) {
            return temp; 
        }
        temp = temp->next;
    }
    return NULL; 
}

struct PurchaseHistory* searchPurchaseHistoryByStockID(struct PurchaseHistory *head, char StockID[]) {
    struct PurchaseHistory *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->StockID, StockID) == 0) {
            return temp; 
        }
        temp = temp->next;
    }
    return NULL; 
}
/*------------------------------------------------------------------------------------*/

struct CartItem* searchCartItemByKey(struct CartItem *head, int key) {
    struct CartItem *temp = head;
    while (temp != NULL) {
        if (temp->key == key) {
            return temp; 
        }
        temp = temp->next;
    }
    return NULL; 
}
// log_activity ดีเเล้ว------------------------------------------------------------------------------------------------------------------------------------------------

void log_activity(struct ProductSales *ps, char *action, char *details)
{
    FILE *file;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char timestamp[20];
    char user[100];
    if(ps->current_user != NULL){
        strcpy(user,ps->current_user->Username);
    }else{
        strcpy(user,"System");
    }

    sprintf(timestamp, "%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    file = fopen("activity_log.csv", "a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s,%s,%s,%s\n", timestamp, user, action, details);
    fclose(file);
    
}

void sortByCat(char categories[]) {
    // เปิดไฟล์ allCategory.csv
    FILE *file = fopen("allCategory.csv", "r");
    if (file == NULL) {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }
    
    

}

// Function to remove newline character from fgets input
void remove_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void login(struct ProductSales *ps) {
    char username[100];
    char password[100];
    int attempts = 0;

    printf("Username: ");
    scanf("%s", username);
    remove_newline(username);

    struct User *USER = searchUserByUsername(ps->users, username);
    if (USER != NULL) {
        do {
            printf("Password: ");
            scanf("%s", password);
            remove_newline(password);
            
            struct User *UserD = searchUserByUsernameAndPassword(ps->users, username, password);
            if (UserD != NULL) {
                ps->current_user = UserD;
                // printf("%p" , ps->current_user);
                return;
            } else {
                attempts++;
                printf("Incorrect password. Attempts left: %d\n", 3 - attempts);
            }
        } while (attempts < 3);
        printf("Maximum login attempts exceeded. Please try again later.\n");
    } 
    else {
        printf("User not found\n");
    }
    return;
}

void register_user(struct ProductSales *ps , char *userLoginFile) {
    char username[100], password[100];
    while (1) {
        printf("Enter new username: ");
        printf("Username: ");
        scanf("%s", username);
        remove_newline(username);

        if (searchUserByUsername(ps->users, username) == NULL) {

            break;
        } else {
            printf("Username already exists. Please choose another username.\n");
            // continue;
        }
        
    }
    // printf("\n");

    printf("Enter password: ");
    printf("Password: ");
    scanf("%s", password);
    remove_newline(password);

    struct User *user = createNode_User(username, password, "user", ps->users->UserID);
    insertNodeUser(&(ps->users), user); // Insert the user node into the user list

    FILE *fp = fopen(userLoginFile, "a");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file. Please check the file path and try again.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "Username: %s\nPassword: %s\n", username, password);
    fclose(fp);
}


void main_menu(struct ProductSales *ps)
{
    int option;
    do{
    printf("Main Menu\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
    scanf("%d", &option);
    clear_terminal();
    switch (option)
    {
    case 1:
        run(ps);
        break;
    case 2:
        register_user(ps,"login.csv");
        break;
    case 3:
        break;
    default:
        printf("Invalid choice. Please try again.");
    }}while(option != 3);
}

void admin_menu(struct ProductSales *ps)
{
    int option;
    char outputFileName[100];
    do
    {
        printf("Admin Menu\n");
        printf("1. Add product\n");
        printf("2. Delete product\n");
        printf("3. Edit product\n");
        scanf("%d", &option);
        clear_terminal();
        switch (option)
        {
        case 1:
            snprintf(outputFileName, sizeof(outputFileName), "addProduct.csv");
            break;
        case 2:
            snprintf(outputFileName, sizeof(outputFileName), "deleteProduct.csv");
            break;
        case 3:
            snprintf(outputFileName, sizeof(outputFileName), "editProduct.csv");
            break;
        default:
            printf("Invalid choice. Please try again.");
        }
    } while (option != 3);

    // view_products(&ps, &outputFileName);
}

void manage_products(struct ProductSales *ps)
{
    int choice;

    while (1)
    {
        printf("\nManage Products:\n");
        printf("1. View Products\n");
        printf("2. Add Product\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Back to Admin Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            view_products(ps, "product.csv");
            break;
        case 2:
            add_product(ps);
            break;
        case 3:
            update_product(ps);
            break;
        case 4:
            delete_product(ps);
            break;
        case 5:
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void view_products(struct ProductSales *ps, char outputFileName[20])
{
    // View products logic here
    FILE *file = fopen(outputFileName, "r");
    if (file == NULL)
    {
        file = fopen(outputFileName, "w");
        printf("\n");
    }
    struct User users[MAX_USERS];
    struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
    int num = 0;
    while (fscanf(file, "%s %d", newNode->ID, &newNode->price) != EOF)
    {
        num++;
        printf("No. %d  ID : %s Price = %d\n",num, newNode->ID, newNode->price);
    }

    if (num == 0)
    {
        printf("No statement found in the file.\n");
    }

    fclose(file);
    // add_product(&ps, num);
}

void add_product(struct ProductSales *ps)
{

    struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
    const char *filename = "product.csv";
    char idToEdit[6]; 
    printf("Enter new ID: ");
    scanf("%5s", newNode->ID);
    getchar();
    printf("Enter new stock ID: ");
    scanf("%5s", newNode->stockID);
    getchar();
    printf("Enter new product name: ");
    fgets(newNode->productName, sizeof(newNode->productName), stdin);
    newNode->productName[strcspn(newNode->productName, "\n")] = '\0'; // Remove newline character

    printf("Enter new price: ");
    scanf("%d", &newNode->price);
    getchar();

    printf("Enter new imports: ");
    scanf("%6s", newNode->imports);
    getchar();
    printf("Enter new exports: ");
    scanf("%6s", newNode->exports);
    getchar();
    printf("Enter new category: ");
    fgets(newNode->category, sizeof(newNode->category), stdin);
    newNode->category[strcspn(newNode->category, "\n")] = '\0'; // Remove newline character

    printf("Enter new stock: ");
    scanf("%d", &newNode->stock);
    getchar();

    // สร้างข้อมูลแถวใหม่ในรูปแบบ CSV
    char newData[MAX_LINE_LENGTH];
    snprintf(newData, sizeof(newData), "%s,%s,%s,%d,%s,%s,%s,%d\n",
             newNode->ID, newNode->stockID, newNode->productName, newNode->price, newNode->imports, newNode->exports, newNode->category, newNode->stock);
    
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        perror("File opening error");
        exit(EXIT_FAILURE);
    }

    fputs(newData, file);

    fclose(file);
}
//update_product ดีเเล้ว------------------------------------------------------------------------------------------------------------------------------------------------

void update_product(struct ProductSales *ps)
{
    struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
    const char *filename = "product.csv";
    char idToEdit[7]; // เพิ่มขนาดเป็น 7 เพื่อให้สามารถเก็บ 6 อักขระ + null terminator


    printf("Enter ID to edit: ");
    scanf("%5s", idToEdit);
    getchar(); // Clear the newline character left by scanf

    // รับข้อมูลใหม่สำหรับแถว
    printf("Enter new ID: ");
    scanf("%5s", newNode->ID);
    getchar();
    printf("Enter new stock ID: ");
    scanf("%5s", newNode->stockID);
    getchar();
    printf("Enter new product name: ");
    fgets(newNode->productName, sizeof(newNode->productName), stdin);
    newNode->productName[strcspn(newNode->productName, "\n")] = '\0'; // Remove newline character

    printf("Enter new price: ");
    scanf("%d", &newNode->price);
    getchar();

    printf("Enter new imports: ");
    scanf("%6s", newNode->imports);
    getchar();
    printf("Enter new exports: ");
    scanf("%6s", newNode->exports);
    getchar();
    printf("Enter new category: ");
    fgets(newNode->category, sizeof(newNode->category), stdin);
    newNode->category[strcspn(newNode->category, "\n")] = '\0'; // Remove newline character

    printf("Enter new stock: ");
    scanf("%d", &newNode->stock);
    getchar();

    // สร้างข้อมูลแถวใหม่ในรูปแบบ CSV
    char newData[MAX_LINE_LENGTH];
    snprintf(newData, sizeof(newData), "%s,%s,%s,%d,%s,%s,%s,%d\n",
             newNode->ID, newNode->stockID, newNode->productName, newNode->price, newNode->imports, newNode->exports, newNode->category, newNode->stock);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("File opening error");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    char *rows[1000];
    int rowCount = 0;
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        char id[7];
        sscanf(line, "%6[^,]", id);
        if (strcmp(id, idToEdit) == 0)
        {
            // Replace the line with new data
            rows[rowCount] = strdup(newData);
            found = 1;
        }
        else
        {
            rows[rowCount] = strdup(line); // Copy the line to memory
        }
        rowCount++;
    }

    fclose(file);

    if (found)
    {
        file = fopen(filename, "w");
        if (file == NULL)
        {
            perror("File opening error");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < rowCount; i++)
        {
            fputs(rows[i], file);
            free(rows[i]); // Free the memory
        }

        fclose(file);
    }
    else
    {
        printf("ID %s not found in %s.\n", idToEdit, filename);
    }
    // write to file
}

void delete_product(struct ProductSales *ps)
{
    const char *filename = "product.csv";
    
    char idToDelete[6];
    printf("Enter ID to delete: ");
    scanf("%5s", idToDelete);

    FILE *file = fopen("data.csv", "r");
    while (file == NULL)
    {
        file = fopen("data.csv", "w");
        printf("Hello\n");
    }

    char line[MAX_LINE_LENGTH];
    char *rows[1000];
    int rowCount = 0;
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        char id[6];
        sscanf(line, "%5[^,]", id);
        if (strcmp(id, idToDelete) != 0)
        {
            rows[rowCount] = strdup(line);
            rowCount++;
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);

    if (found)
    {
        file = fopen(filename, "w");
        if (file == NULL)
        {
            perror("File opening error");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < rowCount; i++)
        {
            fputs(rows[i], file);
            free(rows[i]); // ปล่อยหน่วยความจำ
        }

        fclose(file);
    }
    else
    {
        printf("ID %s not found in %s.\n", idToDelete, filename);
    }
}

void view_orders(struct ProductSales *ps)
{
    // View orders logic here
    struct History *user_his = ps->user_history;
    struct History *tmp = user_his;
    int user[50];
    char id[50][6];
    int i =0;
    do{
        if(i == 0){
            user[i] = tmp->user_id;
        }
        else if(user[i] == user_his->user_id){

        }
    }while(1);
}

// void generate_report(struct ProductSales *ps)
// {
//     int product_purchase_count[ps->product_count];
//     memset(product_purchase_count, 0, sizeof(product_purchase_count));

//     for (int i = 0; i < ps->purchase_history_count; i++)
//     {
//         char *stock_id = ps->purchase_history[i].stock_id;
//         for (int j = 0; j < ps->product_count; j++)
//         {
//             if (strcmp(ps->products[j].stock_id, stock_id) == 0)
//             {
//                 product_purchase_count[j]++;
//                 break;
//             }
//         }
//     }

//     printf("\nPurchase Report:\n");
//     for (int i = 0; i < ps->product_count; i++)
//     {
//         printf("Product: %s, StockID: %s, Purchases: %d\n", ps->products[i].product_name, ps->products[i].stock_id, product_purchase_count[i]);
//     }
// }

void customer_menu(struct ProductSales *ps){
    
    int choice;

    while(1) {
        printf("\nCustomer Menu:\n");
        printf("1. View Recommended Products\n");
        printf("2. View All Products\n");
        printf("3. Add Product to Cart\n");
        printf("4. View Cart\n");
        printf("5. Checkout\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                view_recommended_products(ps);
                break;
            case 2:
                view_all_products(ps);
                break;
            case 3:
                add_to_cart(ps);
                break;
            case 4:
                view_cart(ps);
                break;
            case 5:
                checkout(ps);
                break;
            case 6:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// sorting For suggesion

void swap(struct Product **a, struct Product **b) {
    struct Product *tmp = *a;
    *a = *b;
    *b = tmp;
}

void sortingSuggestValue(struct Product *start) {
    if (start == NULL || (start)->next == NULL) {
        return;
    }

    int n = 0;
    struct Product *tmp = start;
    while (tmp != NULL) {
        n++;
        tmp = tmp->next;
    }

    struct Product *current = start;
    struct Product *next = NULL;

    for (int i = 0; i < n; i++) {
        current = start;
        while (current->next != NULL) {
            next = current->next;
            if ((current->buy)*4 + (current->addToCart)*2 + (current->access) > (next->buy)*4 + (next->addToCart)*2 + (next->access)) {
                swap(&current, &next);
            }
            current = current->next;
        }
    }
}


void printNode(struct Product **start)
{
    struct Product *ptr = *start;
    if (ptr == NULL)
    {
        return;
    }

    while (ptr != NULL)
    {
        printf("%s %d", ptr->productName , (ptr->buy)*4+(ptr->addToCart)*2+(ptr->access));
        ptr = ptr->next;
    }
}

void view_recommended_products(struct ProductSales *ps)
{
    struct Product *product = ps->products;
    sortingSuggestValue(product);
    int recommendations[ps->product_count];
    int recommendation_count = 0;
    int i= 0;

        // If the user has no history, recommend the first 5 products
        struct Product *tmp = product;
        for (int i = 0; i < recommendation_count; i++ && tmp != NULL)
        {
            printf("Stock ID: %s |", tmp->stockID);
            printf("Product Name: %s |", tmp->productName);
            printf("Price : %d |", tmp->price);
            tmp = tmp->next;
        }
}

void product_detail(struct ProductSales *ps , char *stockId){
    struct Product *product = ps->products;
    struct Product *tmp = product;
    int isRemain = 0;
    while (tmp != NULL)
    {
        if(strcmp(tmp->stockID,stockId)==0 && tmp->stock > 0){
            isRemain = 1;
        break;
        }
        tmp = tmp->next;
    }
    printf("Product ID : %s\n" , tmp->stockID);
    printf("Product Name : %s | Category : %s\n" , tmp->productName,tmp->category);
    printf("Status : ");
    (isRemain)? printf("\'Product Remaining\'") : printf("\'Out Of Stock\'");
    printf("\n");
    printf("Price : %d\n" , tmp->price);
}
// //ต้องทำ*********************************

void add_to_cart(struct ProductSales *ps)
{
    char stock_id[50];
    int quantity;
    printf("Enter Stock ID of the product to add to cart: ");
    scanf("%s", stock_id);
    //remove_newline(stock_id);
    struct Product *head = ps->products;
    while (head != NULL)
    {
       if(strcmp(stock_id,head->ID) == 0){
        break;
       }
       head = head->next;
    }
    if(head->stock <= 0){
        printf("Out of stock\n");
        return;
    }else if(head == NULL){
        printf("Product not found.\n");
        return;
    }else{
        printf("product name : %s\n",head->productName);
        printf("Enter quantity to add: ");
        scanf("%d", &quantity);
            FILE *file = fopen("csv/addToCart.csv", "a");
            fprintf(file, "%d,%d,%d\n", ps->current_user->UserID, atoi(head->ID) + atoi(head->stockID), quantity);
            fclose(file);
            head->addToCart++;
    }
    
    
}

void view_cart(struct ProductSales *ps)
{
    int user_id = ps->current_user->UserID;
    struct Product *head = ps->products;
    struct PurchaseHistory *node = (struct PurchaseHistory*)malloc(sizeof(struct PurchaseHistory));
    FILE *file = fopen("csv/addToCart.csv", "r");

    while(fscanf(file,"%d,%[^,],%d",&node->UserID,node->StockID,&node->Quantity) != EOF){
        if(node->UserID == user_id){
        printf("User Id : %d \n",user_id);
        struct Product *pdd = ps->products;
        while (pdd->next != NULL)
        {
           if(atoi(pdd->ID)+atoi(pdd->stockID) == atoi(node->StockID)){
            printf("Product name : %s \n", pdd->productName);
            break;
           }
           pdd = pdd->next;
        }
        printf("Quantity : %d \n", node->Quantity);
        printf("---------------------------------------------\n");
        }
    }
}
//ยังไม่ได้เทส อัพเดตล่าสุด 16/05/67 02:53
void checkout(struct ProductSales *ps)
{
    if (ps == NULL)
    {
        printf("ProductSales pointer is NULL.\n");
        return;
    }

    if (ps->cart_count == 0)
    {
        printf("Your cart is empty.\n");
        return;
    }

    printf("\nCheckout:\n");

    struct CartItem *currentCartItem = ps->cart;
    while (currentCartItem != NULL)
    {
        struct Product *currentProduct = ps->products;
        while (currentProduct != NULL && strcmp(currentProduct->stockID, currentCartItem->IDstock) != 0)
        {
            currentProduct = currentProduct->next;
        }

        if (currentProduct == NULL)
        {
            printf("Product with StockID %s not found.\n", currentCartItem->IDstock);
            currentCartItem = currentCartItem->next;
            continue;
        }

        // Update inventory and num_purchases
        currentProduct->stock -= currentCartItem->quantity;
        currentProduct->buy += currentCartItem->quantity;

        // Record purchase history
        struct PurchaseHistory *ph = malloc(sizeof(struct PurchaseHistory));
        if (ph == NULL)
        {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        ph->UserID = ps->current_user->UserID;
        strcpy(ph->StockID, currentProduct->stockID);
        ph->Quantity = currentCartItem->quantity;
        ph->next = ps->purchase_history;
        ps->purchase_history = ph;
        ps->purchase_history_count++;

        // Log activity
        char details[100];
        snprintf(details, sizeof(details), "Customer purchased %d of %s with StockID %s",
                 currentCartItem->quantity, currentProduct->productName, currentProduct->stockID);
        log_activity(ps, "Purchase", details);

        printf("Purchased %d of %s\n", currentCartItem->quantity, currentProduct->productName);

        struct CartItem *temp = currentCartItem;
        currentCartItem = currentCartItem->next;
        free(temp); // Free memory allocated for the current cart item
    }

    // Reset cart and save data
    ps->cart_count = 0;
    // save_data(ps);
    printf("Checkout complete!\n");
}

// }
// {
//     if (ps->cart_count == 0)
//         {
//             printf("Your cart is empty.\n");
//         }
//         else
//         {
//     //         printf("\nCheckout:\n");
//     //         for (int i = 0; i < ps->cart_count; i++)
//     //         {
//     //             struct CartItem *item = &ps->cart[i];
//     //             item->product.inventories -= item->quantity;
//     //             item->product.num_purchases += item->quantity;

//     //             struct PurchaseHistory ph;
//     //             ph.user_id = ps->current_user.user_id;
//     //             ph.stock_id = item->product.stock_id;
//     //             ph.quantity = item->quantity;
//     //             ps->purchase_history[ps->purchase_history_count++] = ph;

//     //             char details[100];
//     //             snprintf(details, sizeof(details), "Customer purchased %d of %s with StockID %s",
//     //                      item->quantity,
//     //                      item->product.product_name,
//     //                      item->product.stock_id);
//     //             log_activity(ps, "Purchase", details);

//     //             printf("Purchased %d of %s\n", item->quantity, item->product.product_name);
//     //         }
//     //         ps->cart_count = 0;
//     //         save_data(ps);
//     //         printf("Checkout complete!\n");
//     //     }
    
//     if (ps->cart_count == 0)
//     {
//         printf("Your cart is empty.\n");
//     }
//     else
//     {
//         printf("\nCheckout:\n");
//         for (int i = 0; i < ps->cart_count; i++)
//         {
//             ps->cart[i].product.inventories -= ps->cart[i].quantity;
//             ps->cart[i].product.num_purchases += ps->cart[i].quantity;

//             struct PurchaseHistory ph;
//             ph.user_id = ps->current_user.user_id;
//             ph.stock_id = ps->cart[i].product.stock_id;
//             ph.quantity = ps->cart[i].quantity;
//             ps->purchase_history[ps->purchase_history_count++] = ph;

//             char details[100];
//             sprintf(details, "Customer purchased %d of %s with StockID %s",
//                     ps->cart[i].quantity,
//                     ps->cart[i].product.product_name,
//                     ps->cart[i].product.stock_id);
//             log_activity(ps, "Purchase", details);

//             printf("Purchased %d of %s\n", ps->cart[i].quantity, ps->cart[i].product.product_name);
//         }
//         ps->cart_count = 0;
//         save_data(ps);
//         printf("Checkout complete!\n");
//     }
// }
//view_all_products ดีเเล้ว------------------------------------------------------------------------------------------------------------------------------------------------


void view_all_products(struct ProductSales *ps){
    struct Product *head = ps->products;
    while (head != NULL)
    {
        printf("StockID: %s, Name: %s, Quantity : %d, Type : %s",head->stockID,head->productName,head->stock,head->category);
        head = head->next;
    }
}
//run ดีเเล้ว------------------------------------------------------------------------------------------------------------------------------------------------

void run(struct ProductSales *ps)
{
    int i;
    load_data(ps);
    while (1){
        login(ps);
        //printf("%p" , ps->current_user);
        remove_newline(ps->current_user->Role);
        if (ps->current_user != NULL){
            // printf("|%s|" , ps->current_user->Role);
            if (strcmp(ps->current_user->Role, "admin") == 0){
                admin_menu(ps);
            }
            else if (strcmp(ps->current_user->Role, "user") == 0){
                customer_menu(ps);
            }
        }
        else{
            printf("Type 1 to try again, type -1 to exit. : ");
            scanf("%d",&i);
            if(i == -1){
                return;
            }
        }
    }
    
    
}


#define V 4
#define INF 99999 

void floydWarshall(int dist[][V]) {
    int i, j, k;
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distance matrix
    printf(
        "The following matrix shows the shortest distances"
        " between every pair of vertices \n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}



//------------------------------------------------------------------------MAIN------------------------------------------------------------------------
int main()
{
    struct ProductSales *app = malloc(sizeof(struct ProductSales));
    if (app == NULL) {
        printf("Failed to allocate memory for app\n");
        return 1;
    }
    load_data(app);
    printf("Welcome to CashierX\n");
    printf("By ShopWiz Co.,Ltd.\n");
    main_menu(app);
    
    // Don't forget to free the memory you allocated
    free(app);
    
    return 0;
}