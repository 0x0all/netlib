#ifndef NETLIB_GETBOOKS_H
#define NETLIB_GETBOOKS_H

#include "RequestHandler.h"

class GetBooks : public RequestHandler
{
    GetBooks(){};

    void getBooks(const std::string& author, Poco::Net::HTTPServerResponse& resp);

public:
    static Poco::Net::HTTPRequestHandler* create();

    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp);
};

#endif //NETLIB_GETBOOKS_H
