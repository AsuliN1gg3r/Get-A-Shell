#pragma once
#include <iostream>
#include <time.h>

#include "HTTPRequest.hpp"
#include "ConnectionHandler.h"
#include "Log.h"
#include "System.h"


class ServerConnection : public ConnectionHandler
{
	typedef struct Request
	{
		std::string sessionId;
		std::string command;
	} Request;

	typedef struct Response
	{
		std::string sessionId;
		std::string content;
	} Response;

	static std::string _serverAddress;
	std::string extractSessionId(http::Response request);
	ServerConnection::Request* parsingRequest(http::Response request);
	ServerConnection::Response handleRequest(ServerConnection::Request* request);

public:
	ConnectionHandler* run(void);
};