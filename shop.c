// shop (การแสดงข้อมูล)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"

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

void shop(struct AVL_Tree *node)
{

    int choice;
    printf("Categories\n");
    printf("1 : Technology\n");
    printf("2 : Outfit\n");
    printf("3 : SmartPhone\n");
    printf("-1 : Go backward\n");
    printf("What Category you want:\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1 /*tech*/:
        /* code */
        break;

    default:
        break;
    }

    printf("Enter")
}

int main()
{
}