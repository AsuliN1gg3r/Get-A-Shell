#pragma once
#include <iostream>

class System
{
	static int _argc;
	static char** _argv;
	static bool _isSystemAdmin;

public:
	static const bool checkForArgument(std::string arg);
	static void setArguments(const int argc, char** argv) { System::_argc = argc; System::_argv = argv; }
	static void setIsSystemAdmin(const bool isSystemAdmin) { System::_isSystemAdmin = isSystemAdmin; }
	static const bool getIsSystemAdmin() { return System::_isSystemAdmin; }

};