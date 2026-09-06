#include "../edora.h"
#include "ping.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void commandPing(const string& host)
{
    string target = host;

    if (target.empty())
    {
        cout << "Host: ";
        getline(cin, target);
    }

    if (target.empty())
        return;

    cout << "\n";
    cout << "Pinging " << target << "...\n";
    cout << "--------------------------------------------\n";

#ifdef _WIN32
    string command = "ping -n 4 " + target;
#else
    string command = "ping -c 4 " + target;
#endif

    system(command.c_str());

    cout << "--------------------------------------------\n";
}