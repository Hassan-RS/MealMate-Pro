#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    fstream File;
    File.open("Fastfood_menu.txt", ios::in | ios ::out | ios::app);

    if (!File)
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

    return 0;
}
