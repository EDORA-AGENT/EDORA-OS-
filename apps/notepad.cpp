#include "../edora.h"
#include "notepad.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void notepad()
{
    string filename;
    string line;

    cout << "\n";
    cout << "============================================\n";
    cout << "              EDORA NOTEPAD\n";
    cout << "============================================\n";

    cout << "File: ";
    getline(cin, filename);

    if (filename.empty())
        return;

    fs::path filePath = currentPath / filename;

    if (!insideDrive(filePath))
    {
        cout << "Access denied.\n";
        return;
    }

    cout << "\n";
    cout << "1. Open existing file\n";
    cout << "2. Create new file\n";
    cout << "Choice: ";

    string choice;
    getline(cin, choice);

    if (choice == "1")
    {
        if (!fs::exists(filePath))
        {
            cout << "File not found.\n";
            return;
        }

        ifstream file(filePath);

        if (!file)
        {
            cout << "Cannot open file.\n";
            return;
        }

        cout << "\n";
        cout << "------------- FILE CONTENT -------------\n";

        while (getline(file, line))
            cout << line << "\n";

        cout << "----------------------------------------\n";

        file.close();

        cout << "\nEdit file? (y/n): ";
        string edit;
        getline(cin, edit);

        if (edit != "y" && edit != "Y")
            return;
    }
    else if (choice != "2")
    {
        cout << "Invalid choice.\n";
        return;
    }

    cout << "\n";
    cout << "Enter text.\n";
    cout << "Type :save to save.\n";
    cout << "Type :cancel to cancel.\n";
    cout << "----------------------------------------\n";

    ofstream file(filePath);

    if (!file)
    {
        cout << "Cannot open file for writing.\n";
        return;
    }

    while (true)
    {
        getline(cin, line);

        if (line == ":save")
        {
            file.close();
            cout << "File saved successfully.\n";
            return;
        }

        if (line == ":cancel")
        {
            file.close();
            cout << "Operation cancelled.\n";
            return;
        }

        file << line << "\n";
    }
}