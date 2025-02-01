#include <iostream>
#include <limits>

using namespace std;

// Structs
struct Inventory
{
    string productType;
    int quantity;
};

struct Order
{
    string orderType;
    int amount;
};

// Funxtion Prototypes
int MainMenu();
void PrintMenu();
void AddProduct(Inventory* inventory, int &inventorySize);
void AddOrder(Order* orders, int &ordersAmount);
void UpdateProduct(Inventory* inventory);
void UpdateOrder(Order* orders);
void DoOrder(Order* orders, int &ordersAmount, Inventory* inventory, int &inventorySize);
void DoStatusReport(Order* orders, int ordersAmount, Inventory* inventory, int inventorySize);
Inventory UserQuery();



int main()
{
    bool quit = false;
    int choice = -1;

    Inventory inventory[100];
    int inventorySize = 2;

    Order orders[100];
    int ordersAmount = 2;


    while (!quit)
    {
        choice = MainMenu();

        switch (choice)
        {
        case 1:
            // TODO
            break;

        case 6:
            DoStatusReport(orders, ordersAmount, inventory, inventorySize);
            break;

        case 7:
            quit = true;
            break;
        
        default:
            break;
        }
    }

    cout << endl;
    cout << "-- GoodBye :) --" << endl;

    return 0;
}


int MainMenu()
{
    int choice;

    PrintMenu();

    do
    {
        cout << "Enter Option [1-7]: ";

        if (!(cin >> choice) || choice < 0 || choice > 7) {
            cout << "Enter A Valid Option" << endl;
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            choice = -1;
        }
        
    } while (choice < 0 || choice > 7);

    return choice;
    
}


void PrintMenu()
{
    cout << "WholeSale Warehouse Inventory System Menu:" << endl;
    cout << "1. Enter a Product" << endl;
    cout << "2. Place an Order" << endl;
    cout << "3. Update Product Type" << endl;
    cout << "4. Update Order Type" << endl;
    cout << "5. Fulfill the Earliest Order" << endl;
    cout << "6. Print Status Report" << endl;
    cout << "7. Exit the Program" << endl;
}


void DoStatusReport(Order* orders, int ordersAmount, Inventory* inventory, int inventorySize)
{
    cout << "-- Inventory --\n" << endl;

    for (int i = 0; i < inventorySize; i++)
    {
        cout << "-> Product Type: " << inventory[i].productType << endl;
        cout << "-> Product Quantity: " << inventory[i].quantity << endl;
        cout << endl;
    }

    cout << endl;

    cout << "-- Orders --\n" << endl;

    for (int i = 0; i < ordersAmount; i++)
    {
        cout << "-> Order Type: " << orders[i].orderType << endl;
        cout << "-> Order Amount: " << orders[i].amount << endl;
        cout << endl;
    }

    cout << endl;

}


void AddProduct(Inventory* inventory, int &inventorySize)
{
    // Check if the Array is Full
    bool full = true;

    for (int i = 0; i < inventorySize; i++)
    {
        if (inventory[i].productType == "<NONE>")
        {
            full = false;
        }
    }
    
    if (full)
    {
        // Realocate Memory
    }

    for (int i = 0; i < inventorySize; i++)
    {
        if (inventory[i].productType == "<NONE>")
        {
            // Add New Product
            break;
        }
    }
    
    

    
}

