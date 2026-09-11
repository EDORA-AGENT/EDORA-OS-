#include "../edora.h"
#include "../login/login.h"

#include <cstdint>
#include <iostream>

using namespace std;

void debugApp()
{
    error_code statusError;
    uintmax_t fileBytes = 0;
    size_t fileCount = 0;
    size_t directoryCount = 0;

    if (fs::exists(currentPath, statusError))
    {
        for (const auto& entry : fs::recursive_directory_iterator(currentPath, statusError))
        {
            if (entry.is_directory(statusError))
            {
                ++directoryCount;
            }
            else if (entry.is_regular_file(statusError))
            {
                ++fileCount;
                fileBytes += entry.file_size(statusError);
            }
        }
    }

    cout << "\n============================================\n";
    cout << "              EDORA DEBUG APP\n";
    cout << "============================================\n";
    cout << "Version       : " << EDORA_VERSION << "\n";
    cout << "Kernel        : " << KERNEL_VERSION << "\n";
    cout << "Shell         : " << SHELL_VERSION << "\n";
    cout << "User          : " << getCurrentUser() << "\n";
    cout << "Mode          : " << (isRoot ? "ROOT" : "USER") << "\n";
    cout << "Drive         : " << currentDrive << ":\n";
    cout << "Current path  : " << currentPath << "\n";
    cout << "Path exists   : " << (fs::exists(currentPath, statusError) ? "yes" : "no") << "\n";
    cout << "Directories   : " << directoryCount << "\n";
    cout << "Files         : " << fileCount << "\n";
    cout << "File bytes    : " << fileBytes << "\n";
    cout << "Status        : " << (statusError ? "filesystem warning" : "OK") << "\n";
    cout << "============================================\n";
}
