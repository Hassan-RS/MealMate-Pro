#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_ITEMS = 100;
const int ADMIN_PASS = 221224;

// Helper functions
int stringToInt(const string &str) {
    return stoi(str);
}

double stringToFloat(const string &str) {
    return stod(str);
}

// Bubble sort function (iterative version)
void bubblesort(double arr[], int s) {
    for (int i = 0; i < s - 1; i++) {
        for (int j = 0; j < s - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Recommendation function
void recommendation(int &type, const string &filename) {
    string line;
    fstream file;
    int count = 0;
    int serialNumbers[MAX_ITEMS];
    string foodNames[MAX_ITEMS];
    double prices[MAX_ITEMS];
    int calories[MAX_ITEMS];

    // Reading menu files
    string menuFiles[] = {"Desi_menu.txt", "Fastfood_menu.txt"};
    for (const string &menuFile : menuFiles) {
        file.open(menuFile, ios::in);
        if (!file) {
            cout << "Error: Could not open " << menuFile << endl;
            continue;
        }

        while (getline(file, line) && count < MAX_ITEMS) {
            stringstream ss(line);
            string part1, part2, part3, part4;
            getline(ss, part1, '-');
            getline(ss, part2, '-');
            getline(ss, part3, '-');
            getline(ss, part4, '-');

            serialNumbers[count] = stringToInt(part1);
            foodNames[count] = part2;
            prices[count] = stringToFloat(part3);
            calories[count] = stringToInt(part4);
            count++;
        }
        file.close();
    }

    if (count == 0) {
        cout << "No items available for recommendation.\n";
        return;
    }

    srand(time(NULL));
    int randnum = rand() % count;

    cout << "Here is a recommended dish:\n";
    cout << "Food Name: " << foodNames[randnum]
         << "\nPrice: Rs " << prices[randnum]
         << "\nCalories: " << calories[randnum] << endl;

    fstream ufile;
    ufile.open(filename, ios::app);
    if (!ufile) {
        cout << "Error: Could not open user file " << filename << endl;
        return;
    }

    char response;
    cout << "Do you want to order this? (y/n): ";
    cin >> response;
    if (response == 'y' || response == 'Y') {
        ufile << "Food Name: " << foodNames[randnum]
              << "\nPrice: Rs " << prices[randnum]
              << "\nCalories: " << calories[randnum] << endl;
        cout << "Order placed successfully.\n";
    } else {
        cout << "Order canceled.\n";
    }

    ufile.close();
}

// Reading user file
void read_user_file(const string &filename, int &type) {
    fstream ufile;
    double totalAmount = 0.0;
    double prices[MAX_ITEMS];
    int count = 0;

    ufile.open(filename, ios::in);
    if (ufile.is_open()) {
        cout << "Reading previous orders:\n";
        string line;
        while (getline(ufile, line)) {
            cout << line << "\n";
            if (line.find("Price: Rs") != string::npos) {
                stringstream ss(line);
                string temp;
                double price;
                ss >> temp >> temp >> price;
                prices[count++] = price;
                totalAmount += price;
            }
        }

        if (count > 0) {
            bubblesort(prices, count);
            cout << "\nTotal Price: Rs " << totalAmount << endl;
            cout << "Smallest Order Value: Rs " << prices[0] << endl;
            cout << "Largest Order Value: Rs " << prices[count - 1] << endl;
        } else {
            cout << "No orders found.\n";
        }
        ufile.close();
    } else {
        cout << "No previous orders found. Creating a new file.\n";
        ufile.open(filename, ios::out);
        ufile.close();
    }

    recommendation(type, filename);
}

// Display menu
void display_menu(int &type, int serialNumbers[], string foodNames[], double prices[], int calories[], int &count) {
    string menu = (type == 1) ? "Desi_menu.txt" : "Fastfood_menu.txt";
    fstream file(menu, ios::in);
    if (!file) {
        cout << "Error: Could not open " << menu << endl;
        return;
    }

    string line;
    count = 0;
    while (getline(file, line) && count < MAX_ITEMS) {
        stringstream ss(line);
        string part1, part2, part3, part4;
        getline(ss, part1, '-');
        getline(ss, part2, '-');
        getline(ss, part3, '-');
        getline(ss, part4, '-');

        serialNumbers[count] = stringToInt(part1);
        foodNames[count] = part2;
        prices[count] = stringToFloat(part3);
        calories[count] = stringToInt(part4);
        count++;
    }

    file.close();

    for (int i = 0; i < count; i++) {
        cout << "ID: " << serialNumbers[i]
             << ", Food Name: " << foodNames[i]
             << ", Price: Rs " << prices[i]
             << ", Calories: " << calories[i] << endl;
    }
}

// Main function
int main() {
    int serialNumbers[MAX_ITEMS];
    string foodNames[MAX_ITEMS];
    double prices[MAX_ITEMS];
    int calories[MAX_ITEMS];
    int count, type;
    string name, filename;
    long long int ph_number;

    cout << "Welcome to MealMate-Pro\n";

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your phone number: ";
    cin >> ph_number;

    string last4digits = to_string(ph_number % 10000);
    filename = name + "_" + last4digits + ".txt";

    cout << "Filename: " << filename << endl;

    read_user_file(filename, type);

    while (type != 3) {
        display_menu(type, serialNumbers, foodNames, prices, calories, count);
        cout << "Enter 3 to exit or 1 for Desi Menu, 2 for Fast Food: ";
        cin >> type;
    }

    cout << "Thank you for using MealMate-Pro.\n";
    return 0;
}