#pragma once
#include <iostream>
#include <time.h>

#include "ConnectionHandler.h"
#include "MicrosoftUpdate.h"
#include "Log.h"

class Wait : public ConnectionHandler
{
	ConnectionHandler* run(void);
};