#include "../edora.h"
#include "login.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>
#include <conio.h>

using namespace std;

static string currentUser = "";
static bool loggedIn = false;

static fs::path usersFile()
{
    return edoraRoot / "C" / "system" / "users.sys";
}

static string inputPassword()
{
    string password;
    char ch;

    while (true)
    {
        ch = _getch();

        if (ch == 13)
        {
            cout << "\n";
            break;
        }

        if (ch == 8)
        {
            if (!password.empty())
            {
                password.pop_back();
                cout << "\b \b";
            }

            continue;
        }

        if (ch >= 32 && ch <= 126)
        {
            password += ch;
            cout << "*";
        }
    }

    return password;
}

static string hashPassword(const string& password)
{
    hash<string> hasher;
    size_t value = hasher(password);

    stringstream ss;
    ss << hex << value;

    return ss.str();
}

static bool readAccount(string& username, string& passwordHash)
{
    ifstream file(usersFile());

    if (!file)
        return false;

    username.clear();
    passwordHash.clear();

    string line;

    while (getline(file, line))
    {
        if (line.rfind("USERNAME=", 0) == 0)
            username = line.substr(9);

        else if (line.rfind("PASSWORD_HASH=", 0) == 0)
            passwordHash = line.substr(14);
    }

    return !username.empty() && !passwordHash.empty();
}

static bool accountExists()
{
    string username;
    string passwordHash;

    return readAccount(username, passwordHash);
}

bool createAccount()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "              CREATE ACCOUNT\n";
    cout << "============================================\n";

    string username;

    cout << "Username: ";
    getline(cin, username);

    if (username.empty())
    {
        cout << "Invalid username.\n";
        return false;
    }

    string password;

    cout << "Password: ";
    password = inputPassword();

    if (password.empty())
    {
        cout << "Password cannot be empty.\n";
        return false;
    }

    string confirm;

    cout << "Confirm : ";
    confirm = inputPassword();

    if (password != confirm)
    {
        cout << "Passwords do not match.\n";
        return false;
    }

    ofstream file(usersFile());

    if (!file)
    {
        cout << "Cannot create users.sys\n";
        return false;
    }

    file << "USERNAME=" << username << "\n";
    file << "PASSWORD_HASH=" << hashPassword(password) << "\n";
    file << "PRIVILEGE=USER\n";
    file << "STATUS=ACTIVE\n";

    file.close();

    cout << "\n";
    cout << "[ OK ] Account created.\n";

    return true;
}

bool loginSystem()
{
    if (!accountExists())
    {
        cout << "\n";
        cout << "============================================\n";
        cout << "              EDORA OS LOGIN\n";
        cout << "============================================\n";

        cout << "\nNo account found.\n";
        cout << "Create the first EDORA account.\n";

        if (!createAccount())
        {
            cout << "Account creation failed.\n";
            return false;
        }
    }

    while (!loggedIn)
    {
        cout << "\n";
        cout << "============================================\n";
        cout << "              EDORA OS LOGIN\n";
        cout << "============================================\n";

        string username;

        cout << "Username: ";
        getline(cin, username);

        string password;

        cout << "Password: ";
        password = inputPassword();

        string savedUser;
        string savedHash;

        if (!readAccount(savedUser, savedHash))
        {
            cout << "User database error.\n";
            return false;
        }

        if (username == savedUser &&
            hashPassword(password) == savedHash)
        {
            currentUser = savedUser;
            loggedIn = true;

            cout << "\n";
            cout << "[ OK ] Authentication successful.\n";
            cout << "Welcome back, "
                 << currentUser
                 << "!\n";

            return true;
        }

        cout << "\n";
        cout << "[FAIL] Invalid username or password.\n";
    }

    return true;
}

void changePassword()
{
    if (!loggedIn)
    {
        cout << "You are not logged in.\n";
        return;
    }

    string username;
    string oldHash;

    if (!readAccount(username, oldHash))
    {
        cout << "Cannot read account.\n";
        return;
    }

    cout << "\n";
    cout << "============================================\n";
    cout << "              CHANGE PASSWORD\n";
    cout << "============================================\n";

    string oldPassword;

    cout << "Current password: ";
    oldPassword = inputPassword();

    if (hashPassword(oldPassword) != oldHash)
    {
        cout << "Wrong current password.\n";
        return;
    }

    string newPassword;

    cout << "New password: ";
    newPassword = inputPassword();

    if (newPassword.empty())
    {
        cout << "Password cannot be empty.\n";
        return;
    }

    string confirm;

    cout << "Confirm password: ";
    confirm = inputPassword();

    if (newPassword != confirm)
    {
        cout << "Passwords do not match.\n";
        return;
    }

    ofstream file(usersFile());

    if (!file)
    {
        cout << "Cannot update users.sys\n";
        return;
    }

    file << "USERNAME=" << username << "\n";
    file << "PASSWORD_HASH=" << hashPassword(newPassword) << "\n";
    file << "PRIVILEGE=USER\n";
    file << "STATUS=ACTIVE\n";

    file.close();

    cout << "\n";
    cout << "[ OK ] Password changed successfully.\n";
}

void logoutUser()
{
    if (!loggedIn)
    {
        cout << "No user is logged in.\n";
        return;
    }

    cout << "Goodbye, "
         << currentUser
         << "!\n";

    currentUser.clear();
    loggedIn = false;
}

string getCurrentUser()
{
    return currentUser;
}

bool isLoggedIn()
{
    return loggedIn;
}

bool verifyCurrentPassword()
{
    if (!loggedIn)
        return false;

    string username;
    string storedHash;

    if (!readAccount(username, storedHash))
        return false;

    cout << "[sudo] password for "
         << currentUser
         << ": ";

    string password = inputPassword();

    return hashPassword(password) == storedHash;
}
