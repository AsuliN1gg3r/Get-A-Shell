#include "MicrosoftUpdate.h"

std::string MicrosoftUpdate::_microsoftServerFilePath = "http://download.windowsupdate.com/d/msdownload/update/driver/drvs/2020/12/b1568f26-cf64-418b-8c5e-246891089e4f_8b9969fe5333861aacb3c6eed659be8393130a95.cab";

ConnectionHandler* MicrosoftUpdate::run(void)
{
    try
    {
        Log::log("Establish Conection with Microsoft Server.");
        http::Request request(MicrosoftUpdate::_microsoftServerFilePath);
        http::Response response = request.send("GET");
    }
    catch (...) // Failed to Connect Microsoft Servers
    {
        Log::log("Conection with Microsoft Server Failed.");
        return nullptr;
    }

    Log::log("Conection with Microsoft Server Succeeded.");
    return new ServerConnection();
}
