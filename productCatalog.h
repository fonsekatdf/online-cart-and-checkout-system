#ifndef PRODUCT_CATALOG_H
#define PRODUCT_CATALOG_H
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include "product.h"

using namespace std;

class ProductCatalog
{
private:
    unordered_map<string, Product> catalog;

public:
    // add a product to the catalog
    void addProduct(string id, string name, double price, int stock)
    {
        if (catalog.count(id) > 0)
        {
            cout << "[Catalog] Product ID '" << id << "' already exists.\n";
            return;
        }

        Product newProduct(id, name, price, stock);
        catalog[id] = newProduct;

        cout << "[Catalog] Added : " << name << "\n";
    }

    // find a product by ID
    Product *findProduct(string id)
    {
        auto it = catalog.find(id);

        if (it != catalog.end())
        {
            return &(it->second);
        }

        return nullptr;
    }

    // check if a product exists
    bool exists(string id) const
    {
        return catalog.count(id) > 0;
    }

    // display full catalog
    void display()
    {
        cout << "\n========== PRODUCT CATALOG ==================\n";

        cout << left;
        cout << setw(8) << "ID";
        cout << setw(20) << "Name";
        cout << setw(10) << "Price";
        cout << "Stock" << endl;

        cout << "-----------------------------------------------\n";

        for (auto entry : catalog)
        {
            entry.second.display();
        }

        cout << "===============================================\n";
    }

    int size() const
    {
        return catalog.size();
    }
};

#endif
