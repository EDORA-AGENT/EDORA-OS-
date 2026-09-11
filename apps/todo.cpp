#include "../edora.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void todoApp()
{
    vector<string> tasks;

    cout << "\n";
    cout << "============================================\n";
    cout << "               EDORA TODO\n";
    cout << "============================================\n";
    cout << "Commands: add, list, done, clear, exit\n";

    while (true) {
        cout << "todo> ";
        string command;
        getline(cin, command);

        if (command == "exit") {
            cout << "Todo closed.\n";
            return;
        }
        else if (command == "list") {
            if (tasks.empty()) {
                cout << "No tasks yet.\n";
            } else {
                for (size_t i = 0; i < tasks.size(); ++i) {
                    cout << i + 1 << ". " << tasks[i] << "\n";
                }
            }
        }
        else if (command == "clear") {
            tasks.clear();
            cout << "Tasks cleared.\n";
        }
        else if (command.rfind("add ", 0) == 0) {
            tasks.push_back(command.substr(4));
            cout << "Task added.\n";
        }
        else if (command.rfind("done ", 0) == 0) {
            int index = stoi(command.substr(5)) - 1;
            if (index >= 0 && index < static_cast<int>(tasks.size())) {
                cout << "Completed: " << tasks[index] << "\n";
                tasks.erase(tasks.begin() + index);
            } else {
                cout << "Invalid task index.\n";
            }
        }
        else {
            cout << "Unknown command.\n";
        }
    }
}
