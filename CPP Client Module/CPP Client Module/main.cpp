#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include "Communicator.h"
#include "WSAInitializer.h"
#include "rsa.h"

// For Testing Purpose

int main(void)
{

	/*try
	{
		WSAInitializer wsaInit;
		Communicator c1;
		c1.connectToServer(8876, "127.0.0.1");
		c1.sendMsg("Testing BlaBla...");
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}*/
	RSA rsa;

    std::string s = "bla bla bla";
    std::cout << s << std::endl;

	int *enc = RSA::encrypt(rsa.getPublicKey(), s);
    
	std::cout << rsa.decrypt(enc) << std::endl;

	system("PAUSE");
	return 0;
}