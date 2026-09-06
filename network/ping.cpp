#include "../edora.h"
#include "ping.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void commandPing()
{
    string host;

    cout << "Host: ";
    getline(cin, host);

    if (host.empty())
        return;

    cout << "\n";
    cout << "Pinging " << host << "...\n";
    cout << "--------------------------------------------\n";

#ifdef _WIN32
    string command = "ping -n 4 " + host;
#else
    string command = "ping -c 4 " + host;
#endif

    system(command.c_str());

    cout << "--------------------------------------------\n";
}