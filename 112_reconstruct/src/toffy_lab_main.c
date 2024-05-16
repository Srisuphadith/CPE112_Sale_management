#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define V 4
#define INF 99999 
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
struct Product *searchProductByIDamdStockID(struct Product *head, char *ID, char *StockID);
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
//load_data ดีเเล้ว------------------------------------------------------------------------------------------------------------------------------------------------
void load_data(struct ProductSales *ps) {
    FILE *fp1, *fp2, *fp3;
    fp1 = fopen("csv/product.csv", "r");
    fp2 = fopen("csv/userHistory.csv", "r");
    fp3 = fopen("csv/login.csv", "r");

    // Check if files were opened successfully
    if (!fp1 || !fp2 || !fp3) {
        fprintf(stderr, "Failed to open one or more files.\n");
        if (fp1) fclose(fp1);
        if (fp2) fclose(fp2);
        if (fp3) fclose(fp3);
        return;
    }

    char buffer[BUFFER_SIZE];
    struct Product *head = NULL, *tail = NULL;
    struct History *head1 = NULL, *tail1 = NULL;
    struct User *head2 = NULL, *tail2 = NULL;

    // Load product data
    while (fgets(buffer, BUFFER_SIZE, fp1)) {
        struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
        if (!newNode) {
            fprintf(stderr, "Memory allocation failed.\n");
            break;
        }
        if (sscanf(buffer, "%6[^,],%6[^,],%99[^,],%d,%6[^,],%6[^,],%49[^,],%d,%d,%d,%d,%d",
                   newNode->ID, newNode->stockID, newNode->productName, &newNode->price, newNode->imports,
                   newNode->exports, newNode->category, &newNode->stock, &newNode->access,
                   &newNode->addToCart, &newNode->buy, &newNode->key) != 12) {
            fprintf(stderr, "Error parsing product data.\n");
            free(newNode);
            continue;
        }
        newNode->next = NULL;
        if (!head) head = newNode;
        else tail->next = newNode;
        tail = newNode;
    }
    ps->products = head;
    fclose(fp1);

    // Load user history data
    while (fgets(buffer, BUFFER_SIZE, fp2)) {
        struct History *newNode = (struct History *)malloc(sizeof(struct History));
        if (!newNode) {
            fprintf(stderr, "Memory allocation failed.\n");
            break;
        }
        if (sscanf(buffer, "%d,%d,%6[^,],%5[^,]", &newNode->id, &newNode->user_id, newNode->date, newNode->pro_id) != 4) {
            fprintf(stderr, "Error parsing user history data.\n");
            free(newNode);
            continue;
        }
        newNode->next = NULL;
        if (!head1) head1 = newNode;
        else tail1->next = newNode;
        tail1 = newNode;
    }
    ps->user_history = head1;
    fclose(fp2);

    // Load user data
    while (fgets(buffer, BUFFER_SIZE, fp3)) {
        struct User *newNode = (struct User *)malloc(sizeof(struct User));
        if (!newNode) {
            fprintf(stderr, "Memory allocation failed.\n");
            break;
        }
        if (sscanf(buffer, "%d,%99[^,],%99[^,],%19[^,]", &newNode->UserID, newNode->Username, newNode->Password, newNode->Role) != 4) {
            fprintf(stderr, "Error parsing user data.\n");
            free(newNode);
            continue;
        }
        newNode->next = NULL;
        if (!head2) head2 = newNode;
        else tail2->next = newNode;
        tail2 = newNode;
    }
    ps->users = head2;
    fclose(fp3);
}

