#pragma once
#include <iostream>
#include <Windows.h>

class Log
{
	static bool logging;
public:
	static void log(std::string msg);
	static void setLogging(bool state);
};