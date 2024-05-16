#include <stdio.h>
#include "Structure.h"
#include "AVL.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFFER_SIZE 255

// struct Product *createNode_StrProduct(char ID[], char stockID[], char productName[], int price,
//                                       char imports[], char exports[], char category[],
//                                       int stock, int access, int addToCart, int buy, int key)
// {
//     struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
//     if (newNode == NULL)
//     {
//         printf("Memory allocation failed!\n");
//         exit(1);
//     }
//     strncpy(newNode->ID, ID, sizeof(newNode->ID) - 1);
//     newNode->ID[sizeof(newNode->ID) - 1] = '\0';
//     strncpy(newNode->stockID, stockID, sizeof(newNode->stockID) - 1);
//     newNode->stockID[sizeof(newNode->stockID) - 1] = '\0';
//     strncpy(newNode->productName, productName, sizeof(newNode->productName) - 1);
//     newNode->productName[sizeof(newNode->productName) - 1] = '\0';
//     newNode->price = price;
//     strncpy(newNode->imports, imports, sizeof(newNode->imports) - 1);
//     newNode->imports[sizeof(newNode->imports) - 1] = '\0';
//     strncpy(newNode->exports, exports, sizeof(newNode->exports) - 1);
//     newNode->exports[sizeof(newNode->exports) - 1] = '\0';
//     strncpy(newNode->category, category, sizeof(newNode->category) - 1);
//     newNode->category[sizeof(newNode->category) - 1] = '\0';
//     newNode->stock = stock;
//     newNode->access = access;
//     newNode->addToCart = addToCart;
//     newNode->buy = buy;
//     newNode->key = key;
//     newNode->next = NULL;
//     return newNode;
// }

// struct User* createNode_User(char Username[], char Password[], char Role[], int UserID) {
//     struct User *newNode = (struct User*)malloc(sizeof(struct User));
//     if (newNode == NULL) {
//         printf("Memory allocation failed!\n");
//         exit(1);
//     }
//     strcpy(newNode->Username, Username);
//     strcpy(newNode->Password, Password);
//     strcpy(newNode->Role, Role);
//     newNode->UserID = UserID;
//     newNode->next = NULL;
//     return newNode;
// }

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
// void load_data(struct ProductSales *ps)
// {

//     // Load data from CSV files here
//     FILE *fp1 = fopen("csv/product.csv", "r");
//     FILE *fp2 = fopen("csv/userHistory.csv", "r");
//     FILE *fp3 = fopen("csv/login.csv", "r");
//     char buffer[255];
//     int i = 0;
//     struct Product *head = NULL;

//     while (fgets(buffer, 255, fp1))
//     {
//         if (head == NULL)
//         {
//             struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
//             head = newNode;
//             sscanf(buffer, "%6[^,],%6[^,],%100[^,],%d,%7[^,],%7[^,],%50[^,],%d,%d,%d,%d,%d",
//                    newNode->ID, newNode->stockID, newNode->productName, &newNode->price, newNode->imports,
//                    newNode->exports, newNode->category, &newNode->stock, &newNode->access,
//                    &newNode->addToCart, &newNode->buy, &newNode->key);
//             newNode->next = NULL;
//         }
//         else
//         {
//             struct Product *ptr = head;
//             while (ptr->next != NULL)
//             {
//                 ptr = ptr->next;
//             }
//             struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
//             ptr->next = newNode;
//             newNode->next = NULL;
//             sscanf(buffer, "%6[^,],%6[^,],%100[^,],%d,%7[^,],%7[^,],%50[^,],%d,%d,%d,%d,%d",
//                    newNode->ID, newNode->stockID, newNode->productName, &newNode->price, newNode->imports,
//                    newNode->exports, newNode->category, &newNode->stock, &newNode->access,
//                    &newNode->addToCart, &newNode->buy, &newNode->key);
//         }
//     }

//     ps->products = head;
//     struct History *head1 = NULL;
//     while (fgets(buffer, 255, fp2))
//     {
//         // printf("%s",buffer);
//         if (head1 == NULL)
//         {
//             struct History *newNode = (struct History *)malloc(sizeof(struct History));
//             head1 = newNode;
//             sscanf(buffer, "%d,%d,%7[^,],%6[^,]", &newNode->id, &newNode->user_id, newNode->date, newNode->pro_id);
//             newNode->next = NULL;
//         }
//         else
//         {
//             struct History *ptr1 = head1;
//             while (ptr1->next != NULL)
//             {
//                 ptr1 = ptr1->next;
//             }
//             struct History *newNode = (struct History *)malloc(sizeof(struct History));
//             ptr1->next = newNode;
//             newNode->next = NULL;
//             sscanf(buffer, "%d,%d,%7[^,],%6[^,]", &newNode->id, &newNode->user_id, newNode->date, newNode->pro_id);
//         }
//     }
//     ps->user_history = head1;
//     struct User *head2 = NULL;
//     while(fgets(buffer,255,fp3)){
//         if(head2 == NULL){
//             struct User *newNode = (struct User *)malloc(sizeof(struct User));
//             head2 = newNode;
//             sscanf(buffer,"%d,%100[^,],%100[^,],%20[^,]",&newNode->UserID,newNode->Username,newNode->Password,newNode->Role);
//             newNode->next = NULL;
//         }else{
//             struct User *ptr2 = head2;
//             while (ptr2->next != NULL)
//             {
//                 ptr2 = ptr2->next;
//             }
//             struct User *newNode = (struct User *)malloc(sizeof(struct User));
//             ptr2->next = newNode;
//             newNode->next = NULL;
//             sscanf(buffer,"%d,%100[^,],%100[^,],%20[^,]",&newNode->UserID,newNode->Username,newNode->Password,newNode->Role);
//         }
//     }
    
