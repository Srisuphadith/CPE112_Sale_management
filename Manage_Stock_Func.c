#include <stdio.h>
#include <AVL.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct AVL_Tree*createnode(char ID[6]/*ไอดีสินค้า*/, char stockID[6]/*ไอ่ดีสต็อค*/, char imports[7]/*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, char exports[7]/*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, int stock, int access/*จำนวนการกดดูสินค้านั้นๆ*/ ,int addToCart/*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/ ,int buy/*จำนวนการซื้อ(ครั้ง)*/ ){
    struct AVL_Tree* newnode = (struct AVL_Tree*)malloc(sizeof(struct AVL_Tree));
    strcpy(newnode->ID,ID);
    strcpy(newnode->stockID,stockID);
    strcpy(newnode->imports,imports);
    strcpy(newnode->exports,exports);
    newnode->stock=stock;
    newnode->access=access;
    newnode->addToCart=addToCart;
    newnode->buy=buy;
    newnode->heightOfTree=1;
    newnode->key = access+addToCart+buy;

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

int getBalance(struct AVL_Tree *node){
    if(node==NULL)
        return 0;
    return height(node->left)-height(node->right);
}

struct AVL_Tree *rightRotate(struct AVL_Tree *y){
    struct AVL_Tree *x = y->left;
    struct AVL_Tree *temp = x->left;

    //perform rotation
    x->right = y;
    y->left = temp;

    //updateheight
    y->heightOfTree = maxof(height(y->left),height(y->right))+1;
    x->heightOfTree = maxof(height(x->left),height(x->right))+1;

    return x;
}

struct AVL_Tree *leftRotate(struct AVL_Tree *x){
    struct AVL_Tree *y = x->right;
    struct AVL_Tree *temp = y->left;

    //perform rotation
    y->left = x;
    x->right = temp;

    //updateheight
    x->heightOfTree = maxof(height(x->left),height(x->right))+1;
    y->heightOfTree = maxof(height(y->left),height(y->right))+1;

    return y;
}

//เพิ่มสินค้าใน AVL Tree
// เพิ่ม
// กรอกข้อมูลสินค้า เช่น ชื่อ รหัส
// ุจำนวนสินค้าคงคลัง

struct AVL_Tree *insert_AVL(struct AVL_Tree*node, char ID[6]/*ไอดีสินค้า*/, char stockID[6]/*ไอ่ดีสต็อค*/, char imports[7]/*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, char exports[7]/*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, int stock, int access/*จำนวนการกดดูสินค้านั้นๆ*/ ,int addToCart/*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/ ,int buy/*จำนวนการซื้อ(ครั้ง)*/){
    if(node == NULL)
        return createnode(ID/*ไอดีสินค้า*/, stockID/*ไอ่ดีสต็อค*/, imports/*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, exports/*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, stock, access/*จำนวนการกดดูสินค้านั้นๆ*/ , addToCart/*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/ , buy/*จำนวนการซื้อ(ครั้ง)*/ );

    if((access+addToCart+buy) <= (node->key))
        node->left = insert_AVL(node->left, ID/*ไอดีสินค้า*/, stockID/*ไอ่ดีสต็อค*/, imports/*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, exports/*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, stock, access/*จำนวนการกดดูสินค้านั้นๆ*/ , addToCart/*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/ , buy/*จำนวนการซื้อ(ครั้ง)*/ );
    else if((access+addToCart+buy) > (node->key))
        node->right = insert_AVL(node->right, ID/*ไอดีสินค้า*/, stockID/*ไอ่ดีสต็อค*/, imports/*วันสินค้าเข้า[รูปแบบวันที่ DDMMYY]*/, exports/*วันสินค้าออก[รูปแบบวันที่ DDMMYY]*/, stock, access/*จำนวนการกดดูสินค้านั้นๆ*/ , addToCart/*จำนวนการเพิ่มสินค้านั้นๆลงตระกร้า*/ , buy/*จำนวนการซื้อ(ครั้ง)*/ );
    
    node->heightOfTree = 1+ maxof(height(node->left),height(node->right));

    int balance = getBalance(node);

    //**Balance checking and rotations**
    //Left Left case(LL)
    if(balance > 1 && ((access+addToCart+buy) <= node->left->key))
        return rightRotate(node);

    //Right Right case(RR)
    if(balance < -1 && ((access+addToCart+buy) > node->right->key))
        return leftRotate(node);

    //Left Right case(LR)
    if(balance > 1 && ((access+addToCart+buy) > node->left->key)){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
        

    //Right Left case(RL)
    if(balance < -1 && ((access+addToCart+buy) <= node->right->key)){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
        
    return node;
}


//แก้ไขสินค้าใน BS Tree
// แก้ไขสินค้า
// แก้ไขข้อมูลสินค้า
// เปลี่ยนแปลงจำนวนสินค้า
void edit_AVL(){}

struct AVL_Tree *minValueNode(struct AVL_Tree *node)
{
    struct AVL_Tree *current = node; // Change AVL_tree to AVL_Tree

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

//ลบสินค้าใน BS Tree
struct AVL_Tree *del_AVL(struct AVL_Tree *node,char ID[6] , char stockID[6] , char imports[7] , char exports[7] , int stock, int access , int addToCart , int buy)
{
    if (node==NULL)
    {
        return node;
    }
    
    if (ID < node->ID)
    {
        node->left = del_BS(node->left, ID , stockID , imports , exports, stock, access , addToCart , buy );
    }
    else if (ID > node->ID)
    {
        node->right = del_BS(node->right, ID, stockID, imports, exports, stock, access, addToCart, buy);
    }
    else
    {
        if ((node->left == NULL)||(node->right == NULL))
        {
            struct AVL_Tree *temp = node->left ? node->left: node->right;

            if (temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
            {
                node = temp;
            }
            
            free(temp);
        }
        else
        {
            struct AVL_Tree *tempID = minValueNode(node->right);
            strcpy(node->ID, tempID->ID);
            node->right = del_BS(node->right, tempID->ID, tempID->stockID, tempID->imports, tempID->exports, tempID->stock, tempID->access, tempID->addToCart, tempID->buy);
        }
        
    }
}

//ค้นหาสินค้าใน BS_Tree
// ค้นหาสินค้า
// ค้นหาสินค้าตามชื่อ รายละเอียด หมวดหมู่
// ค้นหาสินค้าตามราคา
// ค้นหาสินค้าตามจำนวนสินค้า
bool search_AVL(struct AVL_Tree *node, char ID[6])
{
    if (node == NULL)
    {
        return false;
    }
    else if (node->ID == ID)
    {
        return true;
    }
}

//กรองสินค้าใน BS_Tree
// กรองสินค้า
// กรองสินค้าตามหมวดหมู่/ราคา/จำนวนสินค้า
void filter_AVL(){}

//Traversal BS_Tree To show suggestion right->root->left
void reverse_inorder(struct AVL_Tree *node) 
{
    if (node == NULL)
    {
        return;
    }

    reverse_inorder(node->right);
    printf("value");
    reverse_inorder(node->left);
    
}
