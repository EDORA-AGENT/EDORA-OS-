#include "edora.h"
#include "login/login.h"
#include "filesystem/filesystem.h"

// ======================================================
//                    EDORA OS
//                    MAIN ENTRY
// ======================================================

bool running = true;
bool isRoot = false;

fs::path edoraRoot;
fs::path currentPath;

char currentDrive = 'C';

// ======================================================
//                         MAIN
// ======================================================

int main()
{
    edoraRoot = fs::current_path() / "EDORA_DRIVES";

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