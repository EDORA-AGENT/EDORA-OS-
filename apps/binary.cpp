#include "../edora.h"
#include "binary.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void binaryEditor()
{
    string filename;
    string line;

    cout << "\n";
    cout << "============================================\n";
    cout << "            EDORA BINARY EDITOR\n";
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

    ofstream file(filePath, ios::binary);

    if (!file)
    {
        cout << "Cannot create binary file.\n";
        return;
    }

    cout << "Enter data.\n";
    cout << "Type :save to save.\n";
    cout << "----------------------------------------\n";

    while (true)
    {
        getline(cin, line);

        if (line == ":save")
        {
            file.close();
            cout << "Binary file saved.\n";
            return;
        }

        file << line << '\n';
    }
}

void binaryRead()
{
    string filename;

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

    ifstream file(filePath, ios::binary);

    if (!file)
    {
        cout << "Cannot open file.\n";
        return;
    }

    cout << "\n";
    cout << "------------- BINARY DATA -------------\n";

    char c;

    while (file.get(c))
    {
        if (c >= 32 && c <= 126)
            cout << c;
        else
            cout << '.';
    }

    cout << "\n----------------------------------------\n";
}

void binaryHex()
{
    string filename;

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

    ifstream file(filePath, ios::binary);

    if (!file)
    {
        cout << "Cannot open file.\n";
        return;
    }

    cout << "\n";
    cout << "--------------- HEX VIEW ---------------\n";

    unsigned char buffer[16];
    size_t offset = 0;

    while (file)
    {
        file.read(reinterpret_cast<char*>(buffer), 16);
        streamsize count = file.gcount();

        if (count <= 0)
            break;

        cout << hex << setw(8) << setfill('0') << offset << "  ";

        for (int i = 0; i < 16; i++)
        {
            if (i < count)
                cout << setw(2) << static_cast<int>(buffer[i]) << " ";
            else
                cout << "   ";
        }

        cout << " ";

        for (int i = 0; i < count; i++)
        {
            if (buffer[i] >= 32 && buffer[i] <= 126)
                cout << buffer[i];
            else
                cout << '.';
        }

        cout << "\n";

        offset += count;
    }

    cout << dec;
    cout << "----------------------------------------\n";
}