#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_ITEMS = 100;

void read_user_file(string filename)
{
    fstream ufile;

     ufile.open(filename, ios::in);

    if (ufile.is_open())
    {
        cout << "File found. Reading content:\n";
        string line;

        // Read and display the file's contents
        while (getline(ufile, line))
        {
            cout << line << "\n";
        }
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
}

void display_menu(int &type)
{
    string menu;

    choice:
    int type;
    cout<<"Do you want to eat desi(1) or fastfood(2): \n(3) to exit the program."<<endl;
    cin>>type;

    switch(type)
    {
        case 1:
        menu="Desi_menu.txt";
        break;

        case 2:
        menu="Fastfood_menu.txt";
        break;

        case 3:
        break;

        default:
        cout<<"Invalid input! "
        goto choice;
    }

    int count=1;
    File.open(menu, ios::in);

        if(!File)
        {
            cout << "Error opening file!" << endl;
            return 1;
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
    int choice;
    char response;

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

    read_user_file(filename);

    do
    {
        display_menu(type);  //////to add and start from here
    }while(type!=3);
    

    return 0;
}