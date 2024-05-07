#include <stdio.h>
#include <string.h>

typedef struct Binary_Search_Tree{
    char ID[6], stockID[6], imports[7], exports[7];
    int stock, access, addToCart, buy, heightOfTree;
    struct Binary_Search_Tree* left, *right;
} BS_Tree;

typedef struct {
    BS_Tree* products[50];
    int count;
} ShoppingCart;

void addProduct(ShoppingCart *cart, BS_Tree *product) {
    cart->products[cart->count] = product;
    cart->count++;
}

float calculateTotal(ShoppingCart cart) {
    float total = 0;
    for(int i = 0; i < cart.count; i++) {
        total += cart.products[i]->buy;
    }
    return total;
}

void printReceipt(ShoppingCart cart) {
    printf("Receipt:\n");
    for(int i = 0; i < cart.count; i++) {
        printf("Product ID: %s, Stock ID: %s, Price: %d\n", cart.products[i]->ID, cart.products[i]->stockID, cart.products[i]->buy);
    }
    printf("Total: %.2f\n", calculateTotal(cart));
}

int main() {
    ShoppingCart cart;
    cart.count = 0;

    BS_Tree product1;
    strcpy(product1.ID, "P1");
    strcpy(product1.stockID, "S1");
    product1.buy = 10;

    BS_Tree product2;
    strcpy(product2.ID, "P2");
    strcpy(product2.stockID, "S2");
    product2.buy = 20;

    addProduct(&cart, &product1);
    addProduct(&cart, &product2);

    printReceipt(cart);

    return 0;
}