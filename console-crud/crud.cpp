#include <iostream>
#include <limits>
#include <string>
using namespace std;

// Functions
int get_listsize(int size);
void get_items(int size, string list[], int item_amount[], double prices[]);
void read_data(int size, string list[], int item_amount[], double prices[]);
void update(int size, string list[], int item_amount[], double prices[]);
void erase(int& size, string list[], int item_amount[], double prices[]);

int main()
{
    // Variables used in menu choice
    const int max_size = 100;
    int size = 0;
    char choice;
    int item_amount[max_size];
    string list[max_size];
    double prices[max_size];
    
    // Welcome message
    cout << "\n| Hello, world!\n\nI'm here to help you make a shopping list,\nand calculate how much money you need\nto pay for all the items.\n\n";
    cout << "I can store the item's name, amount, and price.\n\nReady when you are...\n\n";

    // Menu choices
    do
    {
        cout << "\n| What would you like to do? (pick a number to choose)\n";
        cout << "| (1) create\t(3) update\t(0) exit\n";
        cout << "| (2) read\t(4) delete\n|\n";
        cout << "Your choice: ";
        cin >> choice;

        // Menu tree
        switch(choice)
        {
            case '0':
                // Exit program
                cout << "\n*Exiting...\n";
                return 0;
                break;

            case '1':
                // Create list
                cout << "\n*Creating list...\n";
                size = get_listsize(size);
                get_items(size, list, item_amount, prices);
                break;

            case '2':
                // Read data of list
                if (size == 0) 
                {
                    cout << "The list is empty. Please create a list first.\n";
                } else {
                    cout << "\n*Reading list...\n";
                    read_data(size, list, item_amount, prices);
                }
                break;

            case '3':
                // Update or edit something on list
                if (size == 0) 
                {
                    cout << "The list is empty. Please create a list first.\n";
                } else {
                    cout << "\n*Updating...\n";
                    update(size, list, item_amount, prices);
                }
                break;

            case '4':
                // Delete something on list
                if (size == 0) 
                {
                    cout << "The list is empty. Please create a list first.\n";
                } else {
                    cout << "\n*Deleting...\n";
                    erase(size, list, item_amount, prices);
                }
                break;

            default:
                cout << "Please choose a valid option.\n";
                break;
        }
    } 
    while (choice != '0'); // Repeat choices until exit
    return 0;
}   // End of main scope

// Function: Get size of list
int get_listsize(int size)
{
    do
    {
        cout << "| How many items will be on your list? (Enter an integer from 1-100)\nSize: ";
        cin >> size;

        while (size > 100 || size < 1 || cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid integer between 1 and 100.\nSize: ";
            cin >> size;
        }
        return size;

    } while (cin.fail());
}

// Function: Get items on the list
void get_items(int size, string list[], int item_amount[], double prices[])
{
    for (int i = 0; i < size; i++)
    {
        cin.ignore();
        cout << "\nName of item #" << i + 1 << ": \t";
        getline(cin, list[i]);

        cout << "Amount of items: \t";
        cin >> item_amount[i];
        while (cin.fail() || item_amount[i] < 0) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid positive integer for the amount: ";
            cin >> item_amount[i];
        }

        cout << "Price of item #" << i + 1 << ": \t$";
        cin >> prices[i];
        while (cin.fail() || prices[i] < 0) 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid positive price: ";
            cin >> prices[i];
        }
    }
}

// Function: Display data
void read_data(int size, string list[], int item_amount[], double prices[])
{
    cout << "|\tPrice\t\tAmount\t\tItem\n"; // Header row, labels
    for (int x = 0; x < size; x++)
    {
        // Respectively displays item number, price, amount, and name
        cout << "| " << x + 1 << ")\t$" << prices[x] << "\t\t" << item_amount[x] << "\t\t" << list[x] << endl;
    }

    // Variables to display sum
    int items_sum = 0;
    double prices_sum = 0;

    // Calculation of item and price sum
    for (int y = 0; y < size; y++)
    {
        items_sum += item_amount[y];
        prices_sum += (item_amount[y] * prices[y]);
    }

    // Message display after list display
    cout << "|\nYou have a total of " << items_sum << " item(s), you will need $" << prices_sum << " to buy all items.\n";
}

