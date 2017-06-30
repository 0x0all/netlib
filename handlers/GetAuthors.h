#ifndef NETLIB_GETAUTHORS_H
#define NETLIB_GETAUTHORS_H

#include "RequestHandler.h"

class GetAuthors : public RequestHandler
{
    GetAuthors(){};

    void getAuthors(const std::string& book, Poco::Net::HTTPServerResponse& resp);

public:
    static Poco::Net::HTTPRequestHandler* create();

    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp);
};

#endif //NETLIB_GETAUTHORS_H
