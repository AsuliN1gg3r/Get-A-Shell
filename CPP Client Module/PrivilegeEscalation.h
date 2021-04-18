#pragma once
#include <iostream>
#include <Windows.h>

#include "System.h"

class PrivilegeEscalation
{
public:
	static const bool run(void);
	static const bool systemAdminCheck(void);
};