// Function: Update items
void update(int size, string list[], int item_amount[], double prices[])
{
    // Variables to select what row to update
    int row;
    char update_choice;
    
    // Ask for row to edit
    cout << "| Which row on the list? (give the number only)\nRow: ";
    cin >> row;
    while (row > size || row < 1)
    {
        cout << "Please stay within range.\nRow: ";
        cin >> row;
    }
    
    // Update process
    do
    {
        cout << "\n| What to update? (pick a number to choose)\n";
        cout << "| (1) item\t(3) price\t(0) none, go back\n";
        cout << "| (2) amount\t(4) all\n|\nYour choice: ";
        cin >> update_choice;

        switch(update_choice)
        {
            case '0':
                // Exit process
                break;

            case '1':
                // Edit item only
                cin.ignore();
                cout << "\nItem name #" << row << ": \t";
                getline(cin, list[row-1]);
                break;

            case '2':
                // Edit amount only
                cout << "\nItem amount: \t";
                cin >> item_amount[row-1];
                while (cin.fail() || item_amount[row-1] < 0) 
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a valid positive amount: ";
                    cin >> item_amount[row-1];
                }
                break;

            case '3':
                // Edit price only
                cout << "\nItem price: \t$";
                cin >> prices[row-1];
                while (cin.fail() || prices[row-1] < 0) 
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a valid positive price: ";
                    cin >> prices[row-1];
                }
                break;

            case '4':
                // Edit item, amount, and price
                cin.ignore();
                cout << "\nItem name #" << row << ": \t";
                getline(cin, list[row-1]);

                cout << "Item amount:\t";
                cin >> item_amount[row-1];
                while (cin.fail() || item_amount[row-1] < 0) 
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a valid positive amount: ";
                    cin >> item_amount[row-1];
                }

                cout << "Item price:\t$";
                cin >> prices[row-1];
                while (cin.fail() || prices[row-1] < 0) 
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a valid positive price: ";
                    cin >> prices[row-1];
                }
                break;

            default:
                cout << "Please choose a valid option.\n\n";
                break;
        }
    }
    while(update_choice != '0');
}

// Function: Delete items
void erase(int& size, string list[], int item_amount[], double prices[])
{
    // Variables used in deletion process
    int row;
    char delete_choice;

    // Deletion process
    do
    {
        cout << "| What to delete? (pick a number to choose)\n";
        cout << "| (1) pick row\n| (2) all\n| (0) none, go back\n|\nYour choice: ";
        cin >> delete_choice;

        switch(delete_choice)
        {
            case '0':
                // Exit, go back to menu
                break;

            case '1':
                // Pick a row to delete
                cout << "\nEnter the row you wish to delete\nNumber: ";
                cin >> row;
                while (row > size || row < 1) 
                {
                    cout << "\nPlease stay within range.\nRow: ";
                    cin >> row;
                }

                // Remove values
                for (int r = row - 1; r < size - 1; r++) 
                {
                    list[r] = list[r + 1];
                    item_amount[r] = item_amount[r + 1];
                    prices[r] = prices[r + 1];
                }
                size--; // Decrease array size

                cout << "\n*Row (" << row << ") deleted!\n\n";
                break;

            case '2':
                // Confirm deletion of all rows
                cout << "Are you sure you want to delete all items? (y/n): ";
                cin >> delete_choice;
                if (tolower(delete_choice) == 'y') 
                {
                    size = 0;
                    cout << "\n*List content deleted!\n\n";
                } 
                else 
                {
                    cout << "\n*Deletion canceled.\n\n";
                }
                break;

            default:
                cout << "Please choose a valid option.\n\n";
                break;
        }
    } while(delete_choice != '0');
}