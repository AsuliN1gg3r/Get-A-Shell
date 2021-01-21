#include "ServerConnection.h"

std::string ServerConnection::_serverAddress = "http://192.168.1.130";

std::string ServerConnection::extractSessionId(http::Response response)
{
    for (auto &header : response.headers)
    {
        std::size_t pos = header.find("sessionId=");
        if (pos < header.size())
        {
            return header.substr(pos + 10);
        }
    }
    return std::string();
}

ConnectionHandler* ServerConnection::run(void)
{
    try
    {
        while (true)
        {
            http::Request request(ServerConnection::_serverAddress);
            http::Response response = request.send("GET", "", { "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)" });
            std::cout << std::string(response.body.begin(), response.body.end()) << std::endl;
            std::string sessionId = extractSessionId(response);
            response = request.send("POST", std::string(response.body.begin(), response.body.end()), { "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)", "Cookie: sessionID=" + sessionId });
            Sleep(5000);
        }
    }
    catch (...)
    {
        Log::log("Conection with Server Failed.");
        return nullptr;
    }
}
