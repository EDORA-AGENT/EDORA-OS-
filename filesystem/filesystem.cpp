#include "../edora.h"
#include "filesystem.h"
#include<algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

using namespace std;
namespace fs = std::filesystem;

// ======================================================
//                  FILESYSTEM INIT
// ======================================================

void filesystemInit()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "          EDORA VIRTUAL FILESYSTEM\n";
    cout << "============================================\n";

    try
    {
        fs::create_directories(edoraRoot);

        fs::create_directories(
            edoraRoot / "C" / "system"
        );

        fs::create_directories(
            edoraRoot / "C" / "programs"
        );

        fs::create_directories(
            edoraRoot / "D" / "games"
        );

        fs::create_directories(
            edoraRoot / "D" / "data"
        );

        fs::create_directories(
            edoraRoot / "E" / "backup"
        );

        currentDrive = 'C';
        currentPath = drivePath('C');

        cout << "[ OK ] EDORA_DRIVES\n";
        cout << "[ OK ] C: drive\n";
        cout << "[ OK ] D: drive\n";
        cout << "[ OK ] E: drive\n";
        cout << "[ OK ] System directories\n";

        cout << "Filesystem initialized successfully.\n";
    }
    catch (...)
    {
        cout << "[FAIL] Filesystem initialization failed.\n";
    }

    cout << "============================================\n";
}

// ======================================================
//                    DRIVE PATH
// ======================================================

fs::path drivePath(char drive)
{
    drive = toupper(drive);

    if (drive == 'C' ||
        drive == 'D' ||
        drive == 'E')
    {
        return edoraRoot /
               string(1, drive);
    }

    return edoraRoot / "C";
}

// ======================================================
//                    GET PATH
// ======================================================

string getPath()
{
    fs::path root =
        drivePath(currentDrive);

    string result =
        string(1, currentDrive) + ":\\";

    try
    {
        fs::path relative =
            fs::relative(
                currentPath,
                root
            );

        if (!relative.empty() &&
            relative.string() != ".")
        {
            string r =
                relative.string();

            replace(
                r.begin(),
                r.end(),
                '/',
                '\\'
            );

            result += r;
        }
    }
    catch (...)
    {
    }

    return result;
}

// ======================================================
//                  SECURITY CHECK
// ======================================================

bool insideDrive(fs::path path)
{
    try
    {
        fs::path root =
            fs::weakly_canonical(
                drivePath(currentDrive)
            );

        fs::path target =
            fs::weakly_canonical(path);

        string rootString =
            root.generic_string();

        string targetString =
            target.generic_string();

        if (targetString == rootString)
            return true;

        if (targetString.size() >
            rootString.size() &&
            targetString.compare(
                0,
                rootString.size(),
                rootString
            ) == 0 &&
            targetString[rootString.size()] == '/')
        {
            return true;
        }

        return false;
    }
    catch (...)
    {
        return false;
    }
}

// ======================================================
//                  SHOW DRIVES
// ======================================================

void commandDrives()
{
    cout << "\n";
    cout << "+============================================+\n";
    cout << "|             EDORA DRIVES                   |\n";
    cout << "+============================================+\n";
    cout << "| C:   System                                |\n";
    cout << "| D:   Data / Games                          |\n";
    cout << "| E:   Backup                                |\n";
    cout << "+============================================+\n";
}

// ======================================================
//                    LIST FILES
// ======================================================

void commandLs()
{
    cout << "\n";
    cout << "Directory of "
         << getPath()
         << "\n\n";

    try
    {
        bool empty = true;

        for (const auto& entry :
             fs::directory_iterator(currentPath))
        {
            empty = false;

            if (entry.is_directory())
            {
                cout << "[DIR]  ";
            }
            else
            {
                cout << "[FILE] ";
            }

            cout << entry.path()
                         .filename()
                         .string()
                 << "\n";
        }

        if (empty)
            cout << "Directory is empty.\n";
    }
    catch (...)
    {
        cout << "Cannot access directory.\n";
    }
}

// ======================================================
//                    CHANGE DIRECTORY
// ======================================================

