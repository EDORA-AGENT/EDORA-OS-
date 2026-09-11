#include "../edora.h"
#include "basic.h"
#include "../login/login.h"

#include <cstdlib>
#include <iostream>

using namespace std;

void commandHelp()
{
    cout << "\n";
    cout << "═══════════════════════════════════════════════════════\n";
    cout << "                 EDORA OS COMMANDS                   \n";
    cout << "═══════════════════════════════════════════════════════\n";

    cout << "\n[BASIC]\n";
    cout << "  help          Show this help\n";
    cout << "  clear         Clear screen\n";
    cout << "  whoami        Show current user\n";
    cout << "  pwd           Show current path\n";
    cout << "  status        Show system status\n";
    cout << "  drivers       Show driver status\n";

    cout << "\n[FILESYSTEM]\n";
    cout << "  drives        Show available drives\n";
    cout << "  ls / dir      List directory\n";
    cout << "  cd            Change directory\n";
    cout << "  mkdir         Create directory\n";
    cout << "  touch         Create file\n";
    cout << "  rm            Delete file/directory\n";
    cout << "  cat           Read file\n";
    cout << "  copy          Copy file\n";
    cout << "  move          Move file\n";
    cout << "  find          Search file\n";

    cout << "\n[APPLICATIONS]\n";
    cout << "  notepad       Text editor\n";
    cout << "  bin           Binary editor\n";
    cout << "  binread       Read binary file\n";
    cout << "  binhex        Show hexadecimal\n";
    cout << "  edo           EDO editor\n";
    cout << "  edoread       Read EDO file\n";
    cout << "  edoraw        Show raw EDO file\n";
    cout << "  game          Start game\n";
    cout << "  calc          Calculator\n";
    cout << "  todo          To-do list\n";
    cout << "  sysmon        System monitor\n";
    cout << "  debug         Runtime diagnostics\n";
    cout << "  apps          List installed applications\n";

    cout << "\n[SYSTEM]\n";
    cout << "  neofetch      System information\n";
    cout << "  sysinfo       Detailed system info\n";
    cout << "  date          Current date\n";
    cout << "  time          Current time\n";
    cout << "  ping          Network ping\n";
    cout << "  echo          Print text\n";
    cout << "  reboot        Restart EDORA OS\n";
    cout << "  shutdown      Shutdown EDORA OS\n";

    cout << "\n[SECURITY]\n";
    cout << "  sudo          Enter root mode\n";
    cout << "  root          Show root status\n";
    cout << "  passwd        Change password\n";
    cout << "  panic         Kernel panic\n";

    cout << "\n═══════════════════════════════════════════════════════\n";
}

void commandClear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void commandWhoami()
{
    cout << getCurrentUser();

    if (isRoot)
        cout << " (root)";

    cout << "\n";
}

void commandPwd()
{
    cout << getPath() << "\n";
}

void commandStatus()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "             EDORA SYSTEM STATUS\n";
    cout << "============================================\n";
    cout << "User          : " << getCurrentUser() << "\n";
    cout << "Role          : " << (isRoot ? "ROOT" : "USER") << "\n";
    cout << "Current Drive : " << currentDrive << ":\n";
    cout << "Current Path  : " << getPath() << "\n";
    cout << "Version       : " << EDORA_VERSION << "\n";
    cout << "Kernel        : " << KERNEL_VERSION << "\n";
    cout << "Shell         : " << SHELL_VERSION << "\n";
    cout << "============================================\n";
}

void commandDrivers()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "                DRIVER STATUS\n";
    cout << "============================================\n";
    cout << "VGA         : ONLINE\n";
    cout << "Keyboard    : ONLINE\n";
    cout << "Filesystem  : ONLINE\n";
    cout << "Network     : ONLINE\n";
    cout << "Security    : ONLINE\n";
    cout << "============================================\n";
}

void commandApps()
{
    cout << "\nInstalled applications:\n";
    cout << "  notepad  bin  edo  game  calc  todo  sysmon  debug\n";
}

void commandEcho(const string& text)
{
    cout << text << "\n";
}