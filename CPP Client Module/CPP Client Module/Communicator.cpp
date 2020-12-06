// Created by Eyal Asulin™
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Communicator.h"


Communicator::Communicator()
{
	// Create Socket
	this->_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_sock == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
}

Communicator::~Communicator()
{
	// Close Socket
	try
	{
		closesocket(this->_sock);
	}
	catch (...) {}
}

bool Communicator::connectToServer(int PortNo, std::string IPAddress)
{
	// Config socket address
	sockaddr_in target = { 0 };
	target.sin_port = htons(PortNo);
	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr(IPAddress.c_str());

	// Connecting to Server
	return connect(this->_sock, (sockaddr*)&target, sizeof(target)) != SOCKET_ERROR;
}

bool Communicator::sendMsg(std::string msg)
{
	return send(this->_sock, msg.c_str(), msg.size(), 0) != SOCKET_ERROR;
}