void commandCd()
{
    string input;

    cout << "Directory: ";
    getline(cin, input);

    if (input.empty())
        return;

    if (input == "\\")
    {
        currentPath =
            drivePath(currentDrive);

        return;
    }

    fs::path target;

    if (input.size() >= 2 &&
        input[1] == ':')
    {
        char drive =
            toupper(input[0]);

        if (drive != 'C' &&
            drive != 'D' &&
            drive != 'E')
        {
            cout << "Invalid drive.\n";
            return;
        }

        string rest =
            input.substr(2);

        while (!rest.empty() &&
               (rest[0] == '\\' ||
                rest[0] == '/'))
        {
            rest.erase(0, 1);
        }

        currentDrive = drive;

        target =
            drivePath(drive) /
            rest;
    }
    else
    {
        target =
            currentPath / input;
    }

    if (!insideDrive(target))
    {
        cout << "Access denied.\n";
        return;
    }

    try
    {
        target =
            fs::weakly_canonical(target);

        if (!fs::exists(target))
        {
            cout << "Directory not found.\n";
            return;
        }

        if (!fs::is_directory(target))
        {
            cout << "Not a directory.\n";
            return;
        }

        currentPath = target;

        cout << "Current path: "
             << getPath()
             << "\n";
    }
    catch (...)
    {
        cout << "Cannot change directory.\n";
    }
}

// ======================================================
//                    MAKE DIRECTORY
// ======================================================

void commandMkdir()
{
    string name;

    cout << "Directory name: ";
    getline(cin, name);

    if (name.empty())
        return;

    fs::path target =
        currentPath / name;

    if (!insideDrive(target))
    {
        cout << "Access denied.\n";
        return;
    }

    try
    {
        if (fs::create_directory(target))
            cout << "Directory created.\n";
        else
            cout << "Directory already exists.\n";
    }
    catch (...)
    {
        cout << "Failed to create directory.\n";
    }
}

// ======================================================
//                      TOUCH
// ======================================================

void commandTouch()
{
    string name;

    cout << "File name: ";
    getline(cin, name);

    if (name.empty())
        return;

    fs::path target =
        currentPath / name;

    if (!insideDrive(target))
    {
        cout << "Access denied.\n";
        return;
    }

    try
    {
        ofstream file(
            target,
            ios::app
        );

        if (file)
            cout << "File created.\n";
        else
            cout << "Failed to create file.\n";
    }
    catch (...)
    {
        cout << "Failed to create file.\n";
    }
}

// ======================================================
//                       RM
// ======================================================

void commandRm()
{
    string name;

    cout << "Delete: ";
    getline(cin, name);

    if (name.empty() ||
        name == "." ||
        name == "..")
    {
        cout << "Invalid target.\n";
        return;
    }

    fs::path target =
        currentPath / name;

    if (!insideDrive(target))
    {
        cout << "Access denied.\n";
        return;
    }

    fs::path root =
        drivePath(currentDrive);

    try
    {
        target =
            fs::weakly_canonical(target);

        root =
            fs::weakly_canonical(root);

        if (target == root)
        {
            cout << "Cannot delete drive root.\n";
            return;
        }

        if (!fs::exists(target))
        {
            cout << "File or directory not found.\n";
            return;
        }

        fs::remove_all(target);

        cout << "Deleted successfully.\n";
    }
    catch (...)
    {
        cout << "Delete failed.\n";
    }
}

// ======================================================
//                       CAT
// ======================================================

void commandCat()
{
    string name;

    cout << "File: ";
    getline(cin, name);

    if (name.empty())
        return;

    fs::path target =
        currentPath / name;

    if (!insideDrive(target))
    {
        cout << "Access denied.\n";
        return;
    }

    if (!fs::exists(target) ||
        !fs::is_regular_file(target))
    {
        cout << "File not found.\n";
        return;
    }

    ifstream file(target);

    if (!file)
    {
        cout << "Cannot open file.\n";
        return;
    }

    cout << "\n";
    cout << "--------------------------------------------\n";

    string line;

    while (getline(file, line))
    {
        cout << line << "\n";
    }

    cout << "--------------------------------------------\n";
}