#ifndef EDORA_FILESYSTEM_H
#define EDORA_FILESYSTEM_H

#include <filesystem>
#include <string>

#include "../edora.h"

void filesystemInit();
std::filesystem::path drivePath(char drive);
std::string getPath();
bool insideDrive(std::filesystem::path path);

void commandDrives();
void commandLs();
void commandCd();
void commandMkdir();
void commandTouch();
void commandRm();
void commandCat();
void createSystemFile(const std::filesystem::path& path, const std::string& content);
void createSystemFiles();
void writeBootLog();
#endif