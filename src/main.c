#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Structure.h"
#define FILENAME "csv/product.csv"

/**
 * @file main.c
 * @brief This file contains the definitions of various maximum limits used in the program.
 *
 * This file defines the maximum limits for products, users, history, cart items, and line length.
 * These limits are used throughout the program to ensure that arrays and buffers are not exceeded.
 */
#define MAX_PRODUCTS 100     /**< The maximum number of products */
#define MAX_USERS 100        /**< The maximum number of users */
#define MAX_HISTORY 100      /**< The maximum number of history entries */
#define MAX_CART_ITEMS 100   /**< The maximum number of items in a cart */
#define MAX_LINE_LENGTH 1024 /**< The maximum length of a line */
#define BUFFER_SIZE 255

// Function prototypes
void clear_terminal();
int *dealWithFloyd(int productChose);
void load_data(struct ProductSales *ps);
struct Product *createNode_StrProduct(char ID[], char stockID[], char productName[], int price, char imports[], char exports[], char category[], int stock, int access, int addToCart, int buy, int key);
struct User *createNode_User(char Username[], char Password[], char Role[], int UserID);
struct History *createNode_History(int id, int user_id, char date[7], char pro_id[6]);
struct PurchaseHistory *createNode_PurchaseHistory(int UserID, char StockID[], int Quantity);
struct CartItem *createNode_CartItem(int key, int quantity);
void insertNode(struct Product **head, struct Product *newNode);
struct User *searchUserByUsername(struct User *head, char Username[]);
struct User *searchUserByID(struct User *head, int UserID);
struct User *searchUserByUsernameAndPassword(struct User *head, char *username, char *password);
struct History *searchHistoryById(struct History *head, int id);
struct History *searchHistoryByuser_id(struct History *head, int user_id);
struct PurchaseHistory *searchPurchaseHistoryByUserID(struct PurchaseHistory *head, int UserID);
struct PurchaseHistory *searchPurchaseHistoryByStockID(struct PurchaseHistory *head, char StockID[]);
struct CartItem *searchCartItemByKey(struct CartItem *head, int key);
struct Product *searchProductByIDamdStockID(struct Product *head, char *ID, char *StockID);
struct Product *searchProductByID(struct Product *head, char *ID);
void log_activity(struct ProductSales *ps, char *action, char *details);
void remove_newline(char *str);
void login(struct ProductSales *ps);
void register_user_NEW(struct ProductSales *ps);
void register_user(struct ProductSales *ps);
void main_menu(struct ProductSales *ps);
void admin_menu(struct ProductSales *ps);
void manage_products(struct ProductSales *ps);
void view_products(struct ProductSales *ps);
void add_product(struct ProductSales *ps);
void update_product(struct ProductSales *ps);
void delete_product(struct ProductSales *ps);
void view_orders(struct ProductSales *ps);
void generate_report(struct ProductSales *ps);
void customer_menu(struct ProductSales *ps);
void swap(struct Product **a, struct Product **b);
void printNode(struct Product **start);
void view_recommended_products(struct ProductSales *ps);
void product_detail(struct ProductSales *ps);
void add_to_cart(struct ProductSales *ps, char ID[6], char StockID[6], int amount);
// void add_to_cart_to(struct ProductSales *ps);
void view_cart(struct ProductSales *ps);
void checkout(struct ProductSales *ps);
void view_all_products(struct ProductSales *ps);
void run(struct ProductSales *ps);
void search_by_cat(struct ProductSales *ps);
void buy(struct ProductSales *ps, char ID[6], char StockID[6], int amount);
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
    if (!fp1 || !fp2 || !fp3)
    {
        printf("\033[0;31mFailed to open one or more files.\033[0m\n");
        if (!fp1)
            printf("\033[0;31mFailed to open csv/product.csv\033[0m\n");
        if (!fp2)
            printf("\033[0;31mFailed to open csv/userHistory.csv\033[0m\n");
        if (!fp3)
            printf("\033[0;31mFailed to open csv/login.csv\033[0m\n");
        if (fp1)
            fclose(fp1);
        if (fp2)
            fclose(fp2);
        if (fp3)
            fclose(fp3);
        return;
    }

    char buffer[BUFFER_SIZE];
    struct Product *head = NULL;
    struct Product *tail = NULL;

    while (fgets(buffer, BUFFER_SIZE, fp1))
    {
        struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
        if (!newNode)
        {
            printf("\033[0;31mMemory allocation failed.\033[0m\n");
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
        if (!newNode)
        {
            printf("\033[0;31mMemory allocation failed.\033[0m\n");
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

    while (fgets(buffer, BUFFER_SIZE, fp3))
    {
        struct User *newNode = (struct User *)malloc(sizeof(struct User));
        if (!newNode)
        {
            printf("\033[0;31mMemory allocation failed.\033[0m\n");
            return;
        }
        sscanf(buffer, "%d,%100[^,],%100[^,],%20[^,]", &newNode->UserID, newNode->Username, newNode->Password, newNode->Role);
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
        printf("\033[0;31mMemory allocation failed.\033[0m\n");
        exit(EXIT_FAILURE);
    }
    strncpy(newNode->ID, ID, sizeof(newNode->ID) - 1);
    newNode->ID[sizeof(newNode->ID) - 1] = '\0';

    strncpy(newNode->stockID, stockID, sizeof(newNode->stockID) - 1);
    newNode->stockID[sizeof(newNode->stockID) - 1] = '\0';

    strncpy(newNode->productName, productName, sizeof(newNode->productName) - 1);
    newNode->productName[sizeof(newNode->productName) - 1] = '\0';

    newNode->price = price;

    strncpy(newNode->imports, imports, sizeof(newNode->imports) - 1);
    newNode->imports[sizeof(newNode->imports) - 1] = '\0';

    strncpy(newNode->exports, exports, sizeof(newNode->exports) - 1);
    newNode->exports[sizeof(newNode->exports) - 1] = '\0';

    strncpy(newNode->category, category, sizeof(newNode->category) - 1);
    newNode->category[sizeof(newNode->category) - 1] = '\0';

    newNode->stock = stock;
    newNode->access = access;
    newNode->addToCart = addToCart;
    newNode->buy = buy;
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

/*-------------------------------------------------------------------------------------------*/
struct User *createNode_User(char Username[], char Password[], char Role[], int UserID)
{
    struct User *newNode = (struct User *)malloc(sizeof(struct User));
    if (newNode == NULL)
    {
        fprintf(stderr, "\033[0;31mMemory allocation failed.\033[0m\n");
        exit(EXIT_FAILURE);
    }
    strncpy(newNode->Username, Username, sizeof(newNode->Username) - 1);
    newNode->Username[sizeof(newNode->Username) - 1] = '\0';

    strncpy(newNode->Password, Password, sizeof(newNode->Password) - 1);
    newNode->Password[sizeof(newNode->Password) - 1] = '\0';

    strncpy(newNode->Role, Role, sizeof(newNode->Role) - 1);
    newNode->Role[sizeof(newNode->Role) - 1] = '\0';

    newNode->UserID = UserID;
    newNode->next = NULL;
    return newNode;
}
/*------------------------------------------------------------------------------------------*/
struct History *createNode_History(int id, int user_id, char date[7], char pro_id[6])
{
    struct History *newNode = (struct History *)malloc(sizeof(struct History));
    if (newNode == NULL)
    {
        fprintf(stderr, "\033[0;31mMemory allocation failed.\033[0m\n");
        exit(EXIT_FAILURE);
    }

    newNode->id = id;
    newNode->user_id = user_id;

    strncpy(newNode->date, date, sizeof(newNode->date) - 1);
    newNode->date[sizeof(newNode->date) - 1] = '\0';

    strncpy(newNode->pro_id, pro_id, sizeof(newNode->pro_id) - 1);
    newNode->pro_id[sizeof(newNode->pro_id) - 1] = '\0';

    return newNode;
}

/*------------------------------------------------------------------------------------------*/
struct PurchaseHistory *createNode_PurchaseHistory(int UserID, char StockID[], int Quantity)
{
    struct PurchaseHistory *newNode = (struct PurchaseHistory *)malloc(sizeof(struct PurchaseHistory));
    if (newNode == NULL)
    {
        fprintf(stderr, "\033[0;31mMemory allocation failed.\033[0m\n");
        exit(EXIT_FAILURE);
    }
    newNode->UserID = UserID;
    strncpy(newNode->StockID, StockID, sizeof(newNode->StockID) - 1);
    newNode->StockID[sizeof(newNode->StockID) - 1] = '\0';

    newNode->Quantity = Quantity;
    newNode->next = NULL;

    return newNode;
}
/*------------------------------------------------------------------------------------------*/
struct CartItem *createNode_CartItem(int key, int quantity)
{
    struct CartItem *newNode = (struct CartItem *)malloc(sizeof(struct CartItem));
    if (newNode == NULL)
    {
        printf("\033[0;31mMemory allocation failed.\033[0m\n");
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
    if (newNode == NULL)
    {
        printf("\033[0;31mCannot insert NULL node!\033[0m\n");
        return;
    }
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

void insertNodeUser(struct User **head, struct User *newNode)
{
    if (newNode == NULL)
    {
        printf("\033[0;31mCannot insert NULL node!\033[0m\n");
        return;
    }

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

// ฟังก์ชันสำหรับsearch

// ฟังก์ชันสำหรับค้นหาผู้ใช้จาก Username และ IDUsername password
struct User *searchUserByUsername(struct User *head, char Username[])
{
    if (head == NULL)
    {
        printf("\033[0;31mList is empty!\033[0m\n");
        return NULL;
    }
    struct User *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->Username, Username) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// struct User *searchUserByID(struct User *head, int UserID)
// {
//     if (head == NULL){
//         printf("List is empty!\n");
//         return NULL;
//     }
//     struct User *current = head;
//     while (current != NULL){
//         if (strcmp(current->Username, username) == 0 && strcmp(current->Password, password) == 0){
//             return current;
//         }
//         current = current->next;
//     }
//     return NULL;
// }

struct User *searchUserByUsernameAndPassword(struct User *head, char *username, char *password)
{
    struct User *current = head;

    while (current != NULL)
    {
        if (strcmp(current->Username, username) == 0 && strcmp(current->Password, password) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
/*----------------------------------------------------------*/

// ฟังก์ชันสำหรับค้นหาประวัติการใช้งานโดยใช้ id user_id
struct History *searchHistoryById(struct History *head, int id)
{
    if (head == NULL)
    {
        printf("\033[0;31mList is empty!\033[0m\n");
        return NULL;
    }
    struct History *temp = head;
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct History *searchHistoryByuser_id(struct History *head, int user_id)
{
    if (head == NULL)
    {
        printf("\033[0;31mList is empty!\033[0m\n");

        return NULL;
    }
    struct History *temp = head;
    while (temp != NULL)
    {
        if (temp->user_id == user_id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
/*--------------------------------------------------------------------*/

// ฟังก์ชันสำหรับค้นหาประวัติการซื้อสินค้าโดยใช้ UserID ,StockID[20]

struct PurchaseHistory *searchPurchaseHistoryByUserID(struct PurchaseHistory *head, int UserID)
{
    if (head == NULL)
    {
        printf("\033[0;31mList is empty!\033[0m\n");
        return NULL;
    }
    struct PurchaseHistory *temp = head;
    while (temp != NULL)
    {
        if (temp->UserID == UserID)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct PurchaseHistory *searchPurchaseHistoryByStockID(struct PurchaseHistory *head, char StockID[])
{
    struct PurchaseHistory *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->StockID, StockID) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
/*------------------------------------------------------------------------------------*/

struct CartItem *searchCartItemByKey(struct CartItem *head, int key)
{
    struct CartItem *temp = head;
    while (temp != NULL)
    {
        if (temp->key == key)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Function to search product by ID and StockID
struct Product *searchProductByIDamdStockID(struct Product *head, char *ID, char *StockID)
{
    while (head != NULL)
    {
        // printf("| %s-%s   %s-%s |" , head->ID , ID , head->stockID , StockID);
        if (strcmp(head->ID, ID) == 0 && strcmp(head->stockID, StockID) == 0)
        {
            return head; // Found the product
        }
        head = head->next;
    }
    return NULL; // Product not found
}

struct Product *searchProductByID(struct Product *head, char *ID)
{
    while (head != NULL)
    {
        if (strcmp(head->ID, ID) == 0)
        {
            return head; // Found the product
        }
        head = head->next;
    }
    return NULL; // Product not found
}

// log_activity ดีเเล้ว------------------------------------------------------------------------------------------------------------------------------------------------

void log_activity(struct ProductSales *ps, char *action, char *details)
{
    FILE *file;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char timestamp[20];
    char user[100];
    if (ps->current_user != NULL)
    {
        strcpy(user, ps->current_user->Username);
    }
    else
    {
        strcpy(user, "System");
    }

    sprintf(timestamp, "%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    file = fopen("activity_log.csv", "a");
    if (file == NULL)
    {
        printf("\033[0;31mError opening file!\033[0m\n");
        return;
    }
    fprintf(file, "%s,%s,%s,%s\n", timestamp, user, action, details);
    fclose(file);
}

void sortByCat(char categories[])
{
    FILE *file = fopen("allCategory.csv", "r");
    if (file == NULL)
    {
        printf("\033[0;31mUnable to open the file.\033[0m\n");
        return;
    }
    fclose(file);
}

// Function to remove newline character from fgets input
void remove_newline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

void login(struct ProductSales *ps)
{
    char username[100];
    char password[100];
    int attempts = 0;

    printf("\033[1;34mLogin\033[0m\n");
    printf("\033[1mUsername : \033[0m");
    scanf("%s", username);
    remove_newline(username);

    struct User *USER = searchUserByUsername(ps->users, username);
    if (USER != NULL)
    {
        do
        {
            printf("\033[1mPassword : \033[0m");
            scanf("%s", password);
            remove_newline(password);

            struct User *UserD = searchUserByUsernameAndPassword(ps->users, username, password);
            if (UserD != NULL)
            {
                ps->current_user = UserD;
                // printf("%p" , ps->current_user);
                return;
            }
            else
            {
                attempts++;
                printf("\033[0;33mIncorrect password. Attempts left : %d\n\033[0m", 3 - attempts);
            }
        } while (attempts < 3);
        printf("\033[0;31mMaximum login attempts exceeded. Please try again later.\n\033[0m");
    }
    else
    {
        printf("\033[0;31mUser not found\033[0m\n");
    }
    return;
}

void register_user_NEW(struct ProductSales *ps)
{
    char username[100], password[100];
    int maxUserID = 0;
    int userID;
    FILE *fp = fopen("csv/login.csv", "r");
    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%99[^,],%99[^,],%9s", &userID, username, password, (char[10]){}) != EOF)
        {
            if (userID > maxUserID)
            {
                maxUserID = userID;
            }
        }
        fclose(fp);
    }
    printf("\033[1;34mRegister\033[0m\n");
    printf("\033[1mEnter new username : \033[0m");
    scanf("%99s", username);
    remove_newline(username);

    printf("\033[1mEnter password : \033[0m");
    scanf("%99s", password);
    remove_newline(password);
    userID = maxUserID + 1;

    struct User *user = createNode_User(username, password, "user", userID);
    insertNodeUser(&(ps->users), user); // Insert the user node into the user list

    // Open file in append mode to add the new user
    fp = fopen("csv/login.csv", "a");
    if (fp != NULL)
    {
        fprintf(fp, "%d,%s,%s,%s\n", userID, username, password, "user");
        fclose(fp);
        printf("\033[0;32mRegistration successful.\033[0m\n");
    }
    else
    {
        printf("\033[0;31mRegistration failed\033[0m\n");
    }
}

void main_menu(struct ProductSales *ps)
{
    int option;
    do
    {
        printf("\n");
        printf("\t   Welcome to \033[38;2;255;105;180mCashierX\033[0m\n");
        printf("\t   By \033[38;2;255;105;180mShopWiz\033[0m \033[0;34mCo.,Ltd.\033[0m\n");
        printf("\t  ===================\n");
        printf("\t    | Main Menu    |\n");
        printf("\t    | 1. Login     |\n");
        printf("\t    | 2. Register  |\n");
        printf("\t    | 3. Exit      |\n");
        printf("\t    ----------------\n\n");
        printf("\033[1mEnter your option :\033[0m ");
        scanf("%d", &option);
        clear_terminal();
        switch (option)
        {
        case 1:
            run(ps);
            break;
        case 2:
            register_user_NEW(ps);
            break;
        case 3:
            printf("\033[1;34mThank you for your attention. 😊\033[0m\n");
            exit(0);
        default:
            printf("\033[1;31m\nInvalid choice. Please try again.\033[0m");
        }
    } while (option != 3);
}

void admin_menu(struct ProductSales *ps)
{
    int option;
    char outputFileName[100];
    while (1)
    {
        printf("\n\033[1;34mAdmin Menu\033[0m\n");
        printf(" 1. Manage Product\n");
        printf(" 2. View User Order\n");
        printf("-1. Back to login\n");
        printf("-----------------\n");
        printf("\033[1mEnter your choice :\033[0m ");
        scanf("%d", &option);
        clear_terminal();
        switch (option)
        {
        case 1:
            manage_products(ps);
            break;
        case 2:
            view_orders(ps);
            break;
        case -1:
            return;
        default:
            printf("\n\n\033[1;31mInvalid choice. Please try again.\033[0m");
        }
    }
    
    // do
    // {
    //     printf("\nAdmin Menu\n");
    //     printf(" 1. Manage Product\n");
    //     printf(" 2. View User Order\n");
    //     printf("-1. Exit\n");
    //     printf("-----------------\n");
    //     printf("Enter your choice : ");
    //     scanf("%d", &option);
    //     clear_terminal();
    //     switch (option)
    //     {
    //     case 1:
    //         manage_products(ps);
    //         break;
    //     case 2:
    //         view_orders(ps);
    //         break;
    //     default:
    //         printf("Invalid choice. Please try again.\n");
    //     }
    // } while (option != -1);

    // view_products(&ps, &outputFileName);
}

void manage_products(struct ProductSales *ps)
{
    int choice;

    while (1)
    {
        printf("\n\033[1;34mManage Products\033[0m\n");
        printf("1. View Products\n");
        printf("2. Add Product\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Back to Admin Menu\n");
        printf("---------------------\n");
        printf("\033[1mEnter your choice :\033[0m ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            clear_terminal();
            view_products(ps);
            break;
        case 2:
            clear_terminal();
            add_product(ps);
            break;
        case 3:
            clear_terminal();
            update_product(ps);
            break;
        case 4:
            clear_terminal();
            delete_product(ps);
            break;
        case 5:
            clear_terminal();
            return;
        default:
            clear_terminal();
            printf("\033[1;31m\nInvalid choice. Please try again.\033[0m");
        }
    }
}

void view_products(struct ProductSales *ps)
{
    // View products logic here
    char outputFileName[] = "csv/product.csv";
    FILE *file = fopen(outputFileName, "r");
    if (file == NULL)
    {
        file = fopen(outputFileName, "w");
        printf("\n");
    }
    struct User users[MAX_USERS];
    struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
    int num = 0;
    char buffer[255];
    printf("\033[1m                                     All products\033[0m\n");
    printf("-------------------------------------------------------------------------------------------\n");
    while (fgets(buffer, 255, file))
    {
        sscanf(buffer, "%6[^,],%6[^,],%100[^,],%d,%7[^,],%7[^,],%50[^,],%d,%d,%d,%d,%d",
               newNode->ID, newNode->stockID, newNode->productName, &newNode->price, newNode->imports,
               newNode->exports, newNode->category, &newNode->stock, &newNode->access,
               &newNode->addToCart, &newNode->buy, &newNode->key);
        num++;
        printf("\033[1mNo . %d \033[0m|", num);
        printf("\033[1mID :\033[0m %s | ", newNode->ID);
        printf("\033[1mStock ID :\033[0m %s | ", newNode->stockID);
        printf("\033[1mProduct Name :\033[0m %-20s | ", newNode->productName);
        printf("\033[1mPrice :\033[0m %d\n", newNode->price);
    }

    if (num == 0)
    {
        printf("\033[0;33mNo statement found in the file.\033[0m\n");
    }
    printf("-------------------------------------------------------------------------------------------\n");
    fclose(file);
    // add_product(&ps, num);
}

void add_product(struct ProductSales *ps)
{

    struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
    char filename[] = "csv/product.csv";
    char idToEdit[6];
    printf("\033[1;34mAdd Product\033[0m\n");
    printf("\033[1mEnter new ID : \033[0m");
    scanf("%5s", newNode->ID);
    getchar();
    printf("\033[1mEnter new stock ID : \033[0m");
    scanf("%5s", newNode->stockID);
    getchar();
    printf("\033[1mEnter new product name : \033[0m");
    fgets(newNode->productName, sizeof(newNode->productName), stdin);
    newNode->productName[strcspn(newNode->productName, "\n")] = '\0'; // Remove newline character

    printf("\033[1mEnter new price : \033[0m");
    scanf("%d", &newNode->price);
    getchar();

    printf("\033[1mEnter new imports[DDMMYY] : \033[0m");
    scanf("%6s", newNode->imports);
    getchar();
    printf("\033[1mEnter new exports[DDMMYY] : \033[0m");
    scanf("%6s", newNode->exports);
    getchar();
    printf("\033[1mEnter new category : \033[0m");
    fgets(newNode->category, sizeof(newNode->category), stdin);
    newNode->category[strcspn(newNode->category, "\n")] = '\0'; // Remove newline character

    printf("\033[1mEnter new stock : \033[0m");
    scanf("%d", &newNode->stock);
    getchar();

    // สร้างข้อมูลแถวใหม่ในรูปแบบ CSV
    char newData[MAX_LINE_LENGTH];
    snprintf(newData, sizeof(newData), "%s,%s,%s,%d,%s,%s,%s,%d,0,0,0,0\n",
             newNode->ID, newNode->stockID, newNode->productName, newNode->price, newNode->imports, newNode->exports, newNode->category, newNode->stock);

    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        perror("\033[0;31mFile opening error\033[0m");
        exit(EXIT_FAILURE);
    }

    fputs(newData, file);
    struct Product *head = ps->products;
    while (head->next != NULL)
    {
        head = head->next;
    }
    head->next = newNode;
    newNode->next = NULL;

    fclose(file);
}
// update_product ดีเเล้ว------------------------------------------------------------------------------------------------------------------------------------------------

void update_product(struct ProductSales *ps)
{
    struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
    char filename[] = "csv/product.csv";
    char idToEdit[7]; // เพิ่มขนาดเป็น 7 เพื่อให้สามารถเก็บ 6 อักขระ + null terminator
    printf("\033[1;34mEdit Product\033[0m\n");
    printf("\033[1mEnter ID to edit : \033[0m");
    scanf("%5s", idToEdit);
    getchar(); // Clear the newline character left by scanf

    // รับข้อมูลใหม่สำหรับแถว
    printf("\033[1mEnter new ID : \033[0m");
    scanf("%5s", newNode->ID);
    getchar();
    printf("\033[1mEnter new stock ID : \033[0m");
    scanf("%5s", newNode->stockID);
    getchar();
    printf("\033[1mEnter new product name : \033[0m");
    fgets(newNode->productName, sizeof(newNode->productName), stdin);
    newNode->productName[strcspn(newNode->productName, "\n")] = '\0'; // Remove newline character

    printf("\033[1mEnter new price : \033[0m");
    scanf("%d", &newNode->price);
    getchar();

    printf("\033[1mEnter new imports : \033[0m");
    scanf("%6s", newNode->imports);
    getchar();
    printf("\033[1mEnter new exports : \033[0m");
    scanf("%6s", newNode->exports);
    getchar();
    printf("\033[1mEnter new category : \033[0m");
    fgets(newNode->category, sizeof(newNode->category), stdin);
    newNode->category[strcspn(newNode->category, "\n")] = '\0'; // Remove newline character

    printf("\033[1mEnter new stock : \033[0m");
    scanf("%d", &newNode->stock);
    getchar();

    // สร้างข้อมูลแถวใหม่ในรูปแบบ CSV
    char newData[MAX_LINE_LENGTH];
    snprintf(newData, sizeof(newData), "%s,%s,%s,%d,%s,%s,%s,%d, %d, %d, %d, %d, %d\n",
             newNode->ID, newNode->stockID, newNode->productName, newNode->price, newNode->imports, newNode->exports, newNode->category, newNode->stock, newNode->access, newNode->addToCart, newNode->buy, newNode->buy, newNode->key);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("\033[0;31mFile opening error\033[0m");
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
            perror("\033[0;31mFile opening error\033[0m");
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
        printf("\033[0;31mID %s not found in %s.\033[0m\n", idToEdit, filename);
    }
    // write to file
}

void delete_product(struct ProductSales *ps)
{
    char IDdelete[6];
    char stockToDelete[6];
    printf("\033[1;34mDelete Product\033[0m\n");
    printf("\033[1mEnter ID to delete : ");
    if (scanf("%5s", IDdelete) != 1)
    {
        printf("\033[0;33mInvalid input.\033[0m\n");
        return;
    }
    printf("\033[1mEnter Stock ID to delete : \033[0m");
    if (scanf("%5s", stockToDelete) != 1)
    {
        printf("\033[0;33mInvalid input.\033[0m\n");
        return;
    }

    FILE *file = fopen("csv/product.csv", "r");
    if (file == NULL)
    {
        perror("\033[0;31mFile opening error\033[0m");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    char *rows[1000];
    int rowCount = 0;
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        char id[6];
        char stock[6];
        sscanf(line, "%5[^,],%5[^,]", id, stock);
        if (strcmp(id, IDdelete) != 0 || strcmp(stock, stockToDelete) != 0)
        {
            rows[rowCount] = strdup(line);
            if (rows[rowCount] == NULL)
            {
                printf("\033[0;31mMemory allocation error.\033[0m\n");
                exit(EXIT_FAILURE);
            }
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
        file = fopen("csv/product.csv", "w");
        if (file == NULL)
        {
            perror("\033[0;31mFile opening error\033[0m");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < rowCount; i++)
        {
            fputs(rows[i], file);
            free(rows[i]);
        }

        fclose(file);
        printf("\033[0;32mProduct with ID %s and Stock ID %s has been deleted.\033[0m\n", IDdelete, stockToDelete);
    }
    else
    {
        printf("\033[0;31mProduct with ID %s and Stock ID %s not found in %s.\033[0m\n", IDdelete, stockToDelete, "csv/product.csv");
    }
}

void view_orders(struct ProductSales *ps)
{
    int i = 1;
    struct History *node = ps->user_history;

    // Print table header
    printf("\033[1m                User Order\033[0m\n");
    printf("--------------------------------------------\n");
    printf("  No | User ID | Date(DDMMYY)| Products ID\n");
    printf("--------------------------------------------\n");

    while (node != NULL)
    {
        printf("%4d | %7d | %11s |       %s", i++, node->user_id, node->date, node->pro_id);
        printf("\n");
        node = node->next;
    }
    printf("--------------------------------------------\n");
}

void customer_menu(struct ProductSales *ps)
{
    clear_terminal();
    int choice;

    while (1)
    {
        printf("\033[1;34m\nCustomer Menu\033[0m\n");
        printf("1. View Recommended Products\n");
        printf("2. View All Products\n");
        printf("3. View Cart\n");
        printf("4. Search by Category\n");
        printf("5. Back to Main Menu\n");
        printf("-----------------------------\n");
        printf("\033[1mEnter your choice:\033[0m ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            clear_terminal();
            view_recommended_products(ps);
            break;
        case 2:
            clear_terminal();
            view_all_products(ps);
            break;
        case 3:
            clear_terminal();
            view_cart(ps);
            break;
        case 4:
            clear_terminal();
            search_by_cat(ps);
        // case 5:
        //     checkout(ps);
            break;
        case 5:
            clear_terminal();
            main_menu(ps); // รอเเก้
            break;
        default:
            clear_terminal();
            printf("\033[0;33m\nInvalid choice. Please try again.\033[0m");
        }
    }
}
void search_by_cat(struct ProductSales *ps)
{

    printf("\033[1;34mChoose category\033[0m\n");
    FILE *fp = fopen("csv/allCategory.csv", "r");
    int id[100], i = 1;
    char cat[100][20];
    while (fscanf(fp, "%d,%s", &id[i], cat[i]) != EOF)
    {
        remove_newline(cat[i]);
        printf("%d. %s\n", id[i], cat[i]);
        i++;
    }
    fclose(fp);
    printf("----------------\n");
    printf("\033[1mEnter category : \033[0m");
    int userCate;
    scanf("%d", &userCate);
    clear_terminal();
    i = 1;
    struct Product *tmp = ps->products;
    printf("\033[1m                                Category :\033[0m %s\n", cat[userCate]);
    printf("-----------------------------------------------------------------------------------\n");
    while (tmp->next != NULL)
    {
        if (strcmp(tmp->category, cat[userCate]) == 0)
        {
            printf("\033[1mID :\033[0m %s | ", tmp->ID);
            printf("\033[1mStock ID :\033[0m %s | ", tmp->stockID);
            printf("\033[1mProduct Name :\033[0m %-20s | ", tmp->productName);
            printf("\033[1mPrice :\033[0m %d\n", tmp->price);
        }
        tmp = tmp->next;
    }

    //------- floyd Suggestion ---------
    int *suggestArr = dealWithFloyd(userCate - 1);
    // printf("%d %d %d" , suggestArr[0] , suggestArr[1] , suggestArr[2]);
    int z = 0;
    tmp = ps->products;
    printf("-----------------------------------------------------------------------------------\n");
    printf("\033[1m                            Similar Category :\033[0m \'%s\'\n", cat[suggestArr[0]]);
    printf("-----------------------------------------------------------------------------------\n");

    while (tmp->next != NULL)
    {
        if (strcmp(tmp->category, cat[suggestArr[0]]) == 0 && z <= 3)
        {
            printf("\033[1mID :\033[0m %s | ", tmp->ID);
            printf("\033[1mStock ID :\033[0m %s | ", tmp->stockID);
            printf("\033[1mProduct Name :\033[0m %-20s | ", tmp->productName);
            printf("\033[1mPrice :\033[0m %d\n", tmp->price);
            z++;
        }
        tmp = tmp->next;
    }
    printf("-----------------------------------------------------------------------------------\n");
    product_detail(ps);
}
// sorting For suggesion

void swap(struct Product **a, struct Product **b)
{
    struct Product *tmp = *a;
    *a = *b;
    *b = tmp;
}

void sortingSuggestValue(struct Product **start)
{
    if (*start == NULL || (*start)->next == NULL)
    {
        return;
    }
    // printf("now ssv\n");

    // Get the length of the linked list
    int n = 0;
    struct Product *tmp = *start;
    while (tmp != NULL)
    {
        n++;
        tmp = tmp->next;
    }

    // Bubble sort the linked list based on the calculated value
    for (int i = 0; i < n - 1; i++)
    {
        struct Product **current = start;
        for (int j = 0; j < n - i - 1; j++)
        {
            struct Product *next = (*current)->next;
            int currentValue = (*current)->buy * 4 + (*current)->addToCart * 2 + (*current)->access;
            int nextValue = next->buy * 4 + next->addToCart * 2 + next->access;

            if (currentValue < nextValue)
            {
                struct Product *temp = *current;
                *current = next;
                temp->next = next->next;
                (*current)->next = temp;
            }
            current = &(*current)->next;
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
        printf("%s %d", ptr->productName, (ptr->buy) * 4 + (ptr->addToCart) * 2 + (ptr->access));
        ptr = ptr->next;
    }
}

void view_recommended_products(struct ProductSales *ps)
{
    // Uncomment the line below if you want to clear the terminal.
    // clear_terminal();

    struct Product *product = ps->products;
    // printf("Now vrp\n");
    sortingSuggestValue(&product);

    // Assuming we want to recommend the first 5 products after sorting
    int recommendation_count = 5;
    struct Product *tmp = product;
    clear_terminal();
    printf("\033[1m                     Products recommend\033[0m\n");
    printf("------------------------------------------------------------------------------------\n");
    for (int i = 0; i < recommendation_count && tmp != NULL; i++)
    {
        printf("\033[1mProduct ID :\033[0m %s | ", tmp->ID);
        printf("\033[1mStock ID :\033[0m %s | ", tmp->stockID);
        printf("\033[1mProduct Name :\033[0m %-20s | ", tmp->productName);
        printf("\033[1mPrice :\033[0m %d\n", tmp->price);
        tmp = tmp->next;
    }
    printf("------------------------------------------------------------------------------------\n");
    product_detail(ps);
}

void product_detail(struct ProductSales *ps)
{
    struct Product *head = ps->products;

    char productId[6], stockId[6];
    printf("\n\n\033[1;34mView detail\033[0m \033[0;33m(Go Back -1)\033[0m\n");
    printf("\033[1mProduct ID :\033[0m ");
    scanf("%s", productId);
    // printf("|%s|" , productId);
    remove_newline(productId);
    if (strcmp(productId, "-1") == 0)
    {
        clear_terminal();
        return;
    }
    // struct Product *product = searchProductByIDamdStockID(ps->products, productId, "");
    // if (product == NULL)
    // {
    //     printf("ProductID not found.\n");
    //     return;
    // }
    printf("\033[1mStockID :\033[0m ");
    scanf("%s", stockId);
    // printf("|%s|" , stockId);
    remove_newline(stockId);
    if (strcmp(stockId, "-1") == 0)
    {
        return;
    }
    struct Product *product = searchProductByIDamdStockID(ps->products, productId, stockId);
    if (product == NULL)
    {
        printf("\n\033[0;31mStockID not found.\033[0m");
        return;
    }
    clear_terminal();

    struct Product *tmp = product;
    int isRemain = 0;
    int option;
    int amount = 1;

    tmp->access = tmp->access + 1;
    FILE *fp = fopen("csv/product.csv", "w");
    while (head != NULL)
    {
        fprintf(fp, "%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d\n", head->ID, head->stockID, head->productName, head->price, head->imports,
                head->exports, head->category, head->stock, head->access,
                head->addToCart, head->buy, head->key);
        head = head->next;
    }
    fclose(fp);

    int key1 = atoi(tmp->ID) + atoi(tmp->stockID);
    int key = atoi(productId) + atoi(stockId);
    while (tmp != NULL)
    {
        if ((key1 == key) && tmp->stock > 0)
        {
            // printf("%d\n", tmp->stock);
            isRemain = 1;
            break;
        }
        tmp = tmp->next;
    }

    printf("\033[1mProduct ID :\033[0m %s\n", product->ID);
    printf("\033[1mProduct Name :\033[0m %s\n\033[1mCategory :\033[0m %s\n", product->productName, product->category);
    printf("\033[1mStatus : \033[0m ");

    if (isRemain == 1)
    {
        printf("\'\033[1mProduct Remaining\033[0m %d\'", product->stock);
    }
    else if (isRemain == 0)
    {
        printf("\'Out Of Stock\'");
    }
    printf("\n");
    printf("\033[1mPrice :\033[0m %d\n", product->price);
    printf("-----------------------------------");
    printf("\n\033[1;34mMenu\033[0m\n");
    printf("1.Add to cart\n");
    printf("2.Buy\n");
    printf("\033[1mEnter your choice (type -1 to back):\033[0m ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        do
        {
            if (amount <= 0)
            {
                printf("\033[0;33mPlease enter positive amount number.\033[0m\n");
            }
            printf("\033[1mRequired quantity :\033[0m ");
            scanf("%d", &amount);
        } while (amount <= 0);
        add_to_cart(ps, productId, stockId, amount);
        break;
    case 2:
        printf("\033[1mRequired quantity :\033[0m ");
        scanf("%d", &amount);
        buy(ps, productId, stockId, amount);
        break;
    case -1:
        return;
        break;
    default:
        printf("\033[1;31m\nInvalid choice. Please try again.\033[0m");
        break;
    }
}
// //ต้องทำ*********************************

void add_to_cart(struct ProductSales *ps, char ID[6], char StockID[6], int amount)
{
    // printf("Hi");
    struct Product *head = ps->products;
    struct Product *p;
    p = searchProductByIDamdStockID(head, ID, StockID);
    if (p->stock < amount)
    {
        printf("\033[0;31mOut of stock\033[0m\n");
    }
    else
    {
        printf("\033[0;32m\n%s is added\033[0m\n", p->productName);
        FILE *file = fopen("csv/addToCart.csv", "a");
        fprintf(file, "%d,%d,%d\n", ps->current_user->UserID, atoi(p->ID) + atoi(p->stockID), amount);
        fclose(file);
        p->addToCart = p->addToCart + amount;
        // printf("--%d--", p->stock);
        FILE *fp = fopen("csv/product.csv", "w");
        while (head != NULL)
        {
            fprintf(fp, "%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d\n", head->ID, head->stockID, head->productName, head->price, head->imports,
                    head->exports, head->category, head->stock, head->access,
                    head->addToCart, head->buy, head->key);
            head = head->next;
        }
        fclose(fp);
    }
}

void view_cart(struct ProductSales *ps)
{
    int user_id = ps->current_user->UserID , i = 0;
    struct Product *head = ps->products;
    struct PurchaseHistory *node = (struct PurchaseHistory *)malloc(sizeof(struct PurchaseHistory));
    FILE *file = fopen("csv/addToCart.csv", "r");
    char buff[255];
    while (fgets(buff, 255, file))
    {
        sscanf(buff, "%d,%[^,],%d", &node->UserID, node->StockID, &node->Quantity);
        if (node->UserID == user_id)
        {
            printf("\033[1mUser Id :\033[0m %d \n", user_id);
            struct Product *pdd = ps->products;
            while (pdd->next != NULL)
            {
                if (atoi(pdd->ID) + atoi(pdd->stockID) == atoi(node->StockID))
                {
                    printf("\033[1mProduct name :\033[0m %s \n", pdd->productName);
                    break;
                }
                pdd = pdd->next;
                i++;
            }
            printf("\033[1mQuantity :\033[0m %d \n", node->Quantity);
            // printf("Price : %d*%d = %d \n", node->Quantity, node-> )
            printf("---------------------------------------------\n");
        }
    }
            if(i == 0){
            printf("\033[0;31mYour cart is empty.\033[0m\n");
        }
    fclose(file);
}
// ยังไม่ได้เทส อัพเดตล่าสุด 16/05/67 02:53
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
// view_all_products ดีเเล้ว------------------------------------------------------------------------------------------------------------------------------------------------
void view_all_products(struct ProductSales *ps)
{

    char ID[6];
    char StockID[6];
    struct Product *head = ps->products;
    if (head == NULL)
    {
        printf("\033[0;31No products available.\033[0m\n");
        return;
    }
    printf("\033[1m                            All Products\033[0m\n");
    printf("------------------------------------------------------------------------------------\n");
    while (head != NULL)
    {
        printf("\033[1mID:\033[0m %s | ", head->ID);
        printf("\033[1mStock ID:\033[0m %s | ", head->stockID);
        printf("\033[1mProduct Name:\033[0m %-20s | ", head->productName);
        printf("\033[1mPrice:\033[0m %d\n", head->price);
        head = head->next;
    }
    printf("------------------------------------------------------------------------------------\n");
    product_detail(ps);
}

// run ดีเเล้ว------------------------------------------------------------------------------------------------------------------------------------------------

void run(struct ProductSales *ps)
{
    int i;
    load_data(ps);
    while (1)
    {
        login(ps);
        // printf("%p" , ps->current_user);
        if (ps->current_user != NULL)
        {
            remove_newline(ps->current_user->Role);
            // printf("|%s|" , ps->current_user->Role);
            if (strcmp(ps->current_user->Role, "admin") == 0)
            {
                clear_terminal();
                admin_menu(ps);
            }
            else if (strcmp(ps->current_user->Role, "user") == 0)
            {
                clear_terminal();
                customer_menu(ps);
            }
        }
        else
        {
            printf("033[1mType 1 to try again, type -1 to exit. : \033[0m");
            scanf("%d", &i);
            clear_terminal();
            if (i == -1)
            {
                return;
            }
        }
    }
}

int **readAllData(const char *cateFile, int *numRows, int *numCols)
{
    FILE *fp = fopen(cateFile, "r");
    if (fp == NULL)
    {
        perror("\033[0;31Failed to open file\033[0m");
        return NULL;
    }

    char buffer[1024];
    *numRows = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        (*numRows)++;
    }

    fseek(fp, 0, SEEK_SET);

    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    {
        fclose(fp);
        return NULL;
    }

    *numCols = 0;
    char *token = strtok(buffer, " ");
    while (token != NULL)
    {
        (*numCols)++;
        token = strtok(NULL, " ");
    }

    int **arr = (int **)malloc(*numRows * sizeof(int *));
    if (arr == NULL)
    {
        perror("\033[0;31Failed to allocate memory for rows\033[0m");
        fclose(fp);
        return NULL;
    }
    for (int i = 0; i < *numRows; i++)
    {
        arr[i] = (int *)malloc(*numCols * sizeof(int));
        if (arr[i] == NULL)
        {
            perror("\033[0;31Failed to allocate memory for columns\033[0m");
            for (int j = 0; j < i; j++)
            {
                free(arr[j]);
            }
            free(arr);
            fclose(fp);
            return NULL;
        }
    }

    fseek(fp, 0, SEEK_SET);

    int i = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        int j = 0;
        token = strtok(buffer, " ");
        while (token != NULL)
        {
            arr[i][j] = atoi(token);
            j++;
            token = strtok(NULL, " ");
        }
        i++;
    }

    fclose(fp);
    int min = 99999;
    int max = 0;
    for (int m = 0; m < i; m++)
    {
        for (int n = 0; n < i; n++)
        {
            if (arr[m][n] < min && arr[m][n])
            {
                min = arr[m][n]; // Update min if a smaller value is found
            }
            if (arr[m][n] > max)
            {
                max = arr[m][n] + 1; // Update max if a larger value is found
            }
        }
    }
    // printf("-%d %d-\n" , min ,max);
    for (int m = 0; m < i; m++)
    {
        for (int n = 0; n < i; n++)
        {
            arr[m][n] = 100 - (((arr[m][n] - min) / (double)(max - min)) * 100.0);
            // printf("%d ", arr[m][n]);
        }
        // printf("\n");
    }

    return arr;
}

void floydWarshall(int **dist, int V)
{
    int i, j, k;
    for (k = 0; k < V; k++)
    {
        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

int *printSortedRow(int **arr, int numRows, int numCols, int chosenRowIndex)
{
    floyd *sortSuggest = (floyd *)malloc(numCols * sizeof(floyd));
    if (chosenRowIndex < 0 || chosenRowIndex >= numRows)
    {
        printf("\033[0;33mInvalid row index\033[0m\n");
    }
    int *row = (int *)malloc((numCols) * sizeof(int));
    if (row == NULL)
    {
        perror("\033[0;31Failed to allocate memory for row\033[0m");
    }
    int k = 0;
    for (int j = 0; j <= numCols; j++)
    {
        sortSuggest[k++].floydValue = arr[chosenRowIndex][j];
        sortSuggest[k].position = j + 1;
    }

    for (int i = 0; i < numCols - 1; i++)
    {
        for (int j = 0; j < numCols - 1 - i; j++)
        {
            if (sortSuggest[j].floydValue > sortSuggest[j + 1].floydValue)
            {
                floyd temp = sortSuggest[j];
                sortSuggest[j] = sortSuggest[j + 1];
                sortSuggest[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i <= numCols - 1; i++)
    {
        // printf("%d | %d\n", sortSuggest[i].position, sortSuggest[i].floydValue);
    }
    // printf("\n");

    for (int i = 0; i <= numCols - 1; i++)
    {
        row[i] = (sortSuggest[i].position + 1);
        // printf("%d ", row[i]);
    }

    return row;
}

int *dealWithFloyd(int productChose)
{
    char *cateFile = "csv/cateFile.csv"; // Path to the cateFile
    int numRows = 0;
    int numCols = 0;
    int **result = readAllData(cateFile, &numRows, &numCols);

    // Assuming the number of columns determines the value of V
    int V = numCols;

    // Run the Floyd-Warshall algorithm
    floydWarshall(result, V);
    // printf("DB2");

    // Print the sorted row (e.g., row index 1)
    int *suggest = printSortedRow(result, numRows, numCols, productChose);

    // Free allocated memory
    for (int i = 0; i < numRows; i++)
    {
        free(result[i]);
    }
    free(result);

    return suggest;
}

void buy(struct ProductSales *ps, char ID[6], char StockID[6], int amount)
{
    int isRemain = 0;
    struct Product *product = searchProductByIDamdStockID(ps->products, ID, StockID);
    struct Product *tmp = product;
    int key1 = atoi(tmp->ID) + atoi(tmp->stockID);
    int key = atoi(ID) + atoi(StockID);
    while (tmp != NULL)
    {
        if ((key1 == key) && tmp->stock > 0)
        {
            // printf("%d\n", tmp->stock);
            isRemain = 1;
            break;
        }
        tmp = tmp->next;
    }

    struct Product *head = ps->products;
    struct Product *p;
    p = searchProductByIDamdStockID(head, ID, StockID);
    if (p->stock < amount)
    {
        printf("\033[0;31mOut of stock\033[0m\n");
    }
    else
    {
        printf("\n\033[0;32m%s was/were bought.\033[0m\n", p->productName);
        /*FILE *file = fopen("csv/addToCart.csv", "a");
        fprintf(file, "%d,%d,%d\n", ps->current_user->UserID, atoi(p->ID) + atoi(p->stockID), amount);
        fclose(file);*/
        p->stock = p->stock - amount;
        p->buy = p->buy + amount;
        if (isRemain == 1)
        {
            printf("\'\033[1mProduct Remaining :\033[0m %d\'\n", p->stock);
        }
        else if (isRemain == 0)
        {
            printf("\033[0;31m\'Out Of Stock\'\033[0m\n");
        }
        FILE *fp = fopen("csv/product.csv", "w");
        while (head != NULL)
        {
            fprintf(fp, "%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d\n", head->ID, head->stockID, head->productName, head->price, head->imports,
                    head->exports, head->category, head->stock, head->access,
                    head->addToCart, head->buy, head->key);
            head = head->next;
        }
        fclose(fp);
    }
}

//------------------------------------------------------------------------MAIN------------------------------------------------------------------------
int main()
{
    struct ProductSales *app = malloc(sizeof(struct ProductSales));
    if (app == NULL)
    {
        printf("\033[0;31mFailed to allocate memory for app\033[0m\n");
        return 1;
    }
    load_data(app);
    main_menu(app);

    // Don't forget to free the memory you allocated
    free(app);

    return 0;
}