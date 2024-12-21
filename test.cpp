#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_ITEMS = 100;

// Manual string to integer conversion function
int stringToInt(const string &str) {
    int num = 0;
    bool isNegative = false;
    size_t i = 0;

    if (str[i] == '-') {
        isNegative = true;
        i++;
    }

    for (; i < str.length(); i++) {
        if (str[i] < '0' || str[i] > '9') {
            throw invalid_argument("Invalid input string");
        }
        num = num * 10 + (str[i] - '0');
    }

    return isNegative ? -num : num;
}

void bubblesort(double arr[], int s) {
    if (s == 1)
        return;
    for (int j = 0; j < s - 1; j++) {
        if (arr[j] > arr[j + 1]) {
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

    File.open("Desi_menu.txt", ios::in);

    File.seekg(0);
    while (getline(File, line) && count < MAX_ITEMS) {
        stringstream ss(line);
        string part1, part2, part3, part4;
        getline(ss, part1, '-');
        getline(ss, part2, '-');
        getline(ss, part3, '-');
        getline(ss, part4, '-');

        serialNumbers[count] = stringToInt(part1);
        foodNames[count] = part2;
        prices[count] = stod(part3);
        calories[count] = stringToInt(part4);
        count++;
    }

    File.close();

    File.open("Fastfood_menu.txt", ios::in);

    File.seekg(0);
    while (getline(File, line) && count < MAX_ITEMS) {
        stringstream ss(line);
        string part1, part2, part3, part4;
        getline(ss, part1, '-');
        getline(ss, part2, '-');
        getline(ss, part3, '-');
        getline(ss, part4, '-');

        serialNumbers[count] = stringToInt(part1);
        foodNames[count] = part2;
        prices[count] = stod(part3);
        calories[count] = stringToInt(part4);
        count++;
    }

    File.close();

    int a, b, n, randnum;
    a = 1;
    b = count;
    n = b - a; // not using -1 as count is already one above the actual number of entries

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

    if (response == 'y' || response == 'Y') {
        ufile << "\nFood Name: " << foodNames[randnum]
              << "\nPrice: Rs " << prices[randnum]
              << "\nCalories: " << calories[randnum] << endl;

    response:
        cout << "Do you want to order anything else? (y/n)" << endl;
        cin >> response;

        if (response == 'y' || response == 'Y') {
            return;
        } else if (response == 'n' || response == 'N') {
            type = 3;
        } else {
            cout << "Invalid input! " << endl;
            goto response;
        }
    } else if (response == 'n' || response == 'N') {
        return;
    } else {
        cout << "Invalid input! " << endl;
        goto choice;
    }

    ufile.close();
}

void update_price(string menu, int itemSrNo, float newPrice) {
    fstream file;
    file.open(menu, ios::in);

    if (!file) {
        cout << "Error: Could not open the menu file!" << endl;
        return;
    }

    string line;
    string tempFileContent;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string part1, part2, part3, part4;

        // Parse the line into its components
        getline(ss, part1, '-'); // Serial number
        getline(ss, part2, '-'); // Name
        getline(ss, part3, '-'); // Price
        getline(ss, part4, '-'); // Calories

        if (stringToInt(part1) == itemSrNo) {
            found = true;
            part3 = to_string(newPrice); // Update the price
        }

        // Reconstruct the updated line
        tempFileContent += part1 + "." + part2 + "." + part3 + "." + part4 + "\n";
    }

    file.close();

    if (!found) {
        cout << "Error: Menu item with SrNo " << itemSrNo << " not found!" << endl;
        return;
    }

    // Write the updated content back to the file
    ofstream outFile(menu, ios::trunc); // Open file in truncate mode to clear content
    if (outFile.is_open()) {
        outFile << tempFileContent;
        outFile.close();
        cout << "Price updated successfully for Menu Item SrNo: " << itemSrNo << endl;
    } else {
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
    long long int ph_number;
    const int MAX_ITEMS = 100;
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
    const int adminpass = 221224;

    cout << "Welcome to MealMate-Pro" << endl;

    role:
    cout << "Do you want to login as admin(1) or user(2)? " << endl;
    cin >> role;
    cin.ignore();
    if (role == 1)
    {
        cout << "Enter password: " << endl;
        cin >> password;
        if (password == adminpass)
        {
        response:
            cout << "Do you want to update price? (y/n) " << endl;
            cin >> response;
            if (response == 'y' || response == 'Y')
            {
            choice:
                cout << "Which menu do you want to update? \nDesi(1) or Fastfood(2) " << endl;
                cin >> choice;

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
                menufile.open(menu, ios::in);
                while (getline(menufile, line))
                {
                    cout << line << endl;
                }
                menufile.close();

                cout << "Enter the ID for which you want to update price: " << endl;
                cin >> itemSrNo;
                cout << "Enter new price: " << endl;
                cin >> newPrice;
                update_price(menu, itemSrNo, newPrice);
            }
            else if (response == 'n' || response == 'N')
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
    else if (role == 2)
    {
        cout << "Enter your name: " << endl;
        getline(cin, name);

        cout << "Enter your phone number: " << endl;
        cin >> ph_number;
        cin.ignore();

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
                display_menu(type, serialNumbers, foodNames, prices, calories, count);

                if (type != 3)
                {
                    place_order(foodNames, prices, calories, type, filename, count);
                }
            } while (type != 3);
        }
    }
    else
    {
        cout << "Invalid Input! " << endl;
        goto role;
    }
    return 0;
}
