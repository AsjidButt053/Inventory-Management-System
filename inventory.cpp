#include "inventory.h"
#include <iostream>
#include <iomanip>
using namespace std;

Inventory::Inventory() : head(NULL), root(NULL) {}

Inventory::~Inventory()
{

    while (head)
    {
        Product *temp = head;
        head = head->next;
        delete temp;
    }

    clearBST(root);

    while (!deletedProducts.empty())
    {
        delete deletedProducts.top();
        deletedProducts.pop();
    }
}

Product *Inventory::insertBST(Product *node, Product *newProduct)
{
    if (node == NULL)
        return newProduct;

    if (newProduct->name < node->name)
        node->left = insertBST(node->left, newProduct);
    else if (newProduct->name > node->name)
        node->right = insertBST(node->right, newProduct);

    return node;
}

Product *Inventory::searchBST(Product *node, const string &name)
{
    if (node == NULL || node->name == name)
        return node;

    if (name < node->name)
        return searchBST(node->left, name);
    else
        return searchBST(node->right, name);
}

void Inventory::clearBST(Product *node)
{
    if (node)
    {
        clearBST(node->left);
        clearBST(node->right);
        delete node;
    }
}

// Core Functions
void Inventory::addProduct(string name, double price)
{
    if (searchBST(root, name) != NULL)
    {
        cout << "\nProduct already exists!\n";
        return;
    }
    Product *newProduct = new Product(name, price);
    newProduct->next = head;
    head = newProduct;
    root = insertBST(root, newProduct);

    cout << "\nProduct added successfully!\n";
}
void Inventory::removeProduct(string name)
{
    Product *product = searchBST(root, name);
    if (product == NULL)
    {
        cout << "\nProduct not found!\n";
        return;
    }
    deletedProducts.push(product);
    if (head == product)
    {
        head = head->next;
    }
    else
    {
        Product *current = head;
        while (current->next != NULL && current->next != product)
        {
            current = current->next;
        }
        if (current->next == product)
        {
            current->next = product->next;
        }
    }

    cout << "\nProduct moved to deleted stack!\n";
}

void Inventory::permanentlyDelete()
{
    if (deletedProducts.empty())
    {
        cout << "\nDeleted products stack is empty!\n";
        return;
    }
    Product *product = deletedProducts.top();
    deletedProducts.pop();
    delete product;
    cout << "\nProduct permanently deleted!\n";
}

Product *Inventory::searchProduct(string name)
{
    return searchBST(root, name);
}

void Inventory::displayInventory()
{
    if (head == NULL)
    {
        cout << "\nInventory is empty!\n";
        return;
    }

    cout << "\nCurrent Inventory:\n";
    cout << left << setw(20) << "Product Name" << setw(10) << "Price" << "\n";
    cout << "------------------------------------\n";

    Product *current = head;
    while (current != NULL)
    {
        cout << left << setw(20) << current->name << "$" << setw(9) << current->price << "\n";
        current = current->next;
    }
}

void Inventory::displayDeleted()
{
    if (deletedProducts.empty())
    {
        cout << "\nNo deleted products!\n";
        return;
    }

    cout << "\nDeleted Products (LIFO order):\n";
    cout << left << setw(20) << "Product Name" << setw(10) << "Price" << "\n";
    cout << "------------------------------------\n";

    stack<Product *> tempStack = deletedProducts;
    while (!tempStack.empty())
    {
        Product *product = tempStack.top();
        tempStack.pop();
        cout << left << setw(20) << product->name << "$" << setw(9) << product->price << "\n";
    }
}
