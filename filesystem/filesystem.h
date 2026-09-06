#ifndef EDORA_FILESYSTEM_H
#define EDORA_FILESYSTEM_H

#include <string>

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
#include "../edora.h"

void createSystemFile(const fs::path& path, const string& content);
void createSystemFiles();
void writeBootLog();
#endif