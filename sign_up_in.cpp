#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{

    string name, filename;
    string last4digits;
    long long int ph_number;

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

    fstream file;

    // Attempt to open the file in read mode
    file.open(filename, ios::in);

    if (file.is_open())
    {
        cout << "File found. Reading content:\n";
        string line;

        // Read and display the file's contents
        while (getline(file, line))
        {
            cout << line << "\n";
        }
        file.close();
    }
    else
    {
        // File does not exist; create a new file
        file.open(filename, ios::out); // Open in write mode

        if (file.is_open())
        {
            cout << "File not found. Creating a new file: " << filename << "\n";
            cout << "Enter some content to save in the file: ";
            cin.ignore(); // To clear the input buffer
            string content;
            getline(cin, content);
            file << content << "\n";
            file.close();
            cout << "File created and content saved.\n";
        }
        else
        {
            cerr << "Error creating the file.\n";
        }
    }

   


    

    return 0;
}
