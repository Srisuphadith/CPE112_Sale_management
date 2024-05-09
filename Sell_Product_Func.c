//การขายสินค้า (ตะกร้าสินค้า จ่ายเงิน ใบเสร็จ)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"

// Function prototypes
void displayMenu();
void addToCart(AVL_Tree **root, char ID[], int quantity);
void displayCart(AVL_Tree *root);
void displayCartHelper(AVL_Tree *node);
float calculateTotal(AVL_Tree *root);
void calculateTotalHelper(AVL_Tree *node, float *total);
void pay(float total);
void printReceipt(AVL_Tree *root, float total);

int main() {
    AVL_Tree *root = NULL; // Initialize the binary search tree

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                // Add product to cart
                char ID[6];
                int quantity;
                printf("Enter product ID and quantity: ");
                scanf("%s %d", ID, &quantity);
                addToCart(&root, ID, quantity);
                break;
            case 2:
                // View cart
                displayCart(root);
                break;
            case 3:
                // Pay
                if (root == NULL) {
                    printf("Your cart is empty.\n");
                } else {
                    float total = calculateTotal(root);
                    pay(total);
                    printReceipt(root, total);
                    root = NULL; // Reset cart after payment
                }
                break;
            case 4:
                // Exit
                printf("Thank you for shopping with us!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Display the main menu
void displayMenu() {
    printf("\n==== Main Menu ====\n");
    printf("1. Add product to cart\n");
    printf("2. View cart\n");
    printf("3. Pay\n");
    printf("4. Exit\n");
}

// Add a product to the cart
void addToCart(AVL_Tree **root, char ID[], int quantity) {

}

// Display the contents of the cart
void displayCart(AVL_Tree *root) {
    if (root == NULL) {
        printf("Your cart is empty.\n");
    } else {
        printf("Cart Contents:\n");
        printf("---------------\n");
        displayCartHelper(root);
    }
}

// Helper function to recursively display the products in the cart
void displayCartHelper(AVL_Tree *node) {

}

// Calculate the total price of items in the cart
float calculateTotal(AVL_Tree *root) {
    float total = 0.0;
    calculateTotalHelper(root, &total);
    return total;
}

// Helper function to recursively calculate the total price
void calculateTotalHelper(AVL_Tree *node, float *total) {

}

// Simulate payment
void pay(float total) {
    printf("Total amount to pay: $%.2f\n", total);
    printf("Payment successful. Thank you!\n");
}

// Print the receipt
void printReceipt(AVL_Tree *root, float total) {
    printf("Receipt:\n");
    printf("---------------\n");
    displayCartHelper(root);
    printf("Total amount: $%.2f\n", total);
    printf("Thank you for your purchase!\n");
}