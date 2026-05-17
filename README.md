# 🛒 Online Cart & Checkout System

A console-based **Online Cart and Checkout System** built in **C++** using core **Data Structures and Algorithms**, organised with **Object-Oriented Programming** principles.

---

## 📌 Project Overview

This project simulates a real-world e-commerce cart and checkout flow entirely in the terminal. A user can browse a product catalog, add and remove items from a shopping cart, checkout with payment processing, and have their order queued for fulfillment — all driven by four fundamental data structures.

---

## 🧱 Data Structures Used

| Data Structure | Class | Why It Was Chosen |
|---|---|---|
| **HashMap** (`unordered_map`) | `ProductCatalog` | O(1) average-case product lookup by ID — instant regardless of catalog size |
| **Linked List** (manual) | `ShoppingCart` | O(1) insert at head; efficient removal by pointer unlinking without shifting elements |
| **Queue** (`std::queue`) | `OrderQueue` | FIFO ensures orders are processed in the exact order they are placed |
| **Stack** (`std::stack`) | `PaymentProcessor` | LIFO allows payment steps to be rolled back in reverse order on failure |

---

## 🗂️ Class Structure

```
CheckoutSystem             ← Facade / main controller (owns all classes below)
├── ProductCatalog         ← HashMap  (unordered_map<string, Product>)
├── ShoppingCart           ← Singly Linked List
│     └── CartItem         ← Linked List node (productId · qty · next*)
├── OrderQueue             ← FIFO Queue
│     └── Order            ← Order data object
└── PaymentProcessor       ← LIFO Stack
```

### OOP Principles Applied

- **Encapsulation** — all class data is `private`; accessed only through public methods
- **Single Responsibility** — each class has one clearly defined job
- **Composition (HAS-A)** — `CheckoutSystem` owns the other classes as member variables
- **Facade Pattern** — `main.cpp` only interacts with `CheckoutSystem`; all internal complexity is hidden

---

## 📁 File Structure

```
cart_project/
├── Product.h              # Product class — data + stock management
├── ProductCatalog.h       # HashMap-based catalog — add, find, display
├── ShoppingCart.h         # Linked List cart — add, remove, update, total
├── OrderQueue.h           # FIFO order queue + Order data class
├── PaymentProcessor.h     # Stack-based payment steps + rollback
├── CheckoutSystem.h       # Facade — coordinates all classes
└── main.cpp               # Entry point — uses only CheckoutSystem
```

---

## ⚙️ How to Compile and Run

### Requirements
- A C++17 compatible compiler (g++ recommended)

### Compile
```bash
g++ -std=c++17 -o cart_system main.cpp
```

### Run
```bash
# Linux / Mac
./cart_system

# Windows
cart_system.exe
```

---

## 🔄 System Flow

```
1. Load Catalog    →  Products added to HashMap
2. Add to Cart     →  CartItem node inserted at head of Linked List
3. Remove from Cart→  Node found via traversal, unlinked, deleted
4. Checkout        →  Payment steps pushed onto Stack
5. Order Queued    →  Order object enqueued into FIFO Queue
6. Process Orders  →  Orders dequeued and fulfilled in arrival order
```

---

## 🔑 Key Algorithm — removeItem() (Linked List)

The most important algorithm in the project. Uses two pointers to traverse and unlink a node without breaking the chain.

```
BEFORE:  head → [Laptop] → [Keyboard] → [Mouse] → nullptr
                              ↑ prev       ↑ current (target)

Step 1 — traverse: prev trails one step behind current
Step 2 — unlink:   prev->next = current->next
Step 3 — free:     delete current;  count--;

AFTER:   head → [Laptop] → [Keyboard] → nullptr
```

```cpp
// Core unlinking logic
if (prev == nullptr)
    head = current->getNext();       // removing the head node
else
    prev->setNext(current->getNext()); // removing middle or tail node

delete current;
count--;
```

---

## 🧪 Edge Cases Handled

| Scenario | Behaviour |
|---|---|
| Checkout with empty cart | Error message — operation aborted |
| Add item with invalid product ID | `findProduct()` returns `nullptr` — error shown |
| Add quantity greater than stock | `isAvailable()` check fails — error shown |
| Remove item not in cart | `findNode()` returns `{null, null}` — error shown |
| Add same item twice | Quantity updated in-place — no duplicate node created |

---

## 📈 Time Complexity Summary

| Operation | Data Structure | Complexity |
|---|---|---|
| Find product by ID | HashMap | O(1) avg |
| Add item to cart | Linked List | O(n) (duplicate check) |
| Remove item from cart | Linked List | O(n) (traversal) |
| Place order | Queue | O(1) |
| Process next order | Queue | O(1) |
| Record payment step | Stack | O(1) |
| Rollback payment step | Stack | O(1) |

---

## 🚀 Possible Extensions

- **Doubly Linked List** for the cart — enables O(1) removal when a node pointer is known
- **User class** with login and individual cart per user
- **File I/O** to persist the product catalog and order history across runs
- **Priority Queue** to process premium orders ahead of standard ones
- **Search by name** using linear search or a sorted structure for binary search

---

## 🛠️ Built With

- **Language** — C++17
- **IDE** — VS Code with C/C++ extension
- **Compiler** — g++ (GCC)

---

## 👤 Author

**Tharindu**
- GitHub: https://github.com/fonsekatdf
