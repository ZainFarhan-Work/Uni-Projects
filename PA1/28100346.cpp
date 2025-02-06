#include <iostream>
#include <limits>

using namespace std;

// Structs
struct Inventory
{
    string productType;
    int quantity;
};

// Function Prototypes
int MainMenu();
void PrintMenu();

// Function Used to Add an "Inventory" type variable to an Array
void AddUserQuery(Inventory* array, int &arrayUsed, bool addExisting);

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

    int inventoryUsed = 0;

    Inventory orders[999];
    orders->productType = {""};
    orders->quantity = 0;

    int ordersAmount = 0;

    while (!quit)
    {
        choice = MainMenu();

        switch (choice)
        {
        case 1:
            AddUserQuery(inventory, inventoryUsed, true);
            break;

        case 2:
            AddUserQuery(orders, ordersAmount, false);
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
            DoOrder(orders, ordersAmount, inventory, inventoryUsed);
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


void AddUserQuery(Inventory* array, int &arrayUsed, bool addExisting)
{
    // Check if the Array is Full
    bool full = true;

    for (int i = 0; i < 999; i++)
    {
        if (array[i].productType == "")
        {
            full = false;
        }
    }
    
    if (full)
    {
        cout << "Storage Space is Full" << endl;
        cout << "Entry was Not Stored" << endl;
        return;
    }

    Inventory query = UserQuery();

    if (addExisting)
    {
        for (int i = 0; i < arrayUsed; i++)
        {

            if (query.productType == array[i].productType)
            {
                array[i].quantity += query.quantity;
                return;
            }
            
        }
        
    }
    
    array[arrayUsed] = query;
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

    cout << "Error: Product Not Found" << endl;

}


void DoOrder(Inventory* orders, int &ordersAmount, Inventory* inventory, int &inventoryUsed)
{
    bool productAvalible = false;
    int index;

    for (int i = 0; i < inventoryUsed; i++)
    {
        if (orders[0].productType == inventory[i].productType)
        {
            productAvalible = true;
            index = i;
            break;
        }  
    }

    if (!productAvalible)
    {
        // Implement Failure Message
        cout << "Error: Product Not Found in DataBase" << endl;
        return;
    }
    else if (inventory[index].quantity == 0)
    {
        //  Implement Failure Message
        cout << "Product Out of Stock" << endl;
        cout << "Order Could Not be Processed" << endl;
        return;
    }

    if (orders[0].quantity > inventory[index].quantity)
    {
        // Partial completion

        orders[0].quantity -= inventory[index].quantity;
        inventory[index].quantity = 0;

        for (int i = index; i < inventoryUsed - 1; i++)
        {
            inventory[i] = inventory[i + 1];
        }

        inventory[inventoryUsed].productType = "";
        inventory[inventoryUsed].quantity = 0;
        inventoryUsed--;

        cout << "Earliest Order Partially Completed" << endl;
        cout << orders[0].quantity << " - More Product Required" << endl;
        return;
    }

    inventory[index].quantity -= orders[0].quantity;

    // Moving the Entire Order List Up

    for (int i = 0; i < ordersAmount - 1; i++)
    {
        orders[i] = orders[i + 1];
    }

    orders[ordersAmount].productType = "";
    orders[ordersAmount].quantity = 0;
    ordersAmount--;

    if (inventory[index].quantity == 0)
    {
        for (int i = index; i < inventoryUsed - 1; i++)
        {
            inventory[i] = inventory[i + 1];
        }
    }

    inventory[inventoryUsed].productType = "";
    inventory[inventoryUsed].quantity = 0;
    inventoryUsed--;

    cout << "Earliest Order Completed Successfully" << endl;
    
}


Inventory UserQuery()
{
    Inventory query;
    bool dataStored = false;

    cin.clear();

    // I Don't think I need validation here but just in case.
    do
    {
        cout << "Enter Product Type [CAPS Sensitive and No Spaces]: ";
        
        if (!(cin >> query.productType))
        {
            cout << "Enter A Valid Option" << endl;
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            dataStored = false;
        }
        else
        {
            dataStored = true; 
        }

    } while (!dataStored);

    cin.clear();
    

    do
    {
        cout << "Enter Product Quantity: ";

        if (!(cin >> query.quantity) || query.quantity < 0)
        {
            cout << "Enter A Valid Option" << endl;
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            dataStored = false;
        }
        
    } while (!dataStored || query.quantity < 0);

    return query;
    
}

