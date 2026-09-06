#include "../edora.h"
#include "shell.h"

#include <iostream>
#include <string>

using namespace std;

void shellStart()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "               EDORA SHELL\n";
    cout << "============================================\n";

    cout << "EDORA-SHELL " << SHELL_VERSION << "\n";
    cout << "Type 'help' to see available commands.\n";

    cout << "============================================\n";
    cout << "\n";
}

void showPrompt()
{
    if (isRoot)
        cout << "root@edora:";
    else
        cout << "user@edora:";

    cout << getPath();

    if (isRoot)
        cout << "# ";
    else
        cout << "$ ";
}

void shellLoop()
{
    string command;

    showPrompt();
    getline(cin, command);

    if (command.empty())
        return;

    executeCommand(command);
}

void executeCommand(const string& command)
{
    // BASIC
    if (command == "help")
        commandHelp();

    else if (command == "clear")
        commandClear();

    else if (command == "whoami")
        commandWhoami();

    else if (command == "pwd")
        commandPwd();


    // FILESYSTEM
    else if (command == "ls")
        commandLs();

    else if (command == "dir")
        commandLs();

    else if (command == "cd")
        commandCd();

    else if (command == "mkdir")
        commandMkdir();

    else if (command == "touch")
        commandTouch();

    else if (command == "rm")
        commandRm();

    else if (command == "cat")
        commandCat();

    else if (command == "drives")
        commandDrives();


    // FILE COMMANDS
    else if (command == "copy")
        commandCopy();

    else if (command == "move")
        commandMove();

    else if (command == "find")
        commandFind();


    // DRIVES
    else if (command == "C:")
    {
        currentDrive = 'C';
        currentPath = drivePath('C');

        cout << "Switched to C:\\\n";
    }

    else if (command == "D:")
    {
        currentDrive = 'D';
        currentPath = drivePath('D');

        cout << "Switched to D:\\\n";
    }

    else if (command == "E:")
    {
        currentDrive = 'E';
        currentPath = drivePath('E');

        cout << "Switched to E:\\\n";
    }


    // APPLICATIONS
    else if (command == "notepad")
        notepad();

    else if (command == "bin")
        binaryEditor();

    else if (command == "binread")
        binaryRead();

    else if (command == "binhex")
        binaryHex();

    else if (command == "edo")
        edoEditor();

    else if (command == "edoread")
        edoRead();

    else if (command == "edoraw")
        edoRaw();

    else if (command == "game")
        game();


    // NETWORK
    else if (command == "ping")
        commandPing();


    // SYSTEM
    else if (command == "neofetch")
        commandNeofetch();

    else if (command == "sysinfo")
        commandSysinfo();

    else if (command == "date")
        commandDate();

    else if (command == "time")
        commandTime();


    // SECURITY
    else if (command == "sudo")
        commandSudo();

    else if (command == "root")
        commandRoot();

    else if (command == "panic")
        kernelPanic();


    // POWER
    else if (command == "reboot")
        rebootSystem();

    else if (command == "shutdown")
        shutdownSystem();


    // EXIT ROOT
    else if (command == "exit")
    {
        if (isRoot)
        {
            isRoot = false;
            cout << "Exited root mode.\n";
        }
        else
        {
            cout << "Use 'shutdown' to shut down EDORA OS.\n";
        }
    }

    else
    {
        cout << "edora: command not found: "
             << command << "\n";
    }
}