struct Product *createNode_StrProduct(const char ID[], const char stockID[], const char productName[], int price,
                                      const char imports[], const char exports[], const char category[],
                                      int stock, int access, int addToCart, int buy, int key)
{
    struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory allocation failed!\n");
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

struct User* createNode_User(const char Username[], const char Password[], const char Role[], int UserID) {
    struct User *newNode = (struct User *)malloc(sizeof(struct User));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
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

struct History* createNode_History(int id, int user_id, const char date[7], const char pro_id[6]) {
    struct History *newNode = (struct History *)malloc(sizeof(struct History));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
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

struct PurchaseHistory* createNode_PurchaseHistory(int UserID, const char StockID[], int Quantity) {
    struct PurchaseHistory *newNode = (struct PurchaseHistory *)malloc(sizeof(struct PurchaseHistory));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->UserID = UserID;
    strncpy(newNode->StockID, StockID, sizeof(newNode->StockID) - 1);
    newNode->StockID[sizeof(newNode->StockID) - 1] = '\0';

    newNode->Quantity = Quantity;
    newNode->next = NULL;

    return newNode;
}

struct CartItem *createNode_CartItem(int key, int quantity){
    struct CartItem *newNode = (struct CartItem *)malloc(sizeof(struct CartItem));
    if (newNode == NULL){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->quantity = quantity;
    newNode->next = NULL;
    return newNode;
}

void insertNode(struct Product **head, struct Product *newNode){
    if (newNode == NULL){
        printf("Cannot insert NULL node!\n");
        return;
    }
    if (*head == NULL){
        *head = newNode;
        }
    else{
        struct Product *temp = *head;
        while (temp->next != NULL){
            temp = temp->next;
            }
        temp->next = newNode;
        }
}

void insertNodeUser(struct User **head, struct User *newNode){
    if (newNode == NULL){
        printf("Cannot insert NULL node!\n");
        return;
    }

    if (*head == NULL){
        *head = newNode;
    }
    else{
        struct User *temp = *head;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

struct User *searchUserByUsername(struct User *head, const char Username[]){
    if (head == NULL){
        printf("List is empty!\n");
        return NULL;
    }
    struct User *temp = head;
    while (temp != NULL){
        if (strcmp(temp->Username, Username) == 0){
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

struct User *searchUserByUsernameAndPassword(struct User *head, const char *username, const char *password){
    if (head == NULL){
        printf("List is empty!\n");
        return NULL;
    }
    struct User *current = head;
    while (current != NULL){
        if (strcmp(current->Username, username) == 0 && strcmp(current->Password, password) == 0){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct History *searchHistoryById(struct History *head, int id){
    if (head == NULL){
        printf("List is empty!\n");
        return NULL;
    }
    struct History *temp = head;
    while (temp != NULL){
        if (temp->id == id){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct History *searchHistoryByuser_id(struct History *head, int user_id){
    if (head == NULL){
        printf("List is empty!\n");
        return NULL;
    }
    struct History *temp = head;
    while (temp != NULL){
        if (temp->user_id == user_id){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct PurchaseHistory *searchPurchaseHistoryByUserID(struct PurchaseHistory *head, int UserID){
    if (head == NULL){
        printf("List is empty!\n");
        return NULL;
    }
    struct PurchaseHistory *temp = head;
    while (temp != NULL){
        if (temp->UserID == UserID){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct PurchaseHistory *searchPurchaseHistoryByStockID(struct PurchaseHistory *head, const char StockID[]){
    if (head == NULL){
        printf("List is empty!\n");
        return NULL;
    }

    struct PurchaseHistory *temp = head;
    while (temp != NULL){
        if (strcmp(temp->StockID, StockID) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct CartItem *searchCartItemByKey(struct CartItem *head, int key){
    if (head == NULL){
        printf("List is empty!\n");
        return NULL;
    }
    struct CartItem *temp = head;
    while (temp != NULL){
        if (temp->key == key){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

struct Product *searchProductByIDamdStockID(struct Product *head, const char *ID, const char *StockID){
    if (head == NULL){
        printf("List is empty!\n");
        return NULL;
    }
    while (head != NULL){
        if (strcmp(head->ID, ID) == 0 && strcmp(head->stockID, StockID) == 0){
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void log_activity(struct ProductSales *ps, const char *action, const char *details){
    FILE *file;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char timestamp[20];
    char user[100];
    if (ps->current_user != NULL){
        strcpy(user, ps->current_user->Username);
    }
    else{
        strcpy(user, "System");
    }
    sprintf(timestamp, "%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    file = fopen("activity_log.csv", "a");
    if (file == NULL){
        printf("Error opening file!\n");
        return;
    }
    if (fprintf(file, "%s,%s,%s,%s\n", timestamp, user, action, details) < 0){
        printf("Error writing to file!\n");
    }
    fclose(file);
}


void sortByCat(char categories[]) {
    FILE *file = fopen("allCategory.csv", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return;
    }
    fclose(file);
}

void remove_newline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void login(struct ProductSales *ps){
    char username[100];
    char password[100];
    int attempts = 0;

    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    remove_newline(username);

    struct User *user = searchUserByUsername(ps->users, username);
    if (user != NULL){
        do{
            printf("Password: ");
            fgets(password, sizeof(password), stdin);
            remove_newline(password);

            if (strcmp(user->Password, password) == 0){
                ps->current_user = user;
                printf("Login successful!\n");
                return;
            }
            else{
                attempts++;
                printf("Incorrect password. Attempts left: %d\n", 3 - attempts);
            }
        } while (attempts < 3);
        printf("Maximum login attempts exceeded. Please try again later.\n");
    }
    else{
        printf("User not found\n");
    }
}


void register_user_NEW(struct ProductSales *ps){
    char username[100], password[100];
    int maxUserID = 0;
    int userID;

    // Read existing user IDs from the CSV file and find the maximum
    FILE *fp = fopen("csv/login.csv", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d,%99[^,],%99[^,\n]", &userID, username, password) == 3) {
            if (userID > maxUserID) {
                maxUserID = userID;
            }
        }
        fclose(fp);
    } else {
        printf("Error: Unable to open user file for reading.\n");
        return;
    }

    printf("Enter new username: ");
    scanf("%99s", username);
    remove_newline(username);

    printf("Enter password: ");
    scanf("%99s", password);
    remove_newline(password);

    userID = maxUserID + 1;

    // Create a new user node
    struct User *user = createNode_User(username, password, "user", userID);
    if (user == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Insert the new user node into the user list
    insertNodeUser(&(ps->users), user);

    // Open the file in append mode to add the new user
    fp = fopen("csv/login.csv", "a");
    if (fp != NULL) {
        fprintf(fp, "%d,%s,%s,%s\n", userID, username, password, "user");
        fclose(fp);
        printf("Registration successful. UserID: %d\n", userID);
    } else {
        printf("Error: Unable to open user file for writing.\n");
        // Since registration failed, free the memory allocated for the user node
        free(user);
    }
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
        register_user_NEW(ps);
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
        printf("\nAdmin Menu\n");
        printf("1. Manage Products\n");
        printf("2. View User Orders\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &option) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (option)
        {
        case 1:
            manage_products(ps);
            break;
        case 2:
            // view_orders(ps);
            break;
        case 3:
            printf("Exiting admin menu...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (option != 3);
}

void manage_products(struct ProductSales *ps){
    int choice;

    while (1){
        printf("\nManage Products:\n");
        printf("1. View Products\n");
        printf("2. Add Product\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Back to Admin Menu\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        
        switch (choice)
        {
            case 1:
                view_products(ps);
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
                break;
        }
    }
}

void view_products(struct ProductSales *ps){
    char outputFileName[] = "csv/product.csv";
    FILE *file = fopen(outputFileName, "r");
    if (file == NULL){
        printf("Error: Failed to open file '%s'\n", outputFileName);
        return;
    }

    struct Product *newNode;
    int num = 0;
    char buffer[255];

    while (fgets(buffer, 255, file)){
        newNode = (struct Product *)malloc(sizeof(struct Product));
        if (newNode == NULL){
            printf("Error: Memory allocation failed\n");
            fclose(file);
            return;
        }

        if (sscanf(buffer, "%6[^,],%6[^,],%100[^,],%d,%7[^,],%7[^,],%50[^,],%d,%d,%d,%d,%d",
                   newNode->ID, newNode->stockID, newNode->productName, &newNode->price, newNode->imports,
                   newNode->exports, newNode->category, &newNode->stock, &newNode->access,
                   &newNode->addToCart, &newNode->buy, &newNode->key) != 12)
        {
            printf("Error: Invalid data format in file '%s'\n", outputFileName);
            free(newNode);
            fclose(file);
            return;
        }

        num++;
        printf("No. %d\n", num);
        printf("ID: %s\n", newNode->ID);
        printf("Stock ID: %s\n", newNode->stockID);
        printf("Product Name: %s\n", newNode->productName);
        printf("Price: %d\n", newNode->price);

        free(newNode);
    }

    if (num == 0){
        printf("No products found in the file.\n");
    }
    fclose(file);
}


void add_product(struct ProductSales *ps){
    struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
    if (newNode == NULL){
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    char filename[] = "csv/product.csv";

    printf("Enter new ID: ");
    scanf("%5s", newNode->ID);
    getchar();

    printf("Enter new stock ID: ");
    scanf("%5s", newNode->stockID);
    getchar();

    printf("Enter new product name: ");
    fgets(newNode->productName, sizeof(newNode->productName), stdin);
    remove_newline(newNode->productName);

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
    remove_newline(newNode->category);

    printf("Enter new stock: ");
    scanf("%d", &newNode->stock);
    getchar();

    newNode->access = 0;
    newNode->addToCart = 0;
    newNode->buy = 0;
    newNode->key = 0;
    newNode->next = NULL;

    // Write new product data to the CSV file
    FILE *file = fopen(filename, "a");
    if (file == NULL){
        perror("File opening error");
        free(newNode);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d\n",
            newNode->ID, newNode->stockID, newNode->productName, newNode->price,
            newNode->imports, newNode->exports, newNode->category, newNode->stock,
            newNode->access, newNode->addToCart, newNode->buy, newNode->key);

    fclose(file);

    // Insert new product node into the list
    if (ps->products == NULL){
        ps->products = newNode;
    }
    else{
        struct Product *current = ps->products;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
}

//update_product ดีเเล้ว------------------------------------------------------------------------------------------------------------------------------------------------

void update_product(struct ProductSales *ps)
{
    char filename[] = "csv/product.csv";
    char idToEdit[7]; // Increase size to hold 6 characters + null terminator

    printf("Enter ID to edit: ");
    scanf("%6s", idToEdit);
    getchar(); // Clear the newline character left by scanf

    struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
    if (newNode == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    printf("Enter new ID: ");
    scanf("%6s", newNode->ID);
    getchar();

    printf("Enter new stock ID: ");
    scanf("%6s", newNode->stockID);
    getchar();

    printf("Enter new product name: ");
    fgets(newNode->productName, sizeof(newNode->productName), stdin);
    remove_newline(newNode->productName);

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
    remove_newline(newNode->category);

    printf("Enter new stock: ");
    scanf("%d", &newNode->stock);
    getchar();

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("File opening error");
        free(newNode);
        exit(EXIT_FAILURE);
    }

    FILE *tempFile = fopen("csv/temp.csv", "w");
    if (tempFile == NULL)
    {
        perror("Temporary file opening error");
        free(newNode);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        char id[7];
        sscanf(line, "%6[^,]", id);
        if (strcmp(id, idToEdit) == 0)
        {
            fprintf(tempFile, "%s,%s,%s,%d,%s,%s,%s,%d\n",
                    newNode->ID, newNode->stockID, newNode->productName, newNode->price,
                    newNode->imports, newNode->exports, newNode->category, newNode->stock);
            found = 1;
        }
        else
        {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        printf("ID %s not found in %s.\n", idToEdit, filename);
    }
    else
    {
        if (remove(filename) != 0)
        {
            perror("Error deleting original file");
            exit(EXIT_FAILURE);
        }

        if (rename("csv/temp.csv", filename) != 0)
        {
            perror("Error renaming temporary file");
            exit(EXIT_FAILURE);
        }
    }

    free(newNode);
}


void delete_product(struct ProductSales *ps){
    const char *filename = "csv/product.csv";

    char idToDelete[7], stockIdToDelete[7];
    printf("Enter ID to delete: ");
    scanf("%6s", idToDelete);
    printf("Enter Stock ID to delete: ");
    scanf("%6s", stockIdToDelete);

    FILE *file = fopen(filename, "r");
    if (file == NULL){
        perror("File opening error");
        exit(EXIT_FAILURE);
    }

    FILE *tempFile = fopen("csv/temp.csv", "w");
    if (tempFile == NULL){
        perror("Temporary file opening error");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), file)){
        char id[7], stockId[7];
        sscanf(line, "%6[^,],%6[^,]", id, stockId);
        if (strcmp(id, idToDelete) != 0 || strcmp(stockId, stockIdToDelete) != 0){
            fputs(line, tempFile);
        }
        else{
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found){
        printf("Product with ID %s and Stock ID %s not found in %s.\n", idToDelete, stockIdToDelete, filename);
    }
    else{
        if (remove(filename) != 0){
            perror("Error deleting original file");
            exit(EXIT_FAILURE);
        }

        if (rename("csv/temp.csv", filename) != 0){
            perror("Error renaming temporary file");
            exit(EXIT_FAILURE);
        }

        printf("Product with ID %s and Stock ID %s deleted successfully.\n", idToDelete, stockIdToDelete);
    }
}

void view_orders(struct ProductSales *ps)
{
    char ID[6];
    char StockID[6];
    struct Product *head = ps->products;
    struct History *node = ps->user_history;
    while (head != NULL)
    {
        printf("User ID: %d | ", node->user_id);
        printf("Product ID: %s |", head->ID);
        printf("Product Name: %s | ", head->productName);
        printf("Price: %d\n", head->price);
        head = head->next;
    }
    product_detail(ps);
}

    

// }
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

    while (1){
        printf("\nCustomer Menu:\n");
        printf("1. View Recommended Products\n");
        printf("2. View All Products\n");
        printf("3. View Cart\n");
        // printf("4. Checkout\n"); // Enable option for checking out
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice){
        case 1:
            view_recommended_products(ps);
            break;
        case 2:
            view_all_products(ps);
            break;
        case 3:
            view_cart(ps);
            break;
        case 4:
            // checkout(ps); // Enable option for checking out
            break;
        case 5:
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}


// sorting For suggesion

void swap(struct Product **a, struct Product **b){
    struct Product *tmp = *a;
    *a = *b;
    *b = tmp;
}


void sortingSuggestValue(struct Product **start) {
    if (*start == NULL || (*start)->next == NULL) {
        return;
    }

    // Get the length of the linked list
    int n = 0;
    struct Product *tmp = *start;
    while (tmp != NULL) {
        n++;
        tmp = tmp->next;
    }

    // Bubble sort the linked list based on the calculated value
    for (int i = 0; i < n - 1; i++) {
        struct Product **current = start;
        for (int j = 0; j < n - i - 1; j++) {
            struct Product *next = (*current)->next;
            int currentValue = (*current)->buy * 4 + (*current)->addToCart * 2 + (*current)->access;
            int nextValue = next->buy * 4 + next->addToCart * 2 + next->access;

            if (currentValue < nextValue) {
                struct Product *temp = *current;
                *current = next;
                temp->next = next->next;
                (*current)->next = temp;
            }
            current = &(*current)->next;
        }
    }
}



void printNode(struct Product **start){
    struct Product *ptr = *start;
    if (ptr == NULL){
        return;
    }

    while (ptr != NULL){
        printf("%s %d\n", ptr->productName, (ptr->buy) * 4 + (ptr->addToCart) * 2 + (ptr->access));
        ptr = ptr->next;
    }
}


void view_recommended_products(struct ProductSales *ps) {
    // Uncomment the line below if you want to clear the terminal.
    // clear_terminal();
    
    struct Product *product = ps->products;
    // printf("Now vrp\n");
    sortingSuggestValue(&product);

    // Assuming we want to recommend the first 5 products after sorting
    int recommendation_count = 5;
    struct Product *tmp = product;

    for (int i = 0; i < recommendation_count && tmp != NULL; i++) {
        printf("ID: %s | ", tmp->ID);
        printf("Stock ID: %s | ", tmp->stockID);
        printf("Product Name: %s | ", tmp->productName);
        printf("Price: %d\n", tmp->price);
        tmp = tmp->next;
    }
    product_detail(ps);
}

void product_detail(struct ProductSales *ps)
{
    char productId[7], stockId[7];
    printf("Enter ProductID and StockID of the product you want to view details (or type -1 to exit)\n");
    printf("ProductID: ");
    scanf("%s", productId);
    remove_newline(productId);
    if (strcmp(productId, "-1") == 0)
    {
        return;
    }
    printf("StockID: ");
    scanf("%s", stockId);
    remove_newline(stockId);
    if (strcmp(stockId, "-1") == 0)
    {
        return;
    }

    struct Product *product = searchProductByIDamdStockID(ps->products, productId, stockId);
    if (product == NULL)
    {
        printf("Product not found.\n");
        return;
    }

    printf("Product ID: %s\n", product->stockID);
    printf("Product Name: %s | Category: %s\n", product->productName, product->category);
    printf("Status: %s\n", (product->stock > 0) ? "Product Remaining" : "Out Of Stock");
    printf("Price: %d\n", product->price);

    // Menu
    int option;
    printf("Menu:\n");
    printf("1. Add to cart\n");
    printf("2. Buy\n");
    printf("Enter your choice (type -1 to go back): ");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        printf("Enter required quantity: ");
        int amount;
        scanf("%d", &amount);
        // Call add_to_cart function here
        break;
    case 2:
        // Handle buy action
        break;
    case -1:
        return;
    default:
        printf("Invalid choice.\n");
    }
}


// //ต้องทำ*********************************

void add_to_cart(struct ProductSales *ps, char ID[6], char StockID[6], int amount)
{
    char filename[] = "csv/product.csv";
    struct Product *head = ps->products;
    struct Product *p;
    p = searchProductByIDamdStockID(head, ID, StockID);
    if (p->stock < amount)
    {
        printf("Out of stock\n");
    }
    else
    {
        printf("%s is added\n", p->productName);
        //  FILE *file = fopen("csv/addToCart.csv", "a");
        //  fprintf(file, "%d,%d,%d\n", ps->current_user->UserID, atoi(p->ID) + atoi(p->stockID), amount);
        //  fclose(file);
        p->stock = p->stock-amount;
        p->addToCart = p->addToCart+amount;
        // 
        //เพิ่มๆๆๆ
        char newData[MAX_LINE_LENGTH];
        snprintf(newData, sizeof(newData), "%s,%s,%s,%d,%s,%s,%s,%d\n",
             p->ID, p->stockID, p->productName, p->price, p->imports, p->exports, p->category, p->stock);

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
        if (strcmp(id, p->ID) == 0)
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
        printf("ID %s not found in %s.\n", p->ID, filename);
    }
    // write to file


        
    }
}


void view_cart(struct ProductSales *ps){
    int user_id = ps->current_user->UserID;
    struct PurchaseHistory *cart_items[MAX_PRODUCTS] = {NULL}; // Assuming MAX_PRODUCTS is the maximum number of unique products in the cart
    FILE *file = fopen("csv/addToCart.csv", "r");

    if (file == NULL){
        perror("Error opening file");
        return;
    }

    // Load cart items into memory
    struct PurchaseHistory *node = (struct PurchaseHistory *)malloc(sizeof(struct PurchaseHistory));
    while (fscanf(file, "%d,%[^,],%d", &node->UserID, node->StockID, &node->Quantity) != EOF)
    {
        if (node->UserID == user_id){
            // Add cart item to the array based on StockID
            int index = atoi(node->StockID); // Assuming StockID is unique and can be converted to an integer
            cart_items[index] = node;
        }
        else{
            free(node); // Free memory if not for the current user
        }
        node = (struct PurchaseHistory *)malloc(sizeof(struct PurchaseHistory)); // Allocate memory for the next node
    }
    fclose(file);

    // Print cart items
    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        if (cart_items[i] != NULL)
        {
            printf("User Id: %d\n", user_id);
            printf("Product name: %s\n", getProductNameByID(ps->products, cart_items[i]->StockID)); // Implement a function to get product name by ID
            printf("Quantity: %d\n", cart_items[i]->Quantity);
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
    char ID[6];
    char StockID[6];
    struct Product *head = ps->products;
    while (head != NULL)
    {
        printf("ID: %s | ", head->ID);
        printf("Stock ID: %s | ", head->stockID);
        printf("Product Name: %s | ", head->productName);
        printf("Price: %d\n", head->price);
        head = head->next;
    }
    product_detail(ps);
}

//run ดีเเล้ว------------------------------------------------------------------------------------------------------------------------------------------------

void run(struct ProductSales *ps)
{
    int i;
    load_data(ps);
    while (1) {
        login(ps);
        if (ps->current_user != NULL) {
            remove_newline(ps->current_user->Role);
            if (strcmp(ps->current_user->Role, "admin") == 0) {
                admin_menu(ps);
            } else if (strcmp(ps->current_user->Role, "user") == 0) {
                customer_menu(ps);
            }
        } else {
            printf("Type 1 to try again, type -1 to exit. : ");
            scanf("%d", &i);
            if (i == -1) {
                return;
            }
        }
    }
}


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

void shop(){
    
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