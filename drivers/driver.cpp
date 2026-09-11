#include "driver.h"

#include <iostream>

namespace edora {

DriverManager::DriverManager() {
    attach("VGA Driver", "Text mode 80x25", true);
    attach("Keyboard Driver", "PS/2 polling input", true);
    attach("Filesystem Driver", "Virtual drive C:/D:/E:", true);
    attach("Network Driver", "Ping and diagnostics", true);
    attach("Security Driver", "User auth and root checks", true);
}

void DriverManager::initialize() {
    std::cout << "\n";
    std::cout << "============================================\n";
    std::cout << "              DRIVER INITIALIZATION\n";
    std::cout << "============================================\n";
    for (const auto& driver : drivers_) {
        std::cout << "[ OK ] " << driver.name << "\n";
    }
    std::cout << "All drivers initialized successfully.\n";
    std::cout << "============================================\n\n";
}

void DriverManager::showStatus() const {
    std::cout << "\n";
    std::cout << "============================================\n";
    std::cout << "               DRIVER STATUS\n";
    std::cout << "============================================\n";
    for (const auto& driver : drivers_) {
        std::cout << "[" << (driver.online ? "OK" : "OFF") << "] "
                  << driver.name << " - " << driver.detail << "\n";
    }
    std::cout << "============================================\n";
}

void DriverManager::attach(const std::string& name, const std::string& detail, bool online) {
    drivers_.push_back({name, online, detail});
}

const std::vector<DriverStatus>& DriverManager::status() const {
    return drivers_;
}

} // namespace edora
