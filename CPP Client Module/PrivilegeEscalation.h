#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>

#include "System.h"

class PrivilegeEscalation
{
public:
	static const bool run(void);
	static const bool systemAdminCheck(void);
};