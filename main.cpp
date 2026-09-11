#include "edora.h"
#include "drivers/driver.h"
#include "filesystem/filesystem.h"
#include "login/login.h"

// ======================================================
//                    EDORA OS
//                    MAIN ENTRY
// ======================================================

bool running = true;
bool isRoot = false;
string username;
string password;

fs::path edoraRoot;
fs::path currentPath;
char currentDrive = 'C';

// ======================================================
//                         MAIN
// ======================================================

int main()
{
    edoraRoot = fs::current_path() / "EDORA_DRIVES";

    edora::DriverManager drivers;
    drivers.initialize();

    filesystemInit();
    kernelInit();

    if (!loginSystem())
    {
        cout << "Login failed.\n";
        return 1;
    }

    shellStart();

    while (running)
    {
        shellLoop();
    }

    kernelShutdown();
    return 0;
}