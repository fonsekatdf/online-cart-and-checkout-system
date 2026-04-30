#include <iostream>
#include <string>

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
    Product() : id(""), name(""), price(0.0), stock(0) {}

    Product(const string &id, const string &name, double price, int stock)
        : id(id), name(name), price(price), stock(stock) {}

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
        cout << "Product ID : " << id << endl;
        cout << "Product Name : " << name << endl;
        cout << "Price : Rs. " << price << endl;
        cout << "Stock : " << stock << endl;
    }
};