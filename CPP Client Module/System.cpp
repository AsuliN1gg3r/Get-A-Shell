#include "System.h"

// Initialize Class' Static Fields
int System::_argc = 0;
char** System::_argv = nullptr;
bool System::_isSystemAdmin = false;

// This function checks if an argument is given 
const bool System::checkForArgument(std::string arg)
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
