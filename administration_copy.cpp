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

void recommendation(int &type, string filename) {
    string line;
    fstream File;
    int count = 1;
    int serialNumbers[MAX_ITEMS];
    string foodNames[MAX_ITEMS];
    double prices[MAX_ITEMS];
    int calories[MAX_ITEMS];

    // Reading Desi_menu.txt
    File.open("Desi_menu.txt", ios::in);
    if (!File) {
        cout << "Error: Could not open Desi_menu.txt" << endl;
        return;
    }
    while (getline(File, line) && count < MAX_ITEMS) {
        stringstream ss(line);
        string part1, part2, part3, part4;
        getline(ss, part1, '-');
        getline(ss, part2, '-');
        getline(ss, part3, '-');
        getline(ss, part4, '-');

        serialNumbers[count] = stoi(part1);
        foodNames[count] = part2;
        prices[count] = stod(part3);
        calories[count] = stoi(part4);
        count++;
    }
    File.close();

    // Reading Fastfood_menu.txt
    File.open("Fastfood_menu.txt", ios::in);
    if (!File) {
        cout << "Error: Could not open Fastfood_menu.txt" << endl;
        return;
    }
    while (getline(File, line) && count < MAX_ITEMS) {
        stringstream ss(line);
        string part1, part2, part3, part4;
        getline(ss, part1, '-');
        getline(ss, part2, '-');
        getline(ss, part3, '-');
        getline(ss, part4, '-');

        serialNumbers[count] = stoi(part1);
        foodNames[count] = part2;
        prices[count] = stod(part3);
        calories[count] = stoi(part4);
        count++;
    }
    File.close();

    // Generate a random recommendation
    srand(time(NULL));
    int randnum = 1 + rand() % (count - 1); // Random number between 1 and count-1

    cout << "Here is a recommended dish: " << endl;
    cout << "\nFood Name: " << foodNames[randnum]
         << "\nPrice: Rs " << prices[randnum]
         << "\nCalories: " << calories[randnum] << endl;

    // User file handling
    fstream ufile;
    ufile.open(filename, ios::app);
    if (!ufile) {
        cout << "Error: Could not open user file " << filename << endl;
        return;
    }

    // Local flag to handle user choices
    char response;
    char orderMore = 'n';

    do {
        cout << "Do you want to order this? (y/n): " << endl;
        cin >> response;

        if (response == 'y' || response == 'Y') {
            ufile << "\nFood Name: " << foodNames[randnum]
                  << "\nPrice: Rs " << prices[randnum]
                  << "\nCalories: " << calories[randnum] << endl;

            cout << "Do you want to order anything else? (y/n): " << endl;
            cin >> orderMore;

        } else if (response == 'n' || response == 'N') {
            break;
        } else {
            cout << "Invalid input! Please enter y or n." << endl;
        }
    } while (orderMore == 'y' || orderMore == 'Y');

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

        getline(ss, part1, '-');
        getline(ss, part2, '-');
        getline(ss, part3, '-');
        getline(ss, part4, '-');

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

void update_price(string menu, int itemSrNo, float newPrice) 
{
    fstream file;
    file.open(menu, ios::in);

    if (!file) 
    {
        cout << "Error: Could not open the menu file!" << endl;
        return;
    }

    string line;
    string tempFileContent;
    bool found = false;

    while (getline(file, line)) 
    {
        stringstream ss(line);
        string part1, part2, part3, part4;

        // Parse the line into its components
        getline(ss, part1, '-'); // Serial number
        getline(ss, part2, '-'); // Name
        getline(ss, part3, '-'); // Price
        getline(ss, part4, '-'); // Calories

        if (stoi(part1) == itemSrNo) 
        {
            found = true;
            part3 = to_string(newPrice); // Update the price
        }

        // Reconstruct the updated line
        tempFileContent += part1 + "." + part2 + "." + part3 + "." + part4 + "\n";
    }

    file.close();

    if (!found) 
    {
        cout << "Error: Menu item with SrNo " << itemSrNo << " not found!" << endl;
        return;
    }

    // Write the updated content back to the file
    ofstream outFile(menu, ios::trunc); // Open file in truncate mode to clear content
    if (outFile.is_open()) 
    {
        outFile << tempFileContent;
        outFile.close();
        cout << "Price updated successfully for Menu Item SrNo: " << itemSrNo << endl;
    } 
    else 
    {
        cout << "Error: Could not write to the menu file!" << endl;
    }
}


int main()
{
    fstream menufile;
    string line;
    string name;
    string filename;
    string menu;
    string last4digits;
    long int ph_number;
    int serialNumbers[MAX_ITEMS];
    string foodNames[MAX_ITEMS];
    double prices[MAX_ITEMS];
    int calories[MAX_ITEMS];
    int count;
    int choice;
    char response;
    int type;
    int role;
    int password;
    int itemSrNo; 
    float newPrice;
    int const adminpass=221224;

    cout << "Welcome to MealMate-Pro" << endl;

    role:
    cout<<"Do you want to login as admin(1) or user(2)? "<<endl;
    cin>>role;
    cin.ignore();
    if(role==1)
    {
        cout<<"Enter password: "<<endl;
        cin>>password;
        if(password==adminpass)
        {
            response:
            cout<<"Do you want to update price? (y/n) "<<endl;
            cin>>response;
            if(response=='y' || response=='Y')
            {
                choice:
                cout<<"Which menu do you want to update? \nDesi(1) or Fastfood(2) "<<endl;
                cin>>choice;
                
                switch (choice)
                {
                    case 1:
                    menu = "Desi_menu.txt";
                    break;

                    case 2:
                    menu = "Fastfood_menu.txt";
                    break;

                    default:
                    cout << "Invalid input! " << endl;
                    goto choice;
                }
                menufile.open(menu,ios::in);
                while(getline(menufile,line))
                {
                    cout<<line<<endl;
                }
                menufile.close();

                cout<<"Enter the ID for which you want to update price: "<<endl;
                cin>>itemSrNo;
                cout<<"Enter new price: "<<endl;
                cin>>newPrice;
                update_price(menu,itemSrNo,newPrice);
            }
            else if(response=='n' || response=='N')
            {
                return 0;
            }
            else
            {
                cout << "Invalid input! " << endl;
                goto response;
            }
        }
    }
    else if(role==2)
    {
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
    }
    else
    {
        cout<<"Invalid Input! "<<endl;
        goto role;
    }
    return 0;
}