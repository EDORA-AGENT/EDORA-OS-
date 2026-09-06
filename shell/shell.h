#ifndef EDORA_SHELL_H
#define EDORA_SHELL_H

void shellStart();
void shellLoop();

void showPrompt();
void executeCommand(const std::string& command);

#endif