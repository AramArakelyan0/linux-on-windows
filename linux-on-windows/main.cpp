#include <iostream>
#include <string>
#include <sstream>
#include "functions.h"
#include <map>

using namespace std;

int main() {   
    map<string, void (*)(const string&)> functionMap;

    functionMap.insert({ "touch", createFile });
    functionMap.insert({ "cd", changeDirectory });
    functionMap.insert({ "pwd", printDirectory });
    functionMap.insert({ "ls", listDirectoryItems });
    functionMap.insert({ "mkdir", createDirectory });
    functionMap.insert({ "rm", removeFile });
    functionMap.insert({ "rmdir", removeEmptyDirectory });

    cout << "Please enter a valid command. Type [exit] to end the program." << endl;
    string input;

    while (true) {
        cout << endl << '>';
        getline(cin, input);
        if (input == "exit")
        {
            break;
        }


        string command;
        string argument;
        stringstream toBeSplitted(input);

        //splitting input into command and argument parts
        toBeSplitted >> command;
        getline(toBeSplitted, argument);
        int pos = argument.find_first_not_of(' ');
        argument.erase(0, pos);

        //mapping the command to the corresponding function from functionMap
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

