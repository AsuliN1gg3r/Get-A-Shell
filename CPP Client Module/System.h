#pragma once
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <io.h>

#pragma comment(lib, "urlmon.lib")

class System
{
	static int _argc;
	static char** _argv;
	static bool _isSystemAdmin;

public:
	static const bool checkForArgument(const std::string arg);
	static void setArguments(const int argc, char** argv) { System::_argc = argc; System::_argv = argv; }
	static void setIsSystemAdmin(const bool isSystemAdmin) { System::_isSystemAdmin = isSystemAdmin; }
	static const bool getIsSystemAdmin() { return System::_isSystemAdmin; }
	static const bool fileExist(const std::string path);
	static const bool createProcess(std::string command);
	static const bool downloadFile(const std::wstring url, const std::wstring path);
};