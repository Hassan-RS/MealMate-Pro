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
   fstream ufile;
   // Attempt to open the file in read mode
   ufile.open(filename, ios::in | ios::out | ios::app);
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
   ufile.clear();
   back:
   int type;
   cout<<"Do you want to eat desi(1) or fastfood(2): \n(3) to exit the program."<<endl;
   cin>>type;
   int count = 1;
   fstream File;
   if(type==2)
   {
       File.open("Fastfood_menu.txt", ios::in);
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
       for (int i = 1; i < count; i++)
       {
           cout << "ID: " << serialNumbers[i]
<< ", Food Name: " << foodNames[i]
<< ", Price: Rs " << prices[i]
<< ", Calories: " << calories[i] << endl;
       }
   }
   else if(type==1)
   {
       File.open("Desi_menu.txt", ios::in);
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
       for (int i = 1; i < count; i++)
       {
           cout << "ID: " << serialNumbers[i]
<< ", Food Name: " << foodNames[i]
<< ", Price: Rs " << prices[i]
<< ", Calories: " << calories[i] << endl;
       }
   }
   else if(type==3)
   {
       exit();
   }
   else
   {
       cout<<"Invalid input"<<endl;
   }
   cout<<"What do you want to eat (Input ID): "<<endl;
   cin>>choice;
   cout  << "\nFood Name: " << foodNames[choice]
<< "\nPrice: Rs " << prices[choice]
<< "\nCalories: " << calories[choice] << endl;
   choice:
   cout<<"Do you want to order this: (y/n) "<<endl;
   cin>>response;
   if(response=='y' || response=='Y')
   {
      ufile<<"\nFood Name: " << foodNames[choice]
<< "\nPrice: Rs " << prices[choice]
<< "\nCalories: " << calories[choice] << endl;
           response:
           cout<<"Do you want to order anything else? (y/n)"<<endl;
           cin>>response;
           if(response=='y' || response=='Y')
           {
               goto back;
           }
           else if(response=='n' || response=='N')
           {
           }
           else
           {
               cout<<"Invalid input! "<<endl;
               goto response;
           }
   }
   else if(response=='n' || response=='N')
   {
       goto back;
   }
   else
   {
       cout<<"Invalid input! "<<endl;
       goto choice;
   }
   ufile.close();
   return 0;
}