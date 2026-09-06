#include "../edora.h"
#include "../login/login.h"
#include "security.h"

#include <iostream>

using namespace std;

void commandSudo()
{
    if (isRoot)
    {
        cout << "Already running as root.\n";
        return;
    }

    if (!isLoggedIn())
    {
        cout << "No user is logged in.\n";
        return;
    }

    if (verifyCurrentPassword())
    {
        isRoot = true;

        cout << "Authentication successful.\n";
        cout << "You are now root.\n";
    }
    else
    {
        cout << "Sorry, try again.\n";
    }
}

void commandRoot()
{
    cout << "\n";
    cout << "EDORA Security Manager\n";

    if (isRoot)
    {
        cout << "Current user : root\n";
        cout << "Privilege    : ADMINISTRATOR\n";
        cout << "Status       : ROOT ACCESS\n";
    }
    else
    {
        cout << "Current user : " << getCurrentUser() << "\n";
        cout << "Privilege    : USER\n";
        cout << "Status       : LIMITED ACCESS\n";
    }

    cout << "\n";
}

void commandDelete()
{
    if (!isRoot)
    {
        cout << "Permission denied.\n";
        cout << "Root privileges required.\n";
        return;
    }

    cout << "\n";
    cout << "EDORA SECURITY WARNING\n";
    cout << "--------------------------------------------\n";
    cout << "The requested operation is simulated only.\n";
    cout << "Real operating system files will NEVER be deleted.\n";
    cout << "\n";

    cout << "System deletion request accepted.\n";
    cout << "Simulating system destruction...\n";
    cout << "EDORA OS has been halted.\n";

    cout << "--------------------------------------------\n";

    running = false;
}

void commandPasswd()
{
    changePassword();
}
