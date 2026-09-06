#include "../edora.h"
#include "edo.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char shiftChar(char c, int shift)
{
    if (c >= 'a' && c <= 'z')
        return char((c - 'a' + shift + 26) % 26 + 'a');

    if (c >= 'A' && c <= 'Z')
        return char((c - 'A' + shift + 26) % 26 + 'A');

    return c;
}

string edoEncrypt(const string& text)
{
    string result;

    for (char c : text)
        result += shiftChar(c, 2);

    return result;
}

string edoDecrypt(const string& text)
{
    string result;

    for (char c : text)
        result += shiftChar(c, -2);

    return result;
}

void edoEditor()
{
    string filename;
    string line;

    cout << "\n";
    cout << "============================================\n";
    cout << "               EDORA EDO\n";
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

    ofstream file(filePath);

    if (!file)
    {
        cout << "Cannot create EDO file.\n";
        return;
    }

    cout << "EDO encryption enabled.\n";
    cout << "Type :save to save.\n";
    cout << "----------------------------------------\n";

    while (true)
    {
        getline(cin, line);

        if (line == ":save")
        {
            file.close();
            cout << "EDO file saved.\n";
            return;
        }

        file << edoEncrypt(line) << "\n";
    }
}

void edoRead()
{
    string filename;
    string line;

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

    ifstream file(filePath);

    if (!file)
    {
        cout << "Cannot open EDO file.\n";
        return;
    }

    cout << "\n";
    cout << "------------- EDO DECRYPTED -------------\n";

    while (getline(file, line))
        cout << edoDecrypt(line) << "\n";

    cout << "------------------------------------------\n";
}

void edoRaw()
{
    string filename;
    string line;

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

    ifstream file(filePath);

    if (!file)
    {
        cout << "Cannot open EDO file.\n";
        return;
    }

    cout << "\n";
    cout << "--------------- EDO RAW -----------------\n";

    while (getline(file, line))
        cout << line << "\n";

    cout << "------------------------------------------\n";
}