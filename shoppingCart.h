#include <iostream>
#include <vector>
#include <iomanip>
#include "Product.h"
#include "productCatalog.h"

using namespace std;

class CartItem
{
private:
    string productId;
    int quantity;
    CartItem *next;

public:
    CartItem(string id, int qty)
    {
        productId = id;
        quantity = qty;
        next = nullptr;
    }

    // getters
    string getProductId() const
    {
        return productId;
    }

    int getQuantity() const
    {
        return quantity;
    }

    CartItem *getNext() const
    {
        return next;
    }

    // setters
    void setNext(CartItem *n)
    {
        next = n;
    }

    void setQuantity(int qty)
    {
        quantity = qty;
    }

    void increaseQuantity(int qty)
    {
        quantity += qty;
    }
};

class ShoppingCart
{
private:
    CartItem *head; // pointer to the first node
    int count;      // number of items in the cart

    pair<CartItem *, CartItem *> findNode(string productId)
    {
        CartItem *prev = nullptr;
        CartItem *current = head;

        while (current != nullptr)
        {
            if (current->getProductId() == productId)
            {
                return make_pair(prev, current);
            }

            prev = current;
            current = current->getNext();
        }

        return make_pair(nullptr, nullptr);
    }

public:
    // constructor
    ShoppingCart()
    {
        head = nullptr;
        count = 0;
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    void clear()
    {
        while (head != nullptr)
        {
            CartItem *temp = head;
            head = head->getNext();
            delete temp;
        }
        count = 0;
    }

    // destructor
    ~ShoppingCart()
    {
        clear();
    }

    // add item to cart
    void addItem(string productId, int qty, ProductCatalog &catalog)
    {
        // check if product exists in catalog
        Product *product = catalog.findProduct(productId);

        if (product == nullptr)
        {
            cout << "[Cart] Error : Product '" << productId << "' not found.\n";
            return;
        }

        // check id enough stock is available
        if (!product->isAvailable(qty))
        {
            cout << "[Cart] Error : Not enough stock for '" << product->getName() << "'. Available : " << product->getStock() << "\n";
            return;
        }

        // check if item already in cart
        pair<CartItem *, CartItem *> result = findNode(productId);
        CartItem *existing = result.second;

        if (existing != nullptr)
        {
            existing->increaseQuantity(qty);

            cout << "[Cart] '" << product->getName() << "' quantity updated to" << existing->getQuantity() << ".\\n";

            return;
        }

        // add new item at beginning (head)
        CartItem *newItem = new CartItem(productId, qty);

        newItem->setNext(head);
        head = newItem;
        count++;

        cout << "[Cart] Added '" << product->getName() << "' x" << qty << ".\\n";
    }

    // remove item from cart
    bool removeItem(string productId, ProductCatalog &catalog)
    {
        pair<CartItem *, CartItem *> result = findNode(productId);
        CartItem *prev = result.first;
        CartItem *current = result.second;

        if (!current)
        {
            cout << "[Cart] '" << productId << "' is not in your cart.\n";
            return false;
        }

        if (prev == nullptr)
        {
            head = current->getNext();
        }
        else
        {
            prev->setNext(current->getNext());
        }

        Product *p = catalog.findProduct(productId);
        string name = p ? p->getName() : productId;

        delete current;
        count--;

        cout << "[Cart] Removed '" << name << "' from cart.\n";
        return true;
    }

    // update quantity of an existing item
    bool updateQty(string productId, int newQty, ProductCatalog &catalog)
    {
        if (newQty <= 0)
        {
            return removeItem(productId, catalog);
        }

        Product *p = catalog.findProduct(productId);

        if (!p || !p->isAvailable(newQty))
        {
            cout << "[Cart] Cannot update : insufficient stock.\n";
            return false;
        }

        pair<CartItem *, CartItem *> result = findNode(productId);
        CartItem *prev = result.first;
        CartItem *current = result.second;

        if (current == nullptr)
        {
            cout << "[Cart] Product not found in cart.\n";
            return false;
        }

        current->setQuantity(newQty);
        cout << "[Cart] '" << p->getName() << "' quantity updated to " << newQty << ".\n";
        return true;
    }

    // display cart contents
    void display(ProductCatalog &catalog) const
    {
        if (isEmpty())
        {
            cout << "\n[Cart] Your cart is empty.\n";
            return;
        }

        cout << "\n========== YOUR SHOPPING CART ==========\n";
        cout << left;
        cout << setw(20) << "Product";
        cout << setw(8) << "Qty";
        cout << setw(12) << "Unit Price";
        cout << "Subtotal\n";
        cout << "---------------------------------------\n";

        CartItem *current = head;
        double total = 0;

        while (current != nullptr)
        {
            Product *p = catalog.findProduct(current->getProductId());

            if (p)
            {
                double subtotal = p->getPrice() * current->getQuantity();
                total += subtotal;

                cout << left;
                cout << setw(20) << p->getName();
                cout << setw(8) << current->getQuantity();
                cout << "Rs. " << setw(11) << fixed << setprecision(2) << p->getPrice();
                cout << "Rs. " << fixed << setprecision(2) << subtotal << "\n";
            }
            current = current->getNext();
        }

        cout << "---------------------------------------\n";
        cout << right << setw(43) << "TOTAL : Rs. " << fixed << setprecision(2) << total << "\n";
        cout << "=======================================\n";
    }

    // calculate total price of items in cart
    double calcTotal(ProductCatalog &catalog) const
    {
        double total = 0;
        CartItem *current = head;

        while (current != nullptr)
        {
            Product *p = catalog.findProduct(current->getProductId());

            if (p)
            {
                total += p->getPrice() * current->getQuantity();
            }
            current = current->getNext();
        }

        return total;
    }

    // snapshot of cart items for checkout processing
    vector<pair<string, int>> getItems() const
    {
        vector<pair<string, int>> items;
        CartItem *current = head;

        while (current != nullptr)
        {
            items.push_back({current->getProductId(), current->getQuantity()});
            current = current->getNext();
        }
        return items;
    }

    // utility
    bool isEmpty() const
    {
        return head == nullptr;
    }

    int getCount() const
    {
        return count;
    }

    // delete all nodes
    void clear()
    {
        while (head != nullptr)
        {
            CartItem *temp = head;
            head = head->getNext();
            delete temp;
        }
        count = 0;
    }
};