#include <iostream>
#include <limits>

using namespace std;

// Structs
struct Inventory
{
    string productType;
    int quantity;
};

// struct Order
// {
//     string orderType;
//     int amount;
// };

// Funxtion Prototypes
int MainMenu();
void PrintMenu();
void AddProduct(Inventory* inventory, int &inventoryUsed);
void AddOrder(Inventory* orders, int &ordersAmount);
void UpdateProduct(Inventory* inventory);
void UpdateOrder(Inventory* orders);
void DoOrder(Inventory* orders, int &ordersAmount, Inventory* inventory, int &inventoryUsed);
void DoStatusReport(Inventory* orders, int ordersAmount, Inventory* inventory, int inventoryUsed);
Inventory UserQuery();



int main()
{
    bool quit = false;
    int choice = -1;

    Inventory inventory[999];
    inventory->productType = {""};
    inventory->quantity = 0;

    int inventoryUsed = 2;

    Inventory* orders = new Inventory[2];
    orders->productType = {""};
    orders->quantity = 0;

    int ordersAmount = 2;


    while (!quit)
    {
        choice = MainMenu();

        switch (choice)
        {
        case 1:
            AddProduct(inventory, inventoryUsed);
            break;

        case 6:
            DoStatusReport(orders, ordersAmount, inventory, inventoryUsed);
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
    cout << endl;

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


void DoStatusReport(Inventory* orders, int ordersAmount, Inventory* inventory, int inventoryUsed)
{
    cout << "-- Inventory --\n" << endl;

    for (int i = 0; i < inventoryUsed; i++)
    {
        cout << "-> Product Type: " << inventory[i].productType << endl;
        cout << "-> Product Quantity: " << inventory[i].quantity << endl;
        cout << endl;
    }

    cout << endl;

    cout << "-- Orders --\n" << endl;

    for (int i = 0; i < ordersAmount; i++)
    {
        cout << "-> Order Type: " << orders[i].productType << endl;
        cout << "-> Order Amount: " << orders[i].quantity << endl;
        cout << endl;
    }

    cout << endl;

}


void AddProduct(Inventory* inventory, int &inventoryUsed)
{
    // Check if the Array is Full
    bool full = true;

    for (int i = 0; i < inventoryUsed; i++)
    {
        if (inventory[i].productType == "")
        {
            full = false;
        }
    }
    
    if (full)
    {
        // TODO
        return;
    }
    
    inventory[inventoryUsed] = UserQuery();
    inventoryUsed++;
    
}


Inventory UserQuery()
{
    Inventory query;
    bool dataStored = false;

    do
    {
        cout << "Enter Product Type: ";
        
        if (!(cin >> query.productType))
        {
            cout << "Enter A Valid Option" << endl;
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            dataStored = false;
        }
        else dataStored = true;

    } while (!dataStored);
    

    do
    {
        cout << "Enter Product Quantity: ";

        if (!(cin >> query.quantity) || query.quantity < -1)
        {
            cout << "Enter A Valid Option" << endl;
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            dataStored = false;
        }
        
    } while (!dataStored || query.quantity < -1);

    return query;
    
}

