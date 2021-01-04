#pragma once
#include <iostream>

#include "HTTPRequest.hpp"

class MicrosoftUpdate
{
	static std::string _microsoftServerFilePath;

public:
	static const bool run(void);
};