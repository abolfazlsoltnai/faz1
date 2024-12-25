#include "header.hpp"
#include "classes.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "command_defenition.hpp"
using namespace std;

int detect_main_command(string command, vector<string> defined_commands) {
    for (int i = 0; i < defined_commands.size(); i++) {
        if (command == defined_commands[i]) {
            return i + 1;
        }
    }
    return 0;
}


void split_command(string input, vector<string>& commands) {
    stringstream ss(input);
    string word;
    commands.clear();
    while (ss >> word) {
        commands.push_back(word);
    }
}







int main(int argc, char* argv[]) {

    User *first_user = 0;

    string command;
    vector<string> commands;


    System system;
    string resturant_file_name = argv[1];
    ifstream file(resturant_file_name);
    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream lineStream(line);
        string cell;
        vector<string> row;

        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }



        Resturant x(row[0], row[1], row[2], row[3], row[4], row[5]);
        system.add_resturant(x);
    }

    file.close();

    string district_file_name = argv[2];
    ifstream file2(district_file_name);
    getline(file2, line);

        while (getline(file2, line)) {
        stringstream lineStream(line);
        string cell;
        vector<string> row;

        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        system.add_district(row[0],row[1]);
    }

    file2.close();


    vector<string> defined_commands = {"POST","GET","PUT"};


    while (getline(cin,command))
    {
        split_command(command, commands);
        if (commands.empty()) continue;
        string z;
        switch (detect_main_command(commands[0], defined_commands))
        {
            case 0:
                cout << "Bad Request" << endl;
                break;
            case 1:
                z = POST(commands,system,first_user);
                if(z == "signup-1"){
                    first_user = system.get_last_user();
                }else if(z == "logout-succsess"){
                    first_user = 0;
                }else if(z == ""){

                }else{
                    first_user = system.get_lost_login(z);
                }
                
                break;
            case 2:  
                GET(commands,system,first_user);
                break;  
            case 3:
                PUT(commands,system,first_user);       
        }    
    }








    return 0;
}
