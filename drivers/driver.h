#ifndef EDORA_DRIVER_H
#define EDORA_DRIVER_H

#include <string>
#include <vector>

namespace edora {

struct DriverStatus {
    std::string name;
    bool online = false;
    std::string detail;
};

class DriverManager {
public:
    DriverManager();
    void initialize();
    void showStatus() const;
    void attach(const std::string& name, const std::string& detail, bool online = true);
    const std::vector<DriverStatus>& status() const;

private:
    std::vector<DriverStatus> drivers_;
};

} // namespace edora

#endif
