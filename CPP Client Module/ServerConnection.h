#pragma once
#include <iostream>
#include <time.h>

#include "HTTPRequest.hpp"
#include "ConnectionHandler.h"
#include "Log.h"

class ServerConnection : public ConnectionHandler
{
	static std::string _serverAddress;
	std::string extractSessionId(http::Response response);

public:
	ConnectionHandler* run(void);
};