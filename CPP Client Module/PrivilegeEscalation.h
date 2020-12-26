#pragma once
#include <iostream>
#include <fstream>

#include "System.h"

class PrivilegeEscalation
{
public:
	const static bool run(void);
	const static bool systemAdminCheck(void);
};