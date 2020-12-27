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

// This function returns the required environment variable value
const std::string System::getTempPath(void)
{
	TCHAR tcValue[MAX_PATH];
	GetEnvironmentVariable(_T("TEMP"), tcValue, MAX_PATH);

	return std::string(tcValue);
}

// This function checks if required file exists
const bool System::fileExist(const std::string path)
{
	return (_access(path.c_str(), 0) != -1);
}
