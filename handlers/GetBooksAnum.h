#ifndef NETLIB_GETBOOKSANUM_H
#define NETLIB_GETBOOKSANUM_H

#include "RequestHandler.h"

class GetBooksAnum : public RequestHandler
{
    GetBooksAnum() {}

    void getBooksAnum(const std::string& anumstr, Poco::Net::HTTPServerResponse& resp);

public:
    static Poco::Net::HTTPRequestHandler* create();

    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp);
};

#endif //NETLIB_GETBOOKSANUM_H