//     fclose(fp1);
//     fclose(fp2);
//     fclose(fp3);
// }

// void update_product(struct ProductSales *ps)
// {
//     char stock_id[50];
//     printf("Enter Stock ID of the product to update: ");
//     scanf("%s", stock_id);
//     struct Product *head = ps->products;
//     while (head != NULL)
//     {
//         if (strcmp(head->ID, stock_id) == 0)
//         {
//             break;
//         }
//         head = head->next;
//     }
//     if (head == NULL)
//     {
//         printf("Product not found.\n");
//         return;
//     }
//     printf("StockID: %s, Name: %s, Quantity : %d, Type : %s\n", head->stockID, head->productName, head->stock, head->category);
//     printf("Enter new Product Name: ");
//     scanf("%s", head->productName);
//     printf("Enter new Import Date (YYYY-MM-DD): ");
//     scanf("%s", head->imports);
//     printf("Enter new Export Date (YYYY-MM-DD): ");
//     scanf("%s", head->exports);
//     printf("Enter new Categories: ");
//     scanf("%s", head->category);
//     printf("update successfully");
//     head = ps->products;
//     FILE *fp = fopen("csv/product.csv","w");
//     while (head != NULL)
//     {
//         fprintf(fp,"%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d\n", head->ID, head->stockID, head->productName, head->price, head->imports,
//                    head->exports, head->category, head->stock, head->access,
//                    head->addToCart, head->buy, head->key);
//         head = head->next;
//     }
//     fclose(fp);

// }
// void update_product(struct ProductSales *ps)
// {
//     struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
//     const char *filename = "product.csv";
//     char idToEdit[7]; // เพิ่มขนาดเป็น 7 เพื่อให้สามารถเก็บ 6 อักขระ + null terminator


//     printf("Enter ID to edit: ");
//     scanf("%5s", idToEdit);
//     getchar(); // Clear the newline character left by scanf

//     // รับข้อมูลใหม่สำหรับแถว
//     printf("Enter new ID: ");
//     scanf("%5s", newNode->ID);
//     getchar();
//     printf("Enter new stock ID: ");
//     scanf("%5s", newNode->stockID);
//     getchar();
//     printf("Enter new product name: ");
//     fgets(newNode->productName, sizeof(newNode->productName), stdin);
//     newNode->productName[strcspn(newNode->productName, "\n")] = '\0'; // Remove newline character

//     printf("Enter new price: ");
//     scanf("%d", &newNode->price);
//     getchar();

//     printf("Enter new imports: ");
//     scanf("%6s", newNode->imports);
//     getchar();
//     printf("Enter new exports: ");
//     scanf("%6s", newNode->exports);
//     getchar();
//     printf("Enter new category: ");
//     fgets(newNode->category, sizeof(newNode->category), stdin);
//     newNode->category[strcspn(newNode->category, "\n")] = '\0'; // Remove newline character

//     printf("Enter new stock: ");
//     scanf("%d", &newNode->stock);
//     getchar();

//     // สร้างข้อมูลแถวใหม่ในรูปแบบ CSV
//     char newData[MAX_LINE_LENGTH];
//     snprintf(newData, sizeof(newData), "%s,%s,%s,%d,%s,%s,%s,%d\n",
//              newNode->ID, newNode->stockID, newNode->productName, newNode->price, newNode->imports, newNode->exports, newNode->category, newNode->stock);

//     FILE *file = fopen(filename, "r");
//     if (file == NULL)
//     {
//         perror("File opening error");
//         exit(EXIT_FAILURE);
//     }

//     char line[1024];
//     char *rows[1000];
//     int rowCount = 0;
//     int found = 0;

//     while (fgets(line, sizeof(line), file))
//     {
//         char id[7];
//         sscanf(line, "%6[^,]", id);
//         if (strcmp(id, idToEdit) == 0)
//         {
//             // Replace the line with new data
//             rows[rowCount] = strdup(newData);
//             found = 1;
//         }
//         else
//         {
//             rows[rowCount] = strdup(line); // Copy the line to memory
//         }
//         rowCount++;
//     }

//     fclose(file);

//     if (found)
//     {
//         file = fopen(filename, "w");
//         if (file == NULL)
//         {
//             perror("File opening error");
//             exit(EXIT_FAILURE);
//         }

