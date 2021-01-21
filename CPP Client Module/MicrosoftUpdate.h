#pragma once
#include <iostream>

#include "HTTPRequest.hpp"
#include "ConnectionHandler.h"
#include "Log.h"
#include "ServerConnection.h"

class MicrosoftUpdate : public ConnectionHandler
{
	static std::string _microsoftServerFilePath;

public:
	ConnectionHandler* run(void);
};