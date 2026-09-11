#include "../edora.h"
#include "shell.h"
#include "../login/login.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void shellStart()
{
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║               EDORA SHELL v2.1                    ║\n";
    cout << "╠══════════════════════════════════════════════════════╣\n";
    cout << "║  Type 'help' to see available commands.            ║\n";
    cout << "║  Type 'status' for system diagnostics.            ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n\n";
}

void showPrompt()
{
    if (isRoot)
        cout << "root@edora:";
    else
        cout << getCurrentUser() << "@edora:";

    cout << getPath();

    if (isRoot)
        cout << "# ";
    else
        cout << "$ ";
}

void shellLoop()
{
    string input;
    showPrompt();
    getline(cin, input);

    if (input.empty())
        return;

    executeCommand(input);
}

void executeCommand(const string& input)
{
    stringstream ss(input);
    string command;
    string argument;

    ss >> command;
    getline(ss, argument);

    if (!argument.empty() && argument[0] == ' ')
        argument.erase(0, 1);

    if (command == "help")
        commandHelp();
    else if (command == "clear")
        commandClear();
    else if (command == "whoami")
        commandWhoami();
    else if (command == "pwd")
        commandPwd();
    else if (command == "status")
        commandStatus();
    else if (command == "drivers")
        commandDrivers();

    else if (command == "ls" || command == "dir")
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
    else if (command == "copy")
        commandCopy();
    else if (command == "move")
        commandMove();
    else if (command == "find")
        commandFind();

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
    else if (command == "calc")
        calculatorApp();
    else if (command == "todo")
        todoApp();
    else if (command == "sysmon")
        systemMonitorApp();
    else if (command == "debug")
        debugApp();
    else if (command == "apps")
        commandApps();

    else if (command == "ping")
        commandPing(argument);
    else if (command == "echo")
        commandEcho(argument);

    else if (command == "neofetch")
        commandNeofetch();
    else if (command == "sysinfo")
        commandSysinfo();
    else if (command == "date")
        commandDate();
    else if (command == "time")
        commandTime();

    else if (command == "sudo")
        commandSudo();
    else if (command == "root")
        commandRoot();
    else if (command == "passwd")
        changePassword();
    else if (command == "logout")
    {
        if (isRoot)
        {
            isRoot = false;
            cout << "Exited root mode.\n";
        }

        logoutUser();

        if (!loginSystem())
            running = false;
    }
    else if (command == "panic")
        kernelPanic();
    else if (command == "reboot")
        rebootSystem();
    else if (command == "shutdown")
        shutdownSystem();
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
        cout << "edora: command not found: " << command << "\n";
    }
}