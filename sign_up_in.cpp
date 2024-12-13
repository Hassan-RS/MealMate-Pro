#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{

    // string name, filename;
    // string last4digits;
    // long long int ph_number;

    // cout << "Welcome to MealMate-Pro" << endl;
    // cout << "Enter your name: " << endl;
    // getline(cin, name);

    // cout << "Enter your phone number: " << endl;
    // cin >> ph_number;
    // cin.ignore(); // Clear the input buffer

    // last4digits = to_string(ph_number % 10000);
    // cout << "Last 4 digits of phone number: " << last4digits << endl;

    // filename = name + "_" + last4digits + ".txt";
    // cout << "Filename: " << filename << endl;

    // fstream ufile;

    // // Attempt to open the file in read mode
    // ufile.open(filename, ios::in);

    // if (ufile.is_open())
    // {
    //     cout << "File found. Reading content:\n";
    //     string line;

    //     // Read and display the file's contents
    //     while (getline(ufile, line))
    //     {
    //         cout << line << "\n";
    //     }
    //     ufile.close();
    // }
    // else
    // {
    //     // File does not exist; create a new file
    //     ufile.open(filename, ios::out); // Open in write mode

    //     if (ufile.is_open())
    //     {
    //         cout << "File not found. Creating a new file: " << filename << "\n";
    //         cout << "Enter some content to save in the file: ";
    //         cin.ignore(); // To clear the input buffer
    //         string content;
    //         getline(cin, content);
    //         ufile << content << "\n";
    //         ufile.close();
    //         cout << "File created and content saved.\n";
    //     }
    //     else
    //     {
    //         cerr << "Error creating the file.\n";
    //     }
    // }

    int type;
    cout<<"Do you want to eat desi(1) or fastfood(2): "<<endl;
    cin>>type;

    fstream File;

    if(type==1)
    {
        File.open("Fastfood_menu.txt", ios::in | ios ::out | ios::app);

        if(!File)
        {
            cerr << "Error opening file!" << endl;
            return 1;
        }

        const int MAX_ITEMS = 100;
        int serialNumbers[MAX_ITEMS];
        string foodNames[MAX_ITEMS];
        double prices[MAX_ITEMS];
        int calories[MAX_ITEMS];
        int count = 0;

        string line;
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

        for (int i = 0; i < count; i++)
        {
            cout << "ID: " << serialNumbers[i]
                 << ", Food Name: " << foodNames[i]
                 << ", Price: $" << prices[i]
                 << ", Calories: " << calories[i] << endl;
        }
    }
    else if(type==2)
    {
        File.open("Desi_menu.txt", ios::in | ios ::out | ios::app);

        if(!File)
        {
            cerr << "Error opening file!" << endl;
            return 1;
        }

        const int MAX_ITEMS = 100;
        int serialNumbers[MAX_ITEMS];
        string foodNames[MAX_ITEMS];
        double prices[MAX_ITEMS];
        int calories[MAX_ITEMS];
        int count = 0;

        string line;
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

        for (int i = 0; i < count; i++)
        {
            cout << "ID: " << serialNumbers[i]
                 << ", Food Name: " << foodNames[i]
                 << ", Price: $" << prices[i]
                 << ", Calories: " << calories[i] << endl;
        }
    }
    else
    {
        cout<<"Invalid input"<<endl;
    }


    

    return 0;
}
