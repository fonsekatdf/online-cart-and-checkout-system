#ifndef ORDER_QUEUE_H
#define ORDER_QUEUE_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

class Order
{
private:
    static int idCounter;

    int orderId;
    string userId;
    double total;
    string status;
    vector<pair<string, int>> items;

public:
    Order(string userId, double total, vector<pair<string, int>> items)
    {
        this->orderId = ++idCounter;
        this->userId = userId;
        this->total = total;
        this->status = "Pending";
        this->items = items;
    }

    // getters
    int getOrderId() const
    {
        return orderId;
    }

    string getUserId() const
    {
        return userId;
    }

    double getTotal() const
    {
        return total;
    }

    string getStatus() const
    {
        return status;
    }

    vector<pair<string, int>> getItems() const
    {
        return items;
    }

    // update status
    void setStatus(string s)
    {
        status = s;
    }

    // display
    void display() const
    {
        cout << " Order #" << orderId
             << " | user: " << userId
             << " | total: Rs." << fixed << setprecision(2) << total
             << " | Status: " << status << "\n";

        for (const auto &item : items)
        {
            cout << "  - Product: " << item.first
                 << " Qty: " << item.second << "\n";
        }
    }
};

int Order::idCounter = 0;

class OrderQueue
{
private:
    queue<Order> q;

public:
    // place an order into the queue
    void enqueue(const Order &order)
    {
        q.push(order);
        cout << "\n[Queue] Order #" << order.getOrderId()
             << " added to queue for user '" << order.getUserId() << "'.\n";
    }

    // process the next order in line
    bool processNext()
    {
        if (q.empty())
        {
            cout << "[Queue] No pending orders.\n";
            return false;
        }

        Order &o = q.front();
        o.setStatus("Completed");

        cout << "\n[Queue] Processing:\n";
        o.display();
        cout << " [DONE]\n";

        q.pop();
        return true;
    }

    // process all pending orders
    void processAll()
    {
        if (q.empty())
        {
            cout << "[Queue] No orders to process.\n";
            return;
        }

        cout << "\n========== PROCESSING ALL ORDERS ==========\n";

        while (!q.empty())
        {
            processNext();
        }

        cout << "==========================================\n";
    }

    // peek at next order without removing
    void peekNext() const
    {
        if (q.empty())
        {
            cout << "[Queue] Queue is empty.\n";
            return;
        }

        cout << "[Queue] Next order :\n";
        q.front().display();
    }

    bool isEmpty() const
    {
        return q.empty();
    }

    int size() const
    {
        return (int)q.size();
    }
};

#endif