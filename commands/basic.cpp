#include "../edora.h"
#include "basic.h"

#include <iostream>
#include <cstdlib>

using namespace std;

void commandHelp()
{
    cout << "\n";
    cout << "================ EDORA OS COMMANDS ================\n";

    cout << "\n[BASIC]\n";
    cout << "  help          Show this help\n";
    cout << "  clear         Clear screen\n";
    cout << "  whoami        Show current user\n";
    cout << "  pwd           Show current path\n";

    cout << "\n[FILESYSTEM]\n";
    cout << "  drives        Show available drives\n";
    cout << "  ls            List directory\n";
    cout << "  dir           List directory\n";
    cout << "  cd            Change directory\n";
    cout << "  mkdir         Create directory\n";
    cout << "  touch         Create file\n";
    cout << "  rm            Delete file/directory\n";
    cout << "  cat           Read file\n";

    cout << "\n[APPLICATIONS]\n";
    cout << "  notepad       Text editor\n";
    cout << "  bin           Binary editor\n";
    cout << "  binread       Read binary file\n";
    cout << "  binhex        Show hexadecimal\n";
    cout << "  edo           EDO editor\n";
    cout << "  edoread       Read EDO file\n";
    cout << "  edoraw        Show raw EDO file\n";
    cout << "  game          Start game\n";

    cout << "\n[SYSTEM]\n";
    cout << "  neofetch      System information\n";
    cout << "  sysinfo       Detailed system info\n";
    cout << "  date          Current date\n";
    cout << "  time          Current time\n";
    cout << "  ping          Network ping\n";
    cout << "  reboot        Restart EDORA OS\n";
    cout << "  shutdown      Shutdown EDORA OS\n";

    cout << "\n[SECURITY]\n";
    cout << "  sudo          Enter root mode\n";
    cout << "  root          Show root status\n";
    cout << "  panic         Kernel panic\n";

    cout << "\n====================================================\n";
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
    cout << username;

    if (isRoot)
        cout << " (root)";

    cout << "\n";
}

void commandPwd()
{
    cout << getPath() << "\n";
}