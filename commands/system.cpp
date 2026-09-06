#include "../edora.h"
#include "system.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;

void commandNeofetch()
{
    cout << "\n";
    cout << "        ______ ____   ____  ____      _    \n";
    cout << "       |  ____|  _ \\ / __ \\|  _ \\    / \\   \n";
    cout << "       | |__  | | | | |  | | |_) |  / _ \\  \n";
    cout << "       |  __| | | | | |  | |  _ <  / ___ \\ \n";
    cout << "       | |____| |_| | |__| | |_) |/ /   \\ \\\n";
    cout << "       |______|____/ \\____/|____//_/     \\_\\\n";

    cout << "\n";
    cout << "       EDORA OS\n";
    cout << "       -------------------------\n";
    cout << "       OS       : EDORA OS\n";
    cout << "       Version  : " << EDORA_VERSION << "\n";
    cout << "       Kernel   : " << KERNEL_VERSION << "\n";
    cout << "       Shell    : " << SHELL_VERSION << "\n";
    cout << "       User     : " << username << "\n";
    cout << "       Drive    : " << currentDrive << ":\n";
    cout << "       Path     : " << getPath() << "\n";
    cout << "       Mode     : " << (isRoot ? "ROOT" : "USER") << "\n";
    cout << "\n";
}

void commandSysinfo()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "              EDORA SYSTEM INFO\n";
    cout << "============================================\n";

    cout << "Operating System : EDORA OS\n";
    cout << "Version          : " << EDORA_VERSION << "\n";
    cout << "Kernel           : " << KERNEL_VERSION << "\n";
    cout << "Shell            : " << SHELL_VERSION << "\n";
    cout << "Username         : " << username << "\n";
    cout << "Current Drive    : " << currentDrive << ":\n";
    cout << "Current Path     : " << getPath() << "\n";
    cout << "Security Mode    : " << (isRoot ? "ROOT" : "USER") << "\n";
    cout << "Virtual Root     : " << edoraRoot.string() << "\n";

    cout << "============================================\n";
}

void commandDate()
{
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);

    tm localTime{};

#ifdef _WIN32
    localtime_s(&localTime, &currentTime);
#else
    localtime_r(&currentTime, &localTime);
#endif

    cout << put_time(&localTime, "%Y-%m-%d") << "\n";
}

void commandTime()
{
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);

    tm localTime{};

#ifdef _WIN32
    localtime_s(&localTime, &currentTime);
#else
    localtime_r(&currentTime, &localTime);
#endif

    cout << put_time(&localTime, "%H:%M:%S") << "\n";
}