#ifndef NETLIB_HTTPPERF_H
#define NETLIB_HTTPPERF_H

#include "RequestHandler.h"

class HttpPerf : public RequestHandler
{
    HttpPerf(){};

public:
    static Poco::Net::HTTPRequestHandler* create();

    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp);
};

#endif //NETLIB_HTTPPERF_H
