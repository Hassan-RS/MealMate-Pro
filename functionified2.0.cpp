#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_ITEMS = 100;

void bubblesort(double arr[], int s)
{
    if (s == 1)
        return;
    for (int j = 0; j < s - 1; j++)
    {
        if (arr[j] > arr[j + 1])
        {
            double temp;
            temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
        }
    }
    bubblesort(arr, s - 1);
}

void recommendation(int &type, string filename)
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

void read_user_file(string filename, int &type)
{
    fstream ufile;
    double totalAmount = 0.0;

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
            count++;
        }
        ufile.clear();
        ufile.seekg(0);

        count /= 4;
        double arr[count];
        // cout << "count = " << count;
        int i = 0;

        // Initialize smallest and largest values

        while (getline(ufile, line))
        {
            // Check if the line contains the "Price" keyword
            if (line.find("Price: Rs") != string::npos)
            {
                // Extract the price from the line
                stringstream ss(line);
                string temp, priceStr;
                double price;

                // Skip to the price part (i.e., "Rs 140")
                ss >> temp >> temp >> priceStr;

                // Convert the price string to a double
                price = stod(priceStr); // Convert string to double
                arr[i] = price;

                // Update total amount
                totalAmount += price;

                // Update smallest and largest values

                // Output the stored price
                // cout << "Price stored: " << arr[i] << endl;
                i++;
            }
        }

        // Output the results
        cout << "\nTotal Price: Rs " << totalAmount << endl;
        bubblesort(arr, count);
        cout << "Smallest Order Value = " << arr[0] << endl;
        cout << "Largest Order Value = " << arr[count - 1] << endl
             << endl;
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

    recommendation(type, filename);
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

void place_order(string foodNames[], double prices[], int calories[], int &type, string filename, int &count)
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

    read_user_file(filename, type);

    if (type != 3)
    {
        do
        {
            count = 1;
            display_menu(type, serialNumbers, foodNames, prices, calories, count); //////to add and start from here

            if (type != 3)
            {
                place_order(foodNames, prices, calories, type, filename, count);
            }
        } while (type != 3);
    }

    return 0;
}