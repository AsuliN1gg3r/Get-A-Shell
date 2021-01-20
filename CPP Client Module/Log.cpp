#include "Log.h"

bool Log::logging = false;

void Log::log(std::string msg)
{
	if (Log::logging)
	{
		std::cout << "LOG:~$ " << msg << std::endl << std::endl;
	}
}

void Log::setLogging(bool state)
{
	Log::logging = state;
	if (state)
	{
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	}
	else
	{
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}
}
