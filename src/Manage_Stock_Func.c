#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.c"
#include <time.h>

struct Node_LL_Key* head = NULL;
struct AVL_Tree *root = NULL;

// ฟังก์ชันสำหรับสร้างโหนดใหม่ใน linked list
struct Node_LL_Key* newNode_LL_Key(int key_value, AVL_Tree *node) {
  // Allocate memory and check for failure
  struct Node_LL_Key* newNode_LL_Key = (struct Node_LL_Key*)malloc(sizeof(struct Node_LL_Key));
  if (newNode_LL_Key == NULL) {
    // Handle memory allocation failure (e.g., return NULL or log an error)
    return NULL;
  }
  
  // Assign data and pointers
  newNode_LL_Key->data_key = key_value;
  newNode_LL_Key->node = node;
  newNode_LL_Key->next = NULL;

  return newNode_LL_Key;
}

struct Node_LL_Key* insert(struct Node_LL_Key* head, int key, struct AVL_Tree* node) {
  // สร้างโหนดใหม่
  struct Node_LL_Key* new_node = (struct Node_LL_Key*) malloc(sizeof(struct Node_LL_Key));
  new_node->data_key = key;
  new_node->node = node;

  // กรณี Linked List ว่าง
  if (head == NULL) {
    return new_node;
  }

  // ค้นหาตำแหน่งที่เหมาะสม
  struct Node_LL_Key* prev = NULL;
  struct Node_LL_Key* curr = head;
  // printf("%p %d %d" , curr , curr->data_key , key);
  while (curr != NULL && curr->data_key > key) {
    prev = curr;
    curr = curr->next;
  }

  // แทรกโหนดใหม่
  if (prev == NULL) {
    new_node->next = head;
    return new_node;
  } else {
    new_node->next = curr;
    prev->next = new_node;
    return head;
  }
}

void filter_from_cat(AVL_Tree *node, char category[]) {
  // printf("%p" , node);
  if (node == NULL) {
    return;
  }
  filter_from_cat(node->right, category);
  if (strcmp(node->category, category) == 0) {
    printf("Stock ID: %s |", node->stockID);
    printf("Product Name: %s |", node->productName);
    printf("Price : %d |", node->price);
    printf("\n");
  }
  filter_from_cat(node->left, category);
}

// void shop(AVL_Tree *node, char *file) {
//   int choice[50], userChoice, i = -1;
//   char category_t[50][50], category[50][50];
//   FILE *allCategories = fopen(file, "r");

//   if (allCategories == NULL)
//     printf("Error! opening file");
//   int j = 1;
//   printf("Categories\n");
//   while (fgets(category_t[j], 50, allCategories)) {
//     category_t[j][strcspn(category_t[j], "\n")] = 0;
//     printf("||%s||", category_t[j]);
//     sscanf(category_t[j], "%d,%[^,]", &choice[j], category[j]);
//     // printf("%d : %s" , j , category);
//     j++;
//   }
//   fclose(allCategories);
//   printf("-1 : Go backward\n");
//   printf("What Category you want: ");
//   scanf("%d", &userChoice);
//   if (userChoice > 0 && userChoice < j) {
//     printf("-|%s %p|-", category[userChoice], node);
//     printf("Products in category : \"%s\" \n", category[userChoice]);
//     filter_from_cat(node, category[userChoice]);
//   } else {
//     printf("please enter number between 0 to %d or -1 to exit \n", i);
//   }
// }

