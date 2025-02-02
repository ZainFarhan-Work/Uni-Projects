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

// Function Used to Add an "Inventory" type variable to an Array
void AddUserQuery(Inventory* array, int &arrayUsed);

// Function Used to Update an "Inventory" Type Varriable in an Array
void UpdateUserQuery(Inventory* array, int arrayUsed);

void DoOrder(Inventory* orders, int &ordersAmount, Inventory* array, int &arrayUsed);
void DoStatusReport(Inventory* orders, int ordersAmount, Inventory* array, int arrayUsed);
Inventory UserQuery();



int main()
{
    bool quit = false;
    int choice = -1;

    Inventory inventory[999];
    inventory->productType = {""};
    inventory->quantity = 0;

    int inventoryUsed = 2;

    Inventory orders[999];
    orders->productType = {""};
    orders->quantity = 0;

    int ordersAmount = 2;


    while (!quit)
    {
        choice = MainMenu();

        switch (choice)
        {
        case 1:
            AddUserQuery(inventory, inventoryUsed);
            break;

        case 2:
            AddUserQuery(orders, ordersAmount);
            break;

        case 3:
            cout << "Enter Info for Updated Product-" << endl;
            UpdateUserQuery( inventory, inventoryUsed);
            break;

        case 4:
            cout << "Enter Info for Updated Oder-" << endl;
            UpdateUserQuery( orders, ordersAmount);
            break;

        case 5:

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


void AddUserQuery(Inventory* array, int &arrayUsed)
{
    // Check if the Array is Full
    bool full = true;

    for (int i = 0; i < arrayUsed; i++)
    {
        if (array[i].productType == "")
        {
            full = false;
        }
    }
    
    if (full)
    {
        // TODO
        return;
    }
    
    array[arrayUsed] = UserQuery();
    arrayUsed++;
    
}


void UpdateUserQuery(Inventory* array, int arrayUsed)
{
    Inventory query;

    query = UserQuery();

    for (int i = 0; i < arrayUsed; i++)
    {
        if (array[i].productType == query.productType)
        {
            array[i] = query;
            return;
        }
        
    }

    // TODO: Implement Failure Message

}


void DoOrder(Inventory* orders, int &ordersAmount, Inventory* array, int &arrayUsed)
{
    
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

