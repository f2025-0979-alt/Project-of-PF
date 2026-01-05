#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
using namespace std;
struct item
{
    int id;
    string name;
    int price;
    int quantity;
    string customer;
    int tableNo;
};
void changeColor(int colorCode)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}
void setColor(int foreground, int background)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int colorCode = background * 16 + foreground;
    SetConsoleTextAttribute(hConsole, colorCode);
}
void showMenu(const vector<item> &menu)
{
    cout << "---------------------------------";
    cout << "       Menu       ";
    cout << "---------------------------------" << endl;
    for (int i = 0; i < menu.size(); i++)
    {
        changeColor(0);
        cout << menu[i].id << ". ";
        changeColor(12);
        cout << menu[i].name;
        setColor(10, 0);
        cout << " Rs." << menu[i].price << endl;
    }
    changeColor(0);
    cout << endl;
}

void placeOrder(vector<item> &orders)
{
    item temp;
    char more = 'y';
    cout << " Enter order owner Name :  ";
    cin >> temp.customer;
    cout << "  Enter table Number plz  :";
    cin >> temp.tableNo;
    while (more == 'y' || more == 'Y')
    {

        cout << "Enter Item ID: ";
        cin >> temp.id;

        cout << "Enter Quantity: ";
        cin >> temp.quantity;

        orders.push_back(temp);

        cout << "Add more items? (y/n): ";
        cin >> more;
    }
}

int generateBill(const vector<item> &menu, const vector<item> &orders)
{
    int total = 0;

    // Match ordered item with menu item
    for (int i = 0; i < orders.size(); i++)
    {
        for (int j = 0; j < menu.size(); j++)
        {
            if (orders[i].id == menu[j].id)
            {
                total += menu[j].price * orders[i].quantity;
            }
        }
    }
    return total;
}

void saveOrder(const vector<item> &orders)
{
    ofstream file("orders.txt");

    for (int i = 0; i < orders.size(); i++)
    {
        file << "table number :" << orders[i].tableNo << endl;
        file << "Order owner: " << orders[i].customer << endl;
        file << "Item ID: " << orders[i].id << endl;
        file << " Quantity: " << orders[i].quantity << endl;
    }

    file.close();
}

void searchItem(const vector<item> &menu)
{
    int id;
    cout << "Enter Item ID to search: ";
    cin >> id;

    for (int i = 0; i < menu.size(); i++)
    {
        if (menu[i].id == id)
        {
            cout << "Found: " << menu[i].name
                 << " Rs." << menu[i].price << endl;
            return;
        }
    }
    cout << "Item not found!\n";
}
void sortMenu(vector<item> &menu)
{
    item temp;

    for (int i = 0; i < menu.size(); i++)
    {
        for (int j = i + 1; j < menu.size(); j++)
        {
            if (menu[i].price > menu[j].price)
            {
                temp = menu[i];
                menu[i] = menu[j];
                menu[j] = temp;
            }
        }
    }
    cout << "Menu sorted by price\n";
}

int main()
{
    vector<item> menu = {
        {1, "Chicken Biryani ", 250},
        {2, "Beef Karahi     ", 900},
        {3, "Chicken Handi   ", 850},
        {4, "Dal Makhni      ", 400},
        {5, "Fried Rice      ", 300},
        {6, "Chicken Tikka   ", 350},
        {7, "Beef Biryani    ", 300},
        {8, "Chicken Qorma   ", 750},
        {9, "Vegetable Curry ", 280},
        {10, "Chicken Shawarma   ", 200},
        {11, "Zinger Burger   ", 450},
        {12, "Chicken Pulao   ", 320},
        {13, "Seekh Kebab     ", 180},
        {14, "Naan            ", 30},
        {15, "Raita           ", 50}};

    vector<item>
        orders;
    string arry[3] = {"cash", "Credit Card", "Debit Card"};
    int choice;

    do
    {
        changeColor(12);
        cout << "............................................" << endl;
        setColor(12, 0);
        cout << "\n===== Welcome to 2nd wife Restaurant =====\n";
        setColor(12, 0);
        cout << "............................................" << endl;
        changeColor(7);
        cout << "1. Show Menu" << endl;
        cout << "2. Place Order" << endl;
        cout << "3. Generate Bill" << endl;
        cout << "4. Search Item" << endl;
        cout << "5. Sort Menu by Price" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: " << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            showMenu(menu);
            break;

        case 2:
            placeOrder(orders);
            break;

        case 3:
            if (orders.size() == 0)
            {
                cout << "No order placed yet!" << endl;
            }
            else
            {
                int bill = generateBill(menu, orders);
                cout << "-----------------------------------\n";
                cout << "customer      :" << orders[0].customer << endl;
                cout << "Total bill:Rs. " << bill << endl;
                cout << "-----------------------------------\n";
                cout << "        payment method     \n";
                for (int i = 0; i < 3; i++)
                {
                    cout << i + 1 << " ." << arry[i] << endl;
                }
                saveOrder(orders);
            }
            break;

        case 4:
            searchItem(menu);
            break;

        case 5:
            sortMenu(menu);
            break;

        case 6:
            cout << "Thank you! Visit again for our services.";
            break;

        default:
            cout << "Invalid choice!";
        }

    } while (choice != 6);

    return 0;
}
