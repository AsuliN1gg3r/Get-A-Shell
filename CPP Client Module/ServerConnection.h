#pragma once
#include <iostream>
#include <time.h>

#include "HTTPRequest.hpp"
#include "ConnectionHandler.h"
#include "Log.h"

class ServerConnection : public ConnectionHandler
{
	static std::string _serverAddress;

public:
	ConnectionHandler* run(void);
};