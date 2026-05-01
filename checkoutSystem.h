#include <iostream>
#include <string>

#include "productCatalog.h"
#include "shoppingCart.h"
#include "orderQueue.h"
#include "paymentProcessor.h"

using namespace std;

class CheckoutSystem
{
private:
    ProductCatalog catalog;
    ShoppingCart cart;
    OrderQueue orderQueue;
    PaymentProcessor payment;
    string currentUser;

public:
    CheckoutSystem(const string &userId = "giest")
    {
        currentUser = userId;
    }

    // catalog operations
    void addProductToCatalog(string id, string name, double price, int stock)
    {
        catalog.addProduct(id, name, price, stock);
    }

    void showCatalog()
    {
        catalog.display();
    }

    // cart operations
    void addToCart(string productId, int qty)
    {
        cart.addItem(productId, qty, catalog);
    }

    void removeFromCart(string productId)
    {
        cart.removeItem(productId, catalog);
    }

    void updateCartQty(string productId, int newQty)
    {
        cart.updateQty(productId, newQty, catalog);
    }

    void showCart()
    {
        cart.display(catalog);
    }

    void clearCart()
    {
        cart.clear();
        cout << "[Cart] Cart cleared.\n";
    }

    // checkout operation
    bool checkout()
    {
        cout << "\n================================\n";
        cout << "  CHECKOUT - User: " << currentUser << "\n";
        cout << "==================================\n";

        if (cart.isEmpty())
        {
            cout << "[checkout] Your cart is empty!\n";
            return false;
        }

        // show final cart summary
        cart.display(catalog);
        double total = cart.calcTotal(catalog);

        // run payment
        payment.reset();

        if (!payment.processPayment(total))
        {
            cout << "[Checkout] Payment failed. Order cancelled.\n";
            return false;
        }

        auto items = cart.getItems();
        for (const auto &item : items)
        {
            Product *p = catalog.findProduct(item.first);
            if (p)
            {
                p->reduceStock(item.second);
            }
        }

        // create order and push to queue
        Order order(currentUser, total, items);
        ;
        orderQueue.enqueue(order);

        // show payment history
        payment.showSteps();

        // clear the cart
        cart.clear();

        cout << "\n[Checkout] Order placed sucessfully!\n";
        cout << "======================================\n";
        return true;
    }

    // order operations

    void processNextOrder()
    {
        orderQueue.processNext();
    }

    void processAllOrders()
    {
        orderQueue.processAll();
    }

    void peekNextOrders() const
    {
        return orderQueue.peekNext();
    }

    int pendingOrders() const
    {
        return orderQueue.size();
    }

    // user
    void setUser(string userId)
    {
        currentUser = userId;
    }

    string getUser() const
    {
        return currentUser;
    }
};