// Function to create a new AVL tree node
struct AVL_Tree *createNode(const char *ID, const char *stockID,
                            const char *productName, int price,
                            const char *imports, const char *exports,
                            const char *category, int stock, int access,
                            int addToCart, int buy) {
  int key = atoi(ID)+atoi(stockID);
  struct AVL_Tree *newNode = (struct AVL_Tree *)malloc(sizeof(struct AVL_Tree));
  if (newNode == NULL) {
    printf("Memory allocation failed.\n");
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
  newNode->heightOfTree = 1; // Initialize height
  newNode->key = key;

  newNode->left = NULL;
  newNode->right = NULL;

  // printf(" /////////%p %d \n" , head , key);


  head = insert(head, key, newNode);
  
  
  
  return newNode;
}

// Function to get the height of a node
int height(struct AVL_Tree *node) {
  if (node == NULL) {
    return 0;
  }
  return node->heightOfTree;
}

// Function to calculate the maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// Function to update the height of a node
void updateHeight(struct AVL_Tree *node) {
  node->heightOfTree = 1 + max(height(node->left), height(node->right));
}

// Function to perform a right rotation
struct AVL_Tree *rightRotate(struct AVL_Tree *y) {
  struct AVL_Tree *x = y->left;
  struct AVL_Tree *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  updateHeight(y);
  updateHeight(x);

  return x;
}

// Function to perform a left rotation
struct AVL_Tree *leftRotate(struct AVL_Tree *x) {
  struct AVL_Tree *y = x->right;
  struct AVL_Tree *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights
  updateHeight(x);
  updateHeight(y);

  return y;
}

// Function to balance the AVL tree
struct AVL_Tree *balance(struct AVL_Tree *node) {
  // Update height of current node
  updateHeight(node);

  // Check balance factor
  int balanceFactor = height(node->left) - height(node->right);

  // Left Heavy
  if (balanceFactor > 1) {
    if (height(node->left->left) >= height(node->left->right)) {
      return rightRotate(node);
    } else {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  // Right Heavy
  else if (balanceFactor < -1) {
    if (height(node->right->right) >= height(node->right->left)) {
      return leftRotate(node);
    } else {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }

  // Balanced
  return node;
}

// Function to insert a node into the AVL tree
struct AVL_Tree *insertNodeAVL(struct AVL_Tree *root,
                               struct AVL_Tree *newNode) {
  // Perform standard BST insertion
  if (root == NULL) {
    return newNode;
  }

  if (newNode->key < root->key) {
    root->left = insertNodeAVL(root->left, newNode);
  } else if (newNode->key > root->key) {
    root->right = insertNodeAVL(root->right, newNode);
  } else { // Duplicate keys not allowed
    return root;
  }

  // Update height of current node
  updateHeight(root);

  // Balance the tree
  return balance(root);
}

// Function to delete a node from the AVL tree

struct Node_LL_Key* deleteNode_LL(struct Node_LL_Key* head, int key) {
  // กรณี Linked List ว่าง
  if (head == NULL) {
    return NULL;
  }

  // กรณีโหนดแรกมี `data_key` ตรงกับ `key`
  if (head->data_key == key) {
    struct Node_LL_Key* temp = head;
    head = head->next;
    free(temp);
    return head;
  }

  // ค้นหาโหนดก่อนหน้าโหนดเป้าหมาย
  struct Node_LL_Key* prev = NULL;
  struct Node_LL_Key* curr = head;
  while (curr != NULL && curr->data_key != key) {
    prev = curr;
    curr = curr->next;
  }

  // กรณีไม่พบโหนดเป้าหมาย
  if (curr == NULL) {
    return head;
  }

  // ลบโหนดเป้าหมาย
  prev->next = curr->next;
  free(curr);
  return head;
}

struct AVL_Tree *deleteNodeF(struct AVL_Tree *root, const char *ID,const char *stockID) {
  if (root == NULL) {
    return root;
  }
  int key = atoi(ID)+atoi(stockID);

  head = deleteNode_LL(head, key);
  // Search for the node to be deleted

  if (key < root->key) {
    root->left = deleteNodeF(root->left, ID, stockID);
  } else if (key > root->key) {
    root->right = deleteNodeF(root->right, ID, stockID);
  } else {
    // Node found, delete it
    if (root->left == NULL) {
      struct AVL_Tree *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct AVL_Tree *temp = root->left;
      free(root);
      return temp;
    }
  
    // Node with two children, get the inorder successor (smallest in the right
    // subtree)
    struct AVL_Tree *temp = root->right;
    while (temp->left != NULL) {
      temp = temp->left;
    }

    // Copy the inorder successor's content to this node
    strcpy(root->ID, temp->ID);
    strcpy(root->stockID, temp->stockID);
    strcpy(root->productName, temp->productName);
    root->price = temp->price;
    strcpy(root->imports, temp->imports);
    strcpy(root->exports, temp->exports);
    strcpy(root->category, temp->category);
    root->stock = temp->stock;
    root->access = temp->access;
    root->addToCart = temp->addToCart;
    root->buy = temp->buy;
    // Delete the inorder successor
    root->right = deleteNodeF(root->right, temp->ID, temp->stockID);
  }
  return root;
}

// Function to search for a node by its ID
struct AVL_Tree *searchNode(struct AVL_Tree *root, const char *ID) {
  if (root == NULL || strcmp(root->ID, ID) == 0) {
    return root;
  }

  if (strcmp(ID, root->ID) < 0) {
    return searchNode(root->left, ID);
  } else {
    return searchNode(root->right, ID);
  }
}

struct AVL_Tree *searchNodeByKEY(struct AVL_Tree *root, int key) {
  if  (root->key == key) {
    return root;
  }

  if (root->key < key) {
    return searchNodeByKEY(root->left, key);
  } else {
    return searchNodeByKEY(root->right, key);
  }
}

void print_LL(struct Node_LL_Key* head) {
  struct Node_LL_Key* curr = head;
  while (curr != NULL) {
    printf("%s ", curr->node->productName);
    curr = curr->next;
  }
  printf("\n");
}

void edit_AVL(struct AVL_Tree *node, char ID[], char newCategory[],
              char newStockID[]) {
  while (node != NULL) {
    if (strcmp(node->ID, ID) == 0) {
      strcpy(node->category, newCategory);
      strcpy(node->stockID, newStockID);
      return;
    } else if (strcmp(ID, node->ID) < 0) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  }

// Function to display the details of a node
void displayNode(struct AVL_Tree *node) {
  printf("ID: %s\n", node->ID);
  printf("Stock ID: %s\n", node->stockID);
  printf("Product Name: %s\n", node->productName);
  printf("Price: %d\n", node->price);
  printf("Import: %s\n", node->imports);
  printf("Export: %s\n", node->exports);
  printf("Category: %s\n", node->category);
  printf("Stock: %d\n", node->stock);
  printf("Access: %d\n", node->access);
  printf("Add To Cart: %d\n", node->addToCart);
  printf("Buy: %d\n", node->buy);
  printf("key: %d\n", node->key);

  printf("-------------------\n");
}

void reverse_inOrder(struct AVL_Tree *node) {
  if (node == NULL) {
    return;
  }

  reverse_inOrder(node->right);
  displayNode(node);
  reverse_inOrder(node->left);
  }

void displayTree(struct AVL_Tree *root) {
  if (root == NULL) {
    return;
  }

  displayTree(root->right);
  displayNode(root);
  displayTree(root->left);
}


void edit_stock(struct AVL_Tree *node, int key) {
  int option;
  AVL_Tree *target = searchNodeByKEY(node, key);
  if (target == NULL)
    printf("ไม่พบสินค้าที่ต้องการแก้ไข\n");
  else{
    printf("คุณต้องการแก้ไขข้อมูลใดในสินค้า%s\n",target->productName);
    printf("0. รหัสสินค้า\n");
    printf("1. ชื่อสินค้า   \n");
    printf("2. ราคาสินค้า  \n");
    printf("3. จำนวนสินค้า \n");
    printf("4. วันสินค้าเข้า   \n");
    printf("5. วันสินค้าออก    \n");
    printf("6. หมวดหมู่สินค้า   \n");
    printf("7. สต็อกสินค้า      \n");
    printf("8. back       \n");
    scanf("%d",&option);
    switch(option){
      case 0:
        printf("กรุณากรอกชื่อIDสินค้าใหม่  ");
        scanf("%s",target->ID);
        break;
      case 1:
        printf("กรุณากรอกชื่อสินค้าใหม่  ");
        scanf("%s",target->productName);
        break;
      case 2:
        printf("กรุณากรอกราคาสินค้าใหม่  ");
        scanf("%d",&target->price);
        break;
      case 3:
        printf("กรุณากรอกจำนวนสินค้าใหม่  ");
        scanf("%d",&target->stock);
        break;
      case 4:
        printf("กรุณากรอกวันสินค้าเข้าใหม่  ");
        scanf("%s",target->imports);
        break;
      case 5:
        printf("กรุณากรอกวันสินค้าออกใหม่  ");
        scanf("%s",target->exports);
        break;
      case 6:
        printf("กรุณากรอกประเภทสินค้าใหม่  ");
        scanf("%s",target->category);
        break;
      case 7:
        printf("กรุณากรอกเลขสต็อคใหม่  ");
        scanf("%s",target->stockID);
        break;
      case 8:
        //some function
        break;
      default:
        printf("Invalid option(insert 0-8 )\n");
        break;
    }
    
  }
}

void getCurrentTimeAsString(char *timeString) {
    time_t currentTime;
    struct tm *localTime;

    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    strftime(timeString, 7, "%d%m%y", localTime); // Changed size to 7 and format to %d%m%y
}

int calculateIntDate(int day, int month, int year) {
    int intDate = (year - 19) * 365 + ((year - 19) / 4); 

    switch(month) {
        case 2: intDate += 31; break;
        case 3: intDate += 59; break;
        case 4: intDate += 90; break;
        case 5: intDate += 120; break;
        case 6: intDate += 151; break;
        case 7: intDate += 181; break;
        case 8: intDate += 212; break;
        case 9: intDate += 243; break;
        case 10: intDate += 273; break;
        case 11: intDate += 304; break;
        case 12: intDate += 334; break;
    }

    intDate += day - 1;

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        if (month > 2) {
            intDate += 1;
        }
    }

    return intDate;
}

int calculateDayLeft(struct AVL_Tree *root){
    char dayNow[7]; // เพิ่ม 1 ตำแหน่งเพื่อรองรับ '\0'
    char ID[6];
    char StockID[6];

    int day, month, year, day_Now, month_Now, year_Now;
    
    strcpy(ID,root->ID);
    strcpy(StockID,root->stockID);


    int key = atoi(ID) + atoi(StockID);
    AVL_Tree *target = searchNodeByKEY(root, key);

    // เรียกใช้ฟังก์ชัน getCurrentTimeAsString เพื่อรับวันที่ปัจจุบัน
    getCurrentTimeAsString(dayNow);
    sscanf(dayNow, "%2d%2d%2d", &day_Now, &month_Now, &year_Now);

    // แปลงวันที่ที่ได้รับมาจากโหนดเป้าหมายเป็นรูปแบบ int
    sscanf(target->imports, "%2d%2d%2d", &day, &month, &year);

    // คำนวณค่า int ของวันที่ปัจจุบันและวันที่จากโหนดเป้าหมาย
    int intDate = calculateIntDate(day, month, year);
    int intDate_Now = calculateIntDate(day_Now, month_Now, year_Now);

    // คำนวณวันที่เหลือ
    int daysLeft = intDate - intDate_Now;
    
    // แสดงผลลัพธ์
    return daysLeft;
}


// int main() {
//   // Create an empty AVL tree
//   struct AVL_Tree *root = NULL;

//   char ID[6], stockID[6], productName[50], imports[7], exports[7], category[50];
//   int stock, access, addToCart, buy, price;

//   int number;
//   scanf("%d", &number);
//   for (int i = 0; i < number; i++) {
//     scanf("%s %s %s %d %s %s %s %d %d %d %d", ID, stockID, productName, &price,
//           imports, exports, category, &stock, &access, &addToCart, &buy);
//     root = insertNodeAVL(root, createNode(ID, stockID, productName, price,
//                                           imports, exports, category, stock,
//                                           access, addToCart, buy));
//   }

//   // Show the AVL tree nodes before deletion
//   printf("AVL tree nodes before deletion:\n");
//   reverse_inOrder(root);
//   printf("\n");

//   // Delete a node from the AVL tree (for example, with ID "12345")
//   const char *deleteID = "56849";
//   const char *deletestockID = "00001";
  
//   struct AVL_Tree *deleteNode = searchNode(root, deleteID);
//   if (deleteNode != NULL) {
//     root = deleteNodeF(root, deleteID, deletestockID);
//     printf("Node with ID %s deleted successfully.\n\n", deleteID);
//   } else {
//     printf("Node with ID %s not found.\n\n", deleteID);
//   }

//   // Show the AVL tree nodes after deletion
//   printf("AVL tree nodes after deletion:\n");
//   reverse_inOrder(root);

//   //shop(root, "product.csv");
//   print_LL(head);
//   int key;
//   printf("ID and IDstock to Edit");
//   scanf("\n%s %s",ID,stockID);
//   key = atoi(ID)+atoi(stockID);
//   edit_stock(root,key);
//   return 0;
// }