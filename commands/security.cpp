#include "../edora.h"
#include "security.h"

#include <iostream>
#include <string>

using namespace std;

void commandSudo()
{
    if (isRoot)
    {
        cout << "Already running as root.\n";
        return;
    }

    string password;

    cout << "[sudo] password for " << username << ": ";
    getline(cin, password);

    if (password == ROOT_PASSWORD)
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
        cout << "Current user : " << username << "\n";
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
    cout << "systemcl deletion request accepted.\n";
    cout << "Simulating system destruction...\n";
    cout << "EDORA OS has been halted.\n";
    cout << "--------------------------------------------\n";

    running = false;
}