#include "inventory.h"
#include <iostream>
#include <limits>

using namespace std;

void displayMenu()
{
    cout << "\nInventory Management System\n";
    cout << "1. Add Product\n";
    cout << "2. Remove Product\n";
    cout << "3. Permanently Delete from Stack\n";
    cout << "4. Search Product\n";
    cout << "5. Display Inventory\n";
    cout << "6. Display Deleted Products\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    Inventory inventory;
    int choice;
    string name;
    double price;

    do
    {
        displayMenu();
        cin >> choice;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            cout << "\nEnter product name: ";
            getline(cin, name);
            cout << "Enter product price: ";
            cin >> price;
            inventory.addProduct(name, price);
            break;
        }
        case 2:
        {
            cout << "\nEnter product name to remove: ";
            getline(cin, name);
            inventory.removeProduct(name);
            break;
        }
        case 3:
        {
            inventory.permanentlyDelete();
            break;
        }
        case 4:
        {
            cout << "\nEnter product name to search: ";
            getline(cin, name);
            Product *product = inventory.searchProduct(name);
            if (product != NULL)
            {
                cout << "\nProduct Found!\n";
                cout << "Name: " << product->name << "\n";
                cout << "Price: $" << product->price << "\n";
            }
            else
            {
                cout << "\nProduct not found!\n";
            }
            break;
        }
        case 5:
        {
            inventory.displayInventory();
            break;
        }
        case 6:
        {
            inventory.displayDeleted();
            break;
        }
        case 7:
        {
            cout << "\nExiting program...\n";
            break;
        }
        default:
        {
            cout << "\nInvalid choice! Please try again.\n";
        }
        }

        // Pause before clearing screen
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls"); // Clear screen for Windows

    } while (choice != 7);

    return 0;
}
