#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Product
{
private:
    string id;
    string name;
    double price;
    int stock;

public:
    // constructors
    Product()
    {
        id = "";
        name = "";
        price = 0.0;
        stock = 0;
    }

    Product(string id, string name, double price, int stock)
    {
        this->id = id;
        this->name = name;
        this->price = price;
        this->stock = stock;
    }

    // getters
    string getID() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    double getPrice() const
    {
        return price;
    }

    int getStock() const
    {
        return stock;
    }

    // setters
    void setPrice(double p)
    {
        price = p;
    }

    void setStock(int s)
    {
        stock = s;
    }

    // stock management
    bool isAvailable(int quantity) const
    {
        return stock >= quantity;
    }

    bool reduceStock(int quantity)
    {
        if (!isAvailable(quantity))
        {
            return false;
        }
        else
        {
            stock -= quantity;
            return true;
        }
    }

    void restoreStock(int quantity)
    {
        stock += quantity;
    }

    // display product information
    void display() const
    {
        cout << left;
        cout << setw(8) << id;
        cout << setw(20) << name;
        cout << "Rs. " << fixed << setprecision(2) << setw(10) << price;
        cout << stock << endl;
    }
};

#endif