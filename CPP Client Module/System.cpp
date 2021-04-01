#include "System.h"

// Initialize Class' Static Fields
int System::_argc = 0;
char** System::_argv = nullptr;
bool System::_isSystemAdmin = false;

// This function checks if an argument is given 
const bool System::checkForArgument(const std::string arg)
{
	if (System::_argc == 1)
	{
		return false;
	}
	for (int i = 1; i < System::_argc; i++)
	{
		if (!strcmp(System::_argv[i], arg.c_str()))
		{
			return true;
		}
	}
    return false;
}

// This function checks if required file exists
const bool System::fileExist(const std::string path)
{
	return (_access(path.c_str(), 0) != -1);
}


// This function creates system process (not sub-process)
const bool System::createProcess(std::string command)
{
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	LPSTR s = const_cast<char*>(command.c_str());
 
	if (!CreateProcessA(NULL, s, NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &si, &pi))
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return false;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return true;
}

const bool System::downloadFile(const std::wstring url, const std::wstring path)
{
	int code = URLDownloadToFile(NULL, url.c_str(), path.c_str(), 0, NULL);

	return code == S_OK;
}
