#include <iostream>
#include <string>
#include <sstream>
#include "functions.h"
#include <map>

using namespace std;


int main() {
    map <string, void (*)(const string)> functionMap;

    functionMap.insert({ "touch", createFile });

    cout << "Please enter a valid command. Type [exit] to end the program." << endl;
    string input;

    while (true) {
        cout << endl << '>';
        getline(cin, input);
        if (input == "exit")
        {
            break;
        }

        string command, argument;
        stringstream toBeSplitted(input);

        toBeSplitted >> command;
        getline(toBeSplitted, argument);
        int pos = argument.find_first_not_of(' ');
        argument.erase(0, pos);

        auto it = functionMap.find(command);
        if (it != functionMap.end())
        {
            it->second(argument);
        }
        else
        {
            cout << "Command not found.";
        }
    }
}

