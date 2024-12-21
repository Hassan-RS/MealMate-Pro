#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_ITEMS = 100;
void checkout(double &current_Order_Val, double &current_Order_Cal, double price, double cal, double &loyalty_Discount);
void bubblesort(double arr[], int s)
{
    if (s == 1)
        return;
    for (int j = 0; j < s - 1; j++)
    {
        if (arr[j] > arr[j + 1])
        {
            swap(arr[j], arr[j + 1]);
        }
    }
    bubblesort(arr, s - 1);
}

void recommendation(int &type, string filename, double &current_Order_Cal, double &current_Order_Val, double &loyalty_Discount)
{
    string line;
    fstream File;
    int count = 1;
    int serialNumbers[MAX_ITEMS];
    string foodNames[MAX_ITEMS];
    double prices[MAX_ITEMS];
    int calories[MAX_ITEMS];

    File.open("Desi_menu.txt", ios::in);

    File.seekg(0);
    while (getline(File, line) && count < MAX_ITEMS)
    {
        stringstream ss(line);
        string part1, part2, part3, part4;
        getline(ss, part1, '.');
        getline(ss, part2, '.');
        getline(ss, part3, '.');
        getline(ss, part4, '.');

        serialNumbers[count] = stoi(part1);
        foodNames[count] = part2;
        prices[count] = stod(part3);
        calories[count] = stoi(part4);
        count++;
    }

    File.close();

    File.open("Fastfood_menu.txt", ios::in);

    File.seekg(0);
    while (getline(File, line) && count < MAX_ITEMS)
    {
        stringstream ss(line);
        string part1, part2, part3, part4;
        getline(ss, part1, '.');
        getline(ss, part2, '.');
        getline(ss, part3, '.');
        getline(ss, part4, '.');

        serialNumbers[count] = stoi(part1);
        foodNames[count] = part2;
        prices[count] = stod(part3);
        calories[count] = stoi(part4);
        count++;
    }

    File.close();

    int a, b, n, randnum;
    a = 1;
    b = count;
    n = b - a; // not using -1 as count is already one aboove the actual number of entries

    srand(time(NULL));

    randnum = a + rand() % n;

    cout << "Here is a recommended dish: " << endl;

    cout << "\nFood Name: " << foodNames[randnum]
         << "\nPrice: Rs " << prices[randnum]
         << "\nCalories: " << calories[randnum] << endl;

    fstream ufile;

    ufile.open(filename, ios::app);

choice:
    char response;
    cout << "Do you want to order this: (y/n) " << endl;
    cin >> response;

    if (response == 'y' || response == 'Y')
    {
        ufile << "\nFood Name: " << foodNames[randnum]
              << "\nPrice: Rs " << prices[randnum]
              << "\nCalories: " << calories[randnum] << endl;
        checkout(current_Order_Val, current_Order_Cal, prices[randnum], calories[randnum], loyalty_Discount);
    response:
        cout << "Do you want to order anything else? (y/n)" << endl;
        cin >> response;

        if (response == 'y' || response == 'Y')
        {
            return;
        }
        else if (response == 'n' || response == 'N')
        {
            type = 3;
        }
        else
        {
            cout << "Invalid input! " << endl;
            goto response;
        }
    }
    else if (response == 'n' || response == 'N')
    {
        return;
    }
    else
    {
        cout << "Invalid input! " << endl;
        goto choice;
    }

    ufile.close();
}

void read_user_file(string filename, int &type, double &current_Order_Cal, double &current_Order_Val, double &loyalty_Discount)
{
    fstream ufile;
    double totalAmount = 0.0; // Total for the current session
    double grandTotal = 0.0;  // Total across all sessions

    ufile.open(filename, ios::in);

    if (ufile.is_open())
    {
        cout << "File found. Reading content:\n";
        string line;

        // Read and display the file's contents
        int count = 0;
        ufile.clear();
        ufile.seekg(0);
        while (getline(ufile, line))
        {
            cout << line << "\n";

            // Check if the line contains the "Price" keyword
            if (line.find("Price: Rs") != string::npos)
            {
                // Extract the price from the line
                stringstream ss(line);
                string temp, priceStr;
                double price;

                // Skip to the price part (e.g., "Rs 140")
                ss >> temp >> temp >> priceStr;

                // Convert the price string to a double
                price = stod(priceStr);

                // Update the grand total
                grandTotal += price;
            }
            count++;
        }
        ufile.clear();
        ufile.seekg(0);

        count /= 4; // Divide by 4 as each order has 4 lines (Name, Price, Calories, etc.)
        double arr[count];

        int i = 0;

        // Parse prices for the current session
        while (getline(ufile, line))
        {
            if (line.find("Price: Rs") != string::npos)
            {
                stringstream ss(line);
                string temp, priceStr;
                double price;

                ss >> temp >> temp >> priceStr;

                price = stod(priceStr);
                arr[i] = price;
                totalAmount += price; // Add to the current session total
                i++;
            }
        }

        bubblesort(arr, count);
        // cout << "\nSummary of This Session:\n";
        cout << "\nSmallest Order Value in Previous : Rs " << arr[0] << endl;
        cout << "\nLargest Order Value in Session: Rs " << arr[count - 1] << endl;
        if (grandTotal >= 5000)
            loyalty_Discount = 0.05;
        if (grandTotal >= 10000)
            loyalty_Discount = 0.10;
        if (grandTotal >= 15000)
            loyalty_Discount = 0.15;
        if (grandTotal >= 20000)
            loyalty_Discount = 0.20;

        cout << "\nGrand Total of All Previous Orders: Rs " << grandTotal << endl; // Display grand total
        ufile.close();
    }
    else
    {
        // File does not exist; create a new file
        ufile.open(filename, ios::out); // Open in write mode

        if (ufile.is_open())
        {
            cout << "File not found. Creating a new file: " << filename << "\n";
        }
        else
        {
            cerr << "Error creating the file.\n";
        }
    }

    ufile.close();

    recommendation(type, filename, current_Order_Cal, current_Order_Val, loyalty_Discount);
}

