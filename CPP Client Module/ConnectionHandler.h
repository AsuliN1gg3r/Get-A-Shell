#pragma once
#include <iostream>

class ConnectionHandler
{
public:
	virtual ConnectionHandler* run(void) = 0;
};