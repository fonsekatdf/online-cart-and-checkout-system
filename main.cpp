#include <iostream>

#include "checkoutSystem.h"

using namespace std;

int main()
{
    // create the system for user Alice
    CheckoutSystem shop("Alice");

    // addProductToCatalog(id, name, price, stock)
    shop.addProductToCatalog("P001", "Laptop", 999.99, 5);
    shop.addProductToCatalog("P002", "Mouse", 29.99, 20);
    shop.addProductToCatalog("P003", "Keyboard", 79.99, 15);
    shop.addProductToCatalog("P004", "Monitor", 349.99, 8);

    shop.showCatalog();

    return 0;
}