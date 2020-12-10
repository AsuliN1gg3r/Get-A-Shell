// Created by Eyal Asulin™

#pragma once

#include <iostream>
#include <WinSock2.h>
#include <Windows.h>


class Communicator
{
	SOCKET _sock;

public:
	Communicator();
	~Communicator();
	bool connectToServer(int PortNo, std::string IPAddress);
	bool sendMsg(std::string msg);

};