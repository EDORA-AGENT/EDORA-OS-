#include "../edora.h"
#include "../login/login.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void systemMonitorApp()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "             EDORA SYSTEM MONITOR\n";
    cout << "============================================\n";
    cout << "CPU      : x86 / Protected Mode\n";
    cout << "RAM      : Virtual memory manager ready\n";
    cout << "Storage  : Virtual EDORA_DRIVES\n";
    cout << "Kernel   : " << KERNEL_VERSION << "\n";
    cout << "Shell    : " << SHELL_VERSION << "\n";
    cout << "User     : " << getCurrentUser() << "\n";
    cout << "Drive    : " << currentDrive << ":\n";
    cout << "Path     : " << getPath() << "\n";
    cout << "Status   : " << (isRoot ? "ROOT" : "USER") << "\n";
    cout << "============================================\n";
}
