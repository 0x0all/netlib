#ifndef NETLIB_DELBOOK_H
#define NETLIB_DELBOOK_H

#include "RequestHandler.h"

class DelBook : public RequestHandler
{
    DelBook(){};

    void delBook(const std::string& book, Poco::Net::HTTPServerResponse& resp);

public:
    static Poco::Net::HTTPRequestHandler* create();

    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp);
};

#endif // NETLIB_DELBOOK_H
