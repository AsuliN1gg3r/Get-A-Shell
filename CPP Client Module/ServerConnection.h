#pragma once
#include <iostream>

#include "HTTPRequest.hpp"

class ServerConnection
{
	static std::string _serverAddress;

public:
	static const bool run(void);
};