#include "../edora.h"
#include "kernel.h"

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>

using namespace std;

// ======================================================
//                    KERNEL INIT
// ======================================================

void kernelInit()
{
    cout << "\n";
    cout << "============================================\n";
    cout << "             EDORA KERNEL\n";
    cout << "============================================\n";

    cout << "EDORA-KERNEL " << KERNEL_VERSION << "\n";
    cout << "Initializing kernel...\n";

    cout << "[ OK ] Memory manager\n";
    cout << "[ OK ] Process manager\n";
    cout << "[ OK ] Virtual filesystem\n";
    cout << "[ OK ] System clock\n";
    cout << "[ OK ] Security manager\n";

    cout << "Kernel initialized successfully.\n";
    cout << "============================================\n";
    cout << "\n";
}

// ======================================================
//                  KERNEL SHUTDOWN
// ======================================================

void kernelShutdown()
{
    cout << "\n";
    cout << "EDORA-KERNEL: shutting down...\n";

    cout << "[ OK ] Stopping services\n";
    cout << "[ OK ] Saving system state\n";
    cout << "[ OK ] Unmounting virtual filesystem\n";

    cout << "EDORA-KERNEL stopped.\n";
}

// ======================================================
//                    KERNEL PANIC
// ======================================================

void kernelPanic()
{
    cout << "\n";
    cout << "================================================\n";
    cout << "                 KERNEL PANIC\n";
    cout << "================================================\n";

    cout << "\n";
    cout << "EDORA-KERNEL has encountered a fatal error.\n";
    cout << "\n";

    cout << "SYSTEM HALTED.\n";

    cout << "\n";
    cout << "Possible causes:\n";
    cout << " - Fatal system error\n";
    cout << " - Critical service failure\n";
    cout << " - Invalid kernel operation\n";

    cout << "\n";
    cout << "================================================\n";

    running = false;
}

// ======================================================
//                       REBOOT
// ======================================================

void rebootSystem()
{
    cout << "\n";
    cout << "EDORA-KERNEL: reboot requested.\n";

    cout << "Stopping services...\n";

    isRoot = false;

    currentDrive = 'C';
    currentPath = drivePath('C');

    cout << "Resetting kernel state...\n";
    cout << "Loading EDORA-KERNEL...\n";

    cout << "\n";
    cout << "EDORA OS restarted successfully.\n";
    cout << "\n";
}

// ======================================================
//                     SHUTDOWN
// ======================================================

void shutdownSystem()
{
    cout << "\n";
    cout << "EDORA-KERNEL: shutdown requested.\n";

    cout << "Stopping services...\n";
    cout << "Unmounting virtual filesystem...\n";
    cout << "Stopping shell...\n";

    cout << "\n";
    cout << "EDORA OS has been shut down.\n";

    running = false;
}