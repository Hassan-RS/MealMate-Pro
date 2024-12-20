#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    int order_value = 0;
    fstream ufile;

    
    ufile.open("zara_5575.txt", ios::in);

    if (ufile.is_open())
    {
        cout << "File found. Reading content:\n";
        string line;

        
        while (getline(ufile, line))
        {
           
            if (line.find("the price") != -1)
            {
               
                stringstream ss(line);
                string token;

                getline(ss, token, ':'); 
                getline(ss, token, '.'); 

                
                int price = stoi(token); 
                order_value += price;
            }
        }

        cout << "Total sum of prices: " << order_value << "\n";
        ufile.close();
    }
    else
    {
        cout << "Error: File not found.\n";
    }

    return 0;
}