//         for (int i = 0; i < rowCount; i++)
//         {
//             fputs(rows[i], file);
//             free(rows[i]); // Free the memory
//         }

//         fclose(file);
//     }
//     else
//     {
//         printf("ID %s not found in %s.\n", idToEdit, filename);
//     }
//     // write to file
// }
// void view_products(struct ProductSales *ps, char outputFileName[])
// {
//     // View products logic here
//     FILE *file = fopen(outputFileName, "r");
//     if (file == NULL)
//     {
//        printf("No statement found in the file.\n");
//        return;
//     }
//     struct User users[100];
//     struct Product *newNode = (struct Product *)malloc(sizeof(struct Product));
//     int num = 0;
//     while (fscanf(file, "%s %d", newNode->ID, &newNode->price) != EOF)
//     {
//         num++;
//         printf("No. %d  ID : %s Price = %d\n",num, newNode->ID, newNode->price);
//     }
//     fclose(file);
//     // add_product(&ps, num);
// }
// void log_activity(struct ProductSales *ps, char *action, char *details)
// {
//     FILE *file;
//     time_t t = time(NULL);
//     struct tm tm = *localtime(&t);
//     char timestamp[20];
//     char user[100];
//     if(ps->current_user != NULL){
//         strcpy(user,ps->current_user->Username);
//     }else{
//         strcpy(user,"System");
//     }

//     sprintf(timestamp, "%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

//     file = fopen("activity_log.csv", "a");
//     if (file == NULL)
//     {
//         printf("Error opening file!\n");
//         return;
//     }
//     fprintf(file, "%s,%s,%s,%s\n", timestamp, user, action, details);
//     fclose(file);
// }
// void view_cart(struct ProductSales *ps)
// {
//     int user_id = ps->current_user->UserID;
//     struct Product *head = ps->products;
//     struct PurchaseHistory *node = (struct PurchaseHistory*)malloc(sizeof(struct PurchaseHistory));
//     FILE *file = fopen("csv/addToCart.csv", "r");

//     while(fscanf(file,"%d,%[^,],%d",&node->UserID,node->StockID,&node->Quantity) != EOF){
//         if(node->UserID == user_id){
//         printf("User Id : %d \n",user_id);
//         struct Product *pdd = ps->products;
//         while (pdd->next != NULL)
//         {
//            if(atoi(pdd->ID)+atoi(pdd->stockID) == atoi(node->StockID)){
//             printf("Product name : %s \n", pdd->productName);
//             break;
//            }
//            pdd = pdd->next;
//         }
//         printf("Quantity : %d \n", node->Quantity);
//         printf("---------------------------------------------\n");
//         }
//     }
// }
// void add_to_cart(struct ProductSales *ps)
// {
//     char stock_id[50];
//     int quantity;
//     printf("Enter Stock ID of the product to add to cart: ");
//     scanf("%s", stock_id);
//     //remove_newline(stock_id);
//     struct Product *head = ps->products;
//     while (head != NULL)
//     {
//        if(strcmp(stock_id,head->ID) == 0){
//         break;
//        }
//        head = head->next;
//     }
//     if(head->stock <= 0){
//         printf("Out of stock\n");
//         return;
//     }else if(head == NULL){
//         printf("Product not found.\n");
//         return;
//     }else{
//         printf("product name : %s\n",head->productName);
//         printf("Enter quantity to add: ");
//         scanf("%d", &quantity);
//             FILE *file = fopen("csv/addToCart.csv", "a");
//             fprintf(file, "%d,%d,%d\n", ps->current_user->UserID, atoi(head->ID) + atoi(head->stockID), quantity);
//             fclose(file);
//     }
    
// }
void register_user(struct ProductSales *ps) {
    char username[100], password[100];
        printf("Enter new username: ");
        scanf("%s", username);
        //remove_newline(username);
        
    printf("Enter password: ");
    scanf("%s", password);
    //remove_newline(password);
    int ud;
    //struct User *user = createNode_User(username, password, "user", ps->users->UserID);
    //insertNodeUser(&(ps->users), user); // Insert the user node into the user list
    struct User *head = ps->users;
    while (head->next != NULL)
    {
        head = head->next;
        
    }
    FILE *fp = fopen("csv/login.csv", "a");
    if(fp!=NULL){
        printf("%d",head->UserID);
        fprintf(fp, "%d,%s,%s,%s\n", head->UserID+1, username, password,"user");
    }else{
        printf("regist failed");
    }
    fclose(fp);
}
int main()
{
    struct ProductSales app;
    app.current_user->UserID = 2;
     load_data(&app);
    //view_cart(&app);
    register_user(&app);
    //log_activity(&app,"hello","555");
    //add_to_cart(&app);
    // struct Product *head = app.products;
    // while (head != NULL)
    // {
    //     printf("%s\n",head->productName);
    //     head = head->next;
    // }
    //update_product(&app);
     //view_products(&app,"test.csv");
}
