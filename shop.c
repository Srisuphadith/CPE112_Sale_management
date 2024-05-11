// shop (การแสดงข้อมูล)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"
#include "Manage_Stock_func.c"

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
        printf("%d %s", choice, category);
    }

    printf("-1 : Go backward\n");
    printf("What Category you want:\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1 /*cat 1*/:
        /* code find that category product*/
        break;

    case 2 /*cat 2*/:

        break;

    default:
        printf("Please Enter Number Between 1-10");
    }

    printf("Enter Product ID");
}

int main()
{
}