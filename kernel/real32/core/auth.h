#ifndef EDORA_AUTH_H
#define EDORA_AUTH_H

enum PermissionLevel
{
    PERMISSION_GUEST = 0,
    PERMISSION_USER = 1,
    PERMISSION_ADMIN = 2,
    PERMISSION_KERNEL = 3
};

void auth_init();
bool auth_login();
PermissionLevel auth_permission();
const char* auth_username();
const char* auth_permission_name();

#endif
