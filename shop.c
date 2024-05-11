// shop (การแสดงข้อมูล)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"
#include "Manage_Stock_Func.c"

// search เพื่อหาของนั้นเลย คือการ search

// shop คือการเข้ามาดูของ ให้เลือกคือ ฮิต หรือ การเลือกประเภทเอง
// ถ้าเลือกประเภทและแสดงของในประเภท เมื่อหมดก็แสดงประเภทใกล้เคียง

void searchProduct(struct AVL_Tree *node, char *category)
{
    if (node == NULL)
    {
        return;
    }

    reverse_inOrder(node->right);
    if (strcmp(node->category, category) == 0)
    {
        displayNode(node);
    }
    reverse_inOrder(node->left);
}

void shop(struct AVL_Tree *node, char *file)
{
    int choice, userChoice,i=0;
    char category[50] , switchCat[10][50];
    FILE *allCategories = fopen(file, "r");

    if (allCategories == NULL)
        printf("Error! opening file");


    printf("Categories\n");
    while (fscanf(allCategories, "%d %c", &choice, category) != EOF)
    {
        strcpy(switchCat[i++], category);
        printf("%d %s\n", choice, category);
    }

    printf("-1 : Go backward\n");
    printf("What Category you want:\n");
    scanf("%d", &choice);

    if(choice > 0 && choice < i){
        filter_from_cat(node , switchCat[i]);
    }else{
        printf("please enter number between 0 to %d or -1 to exit \n", i);
    }

}

void buying_from_id(struct AVL_Tree *node , char *file){

}

int main()
{
}