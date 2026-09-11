#ifndef EDORA_H
#define EDORA_H

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using namespace std;

// ======================================================
//                    EDORA OS CORE
// ======================================================

extern bool running;
extern bool isRoot;
extern string username;
extern string password;

extern fs::path edoraRoot;
extern fs::path currentPath;
extern char currentDrive;

// ======================================================
//                    SYSTEM CONSTANTS
// ======================================================

const string EDORA_VERSION = "2.1";
const string KERNEL_VERSION = "2.1";
const string SHELL_VERSION = "2.1";
const string ROOT_PASSWORD = "1234";

// ======================================================
//                    DRIVE SYSTEM
// ======================================================

fs::path drivePath(char drive);
string getPath();
bool insideDrive(fs::path path);

// ======================================================
//                    KERNEL
// ======================================================

void kernelInit();
void kernelShutdown();
void kernelPanic();
void rebootSystem();
void shutdownSystem();

// ======================================================
//                    SHELL
// ======================================================

void shellStart();
void shellLoop();
void showPrompt();
void executeCommand(const string& command);

// ======================================================
//                    BASIC COMMANDS
// ======================================================

void commandHelp();
void commandClear();
void commandWhoami();
void commandPwd();
void commandStatus();
void commandDrivers();
void commandNeofetch();
void commandSysinfo();
void commandDate();
void commandTime();

// ======================================================
//                    FILESYSTEM
// ======================================================

void filesystemInit();
void commandDrives();
void commandLs();
void commandCd();
void commandMkdir();
void commandTouch();
void commandRm();
void commandCat();
void commandCopy();
void commandMove();
void commandFind();

// ======================================================
//                    APPLICATIONS
// ======================================================

void notepad();
void binaryEditor();
void binaryRead();
void binaryHex();
void edoEditor();
void edoRead();
void edoRaw();
void game();
void calculatorApp();
void todoApp();
void systemMonitorApp();
void debugApp();

// ======================================================
//                    NETWORK
// ======================================================

void commandPing(const std::string& host = "");
void commandApps();
void commandEcho(const std::string& text);

// ======================================================
//                    SECURITY
// ======================================================

void commandSudo();
void commandRoot();
void commandDelete();
void commandPasswd();

#endif