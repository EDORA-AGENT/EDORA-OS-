#include "../edora.h"
#include "file.h"

#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
namespace fs = std::filesystem;

void commandCopy()
{
    string source;
    string destination;

    cout << "Source: ";
    getline(cin, source);

    cout << "Destination: ";
    getline(cin, destination);

    if (source.empty() || destination.empty())
        return;

    fs::path src = currentPath / source;
    fs::path dst = currentPath / destination;

    if (!insideDrive(src) || !insideDrive(dst))
    {
        cout << "Access denied.\n";
        return;
    }

    try
    {
        if (!fs::exists(src))
        {
            cout << "Source not found.\n";
            return;
        }

        if (fs::is_directory(src))
            fs::copy(src, dst, fs::copy_options::recursive);
        else
            fs::copy_file(src, dst, fs::copy_options::overwrite_existing);

        cout << "Copied successfully.\n";
    }
    catch (...)
    {
        cout << "Copy failed.\n";
    }
}

void commandMove()
{
    string source;
    string destination;

    cout << "Source: ";
    getline(cin, source);

    cout << "Destination: ";
    getline(cin, destination);

    if (source.empty() || destination.empty())
        return;

    fs::path src = currentPath / source;
    fs::path dst = currentPath / destination;

    if (!insideDrive(src) || !insideDrive(dst))
    {
        cout << "Access denied.\n";
        return;
    }

    try
    {
        if (!fs::exists(src))
        {
            cout << "Source not found.\n";
            return;
        }

        fs::rename(src, dst);

        cout << "Moved successfully.\n";
    }
    catch (...)
    {
        cout << "Move failed.\n";
    }
}

void commandFind()
{
    string name;

    cout << "Search: ";
    getline(cin, name);

    if (name.empty())
        return;

    try
    {
        bool found = false;

        for (const auto& entry : fs::recursive_directory_iterator(currentPath))
        {
            if (entry.path().filename().string() == name)
            {
                cout << entry.path().string() << "\n";
                found = true;
            }
        }

        if (!found)
            cout << "No matching files found.\n";
    }
    catch (...)
    {
        cout << "Search failed.\n";
    }
}