#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include <stack>
#include <iomanip>

struct Product {
    std::string name;
    double price;
    Product* next; 
    Product* left; 
    Product* right; 

    Product(std::string n, double p) : name(n), price(p), next(NULL), left(NULL), right(NULL) {}
};

class Inventory {
private:
    Product* head;
    Product* root; 
    std::stack<Product*> deletedProducts; 


    Product* insertBST(Product* node, Product* newProduct);
    Product* searchBST(Product* node, const std::string& name);
    void clearBST(Product* node);

public:
    Inventory();
    ~Inventory();

    // Core functions
    void addProduct(std::string name, double price);
    void removeProduct(std::string name);
    void permanentlyDelete();
    Product* searchProduct(std::string name);
    void displayInventory();
    void displayDeleted();
};

#endif
