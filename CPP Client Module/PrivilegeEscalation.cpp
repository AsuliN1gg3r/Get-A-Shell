#include "PrivilegeEscalation.h"

// This function checks if the current process is run as system admin
const bool PrivilegeEscalation::systemAdminCheck(void)
{
    int exitCode = system("net session >nul 2>&1"); // This command require high-privileged user
    return !exitCode;
}