void display_menu(int &type, int serialNumbers[], string foodNames[], double prices[], int calories[], int &count)
{
    string menu;
    fstream File;

choice:
    cout << "Do you want to eat desi(1) or fastfood(2): \n(3) to exit the program." << endl;
    cin >> type;

    switch (type)
    {
    case 1:
        menu = "Desi_menu.txt";
        break;

    case 2:
        menu = "Fastfood_menu.txt";
        break;

    case 3:
        return;
        break;

    default:
        cout << "Invalid input! " << endl;
        goto choice;
    }

    File.open(menu, ios::in);

    if (!File)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    File.seekg(0);
    while (getline(File, line) && count < MAX_ITEMS)
    {
        stringstream ss(line);
        string part1, part2, part3, part4;

        getline(ss, part1, '.');
        getline(ss, part2, '.');
        getline(ss, part3, '.');
        getline(ss, part4, '.');

        serialNumbers[count] = stoi(part1);
        foodNames[count] = part2;
        prices[count] = stod(part3);
        calories[count] = stoi(part4);
        count++;
    }

    File.close();

    for (int i = 1; i < count; i++)
    {
        cout << "ID: " << serialNumbers[i]
             << ", Food Name: " << foodNames[i]
             << ", Price: Rs " << prices[i]
             << ", Calories: " << calories[i] << endl;
    }
}

void place_order(string foodNames[], double prices[], int calories[], int &type, string filename, int &count, double &current_Order_Cal, double &current_Order_Val, double &loyalty_Discount)
{
    fstream ufile;

    ufile.open(filename, ios::app);

    int choice;

ID:
    cout << "What do you want to eat (Input ID): " << endl;
    cin >> choice;

    if (choice > count || choice < 1)
    {
        cout << "Invalid ID" << endl;
        goto ID;
    }
    else
    {
        cout << "\nFood Name: " << foodNames[choice]
             << "\nPrice: Rs " << prices[choice]
             << "\nCalories: " << calories[choice] << endl;

    choice:
        char response;
        cout << "Do you want to order this: (y/n) " << endl;
        cin >> response;

        if (response == 'y' || response == 'Y')
        {

            ufile << "\nFood Name: " << foodNames[choice]
                  << "\nPrice: Rs " << prices[choice]
                  << "\nCalories: " << calories[choice] << endl;
            checkout(current_Order_Val, current_Order_Cal, prices[choice], calories[choice], loyalty_Discount);
        response:
            cout << "Do you want to order anything else? (y/n)" << endl;
            cin >> response;

            if (response == 'y' || response == 'Y')
            {
                return;
            }
            else if (response == 'n' || response == 'N')
            {
                type = 3;
            }
            else
            {
                cout << "Invalid input! " << endl;
                goto response;
            }
        }
        else if (response == 'n' || response == 'N')
        {
            return;
        }
        else
        {
            cout << "Invalid input! " << endl;
            goto choice;
        }
    }

    ufile.close();
}
void checkout(double &current_Order_Val, double &current_Order_Cal, double price, double cal, double &loyalty_Discount)
{
    // cout << price << endl;
    // cout << cal << endl;
    current_Order_Cal += cal;
    current_Order_Val += price;
}

int main()
{
    string name, filename;
    string last4digits;
    long long int ph_number;
    const int MAX_ITEMS = 100;
    int serialNumbers[MAX_ITEMS];
    string foodNames[MAX_ITEMS];
    double prices[MAX_ITEMS];
    int calories[MAX_ITEMS];
    int count;
    char response;
    int type;
    double current_Order_Val = 0.0;
    double current_Order_Cal = 0.0;
    double loyalty_Discount = 0.0;

    cout << "Welcome to MealMate-Pro" << endl;
    cout << "Enter your name: " << endl;
    getline(cin, name);

    cout << "Enter your phone number: " << endl;
    cin >> ph_number;
    cin.ignore(); // Clear the input buffer

    last4digits = to_string(ph_number % 10000);
    cout << "Last 4 digits of phone number: " << last4digits << endl;

    filename = name + "_" + last4digits + ".txt";
    cout << "Filename: " << filename << endl;

    read_user_file(filename, type, current_Order_Cal, current_Order_Val, loyalty_Discount);

    if (type != 3)
    {
        do
        {
            count = 1;
            display_menu(type, serialNumbers, foodNames, prices, calories, count); //////to add and start from here

            if (type != 3)
            {
                place_order(foodNames, prices, calories, type, filename, count, current_Order_Cal, current_Order_Val, loyalty_Discount);
            }
        } while (type != 3);
    }
    cout << "\n\nCurrent order calories: " << current_Order_Cal << "\n\n\n";
    if (loyalty_Discount > 0)
    {
        cout << "\nFor being our regular customer, we would like to offer you a loyalty discount of " << loyalty_Discount * 100 << " % Enjoy! :) \n";
        cout << "\nYour total order value after discount = ";
    }
    else
        cout << "\n\nYour total order value = ";
    current_Order_Val = (1 - loyalty_Discount) * current_Order_Val;
    cout << current_Order_Val;
    return 0;
}