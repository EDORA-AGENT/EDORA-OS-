#ifndef EDORA_LOGIN_H
#define EDORA_LOGIN_H

#include "../edora.h"

bool loginSystem();
void logoutUser();
void changePassword();
bool createAccount();

string getCurrentUser();
bool isLoggedIn();
bool verifyCurrentPassword();
#endif