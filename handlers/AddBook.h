#ifndef NETLIB_ADDBOOK_H
#define NETLIB_ADDBOOK_H

#include "RequestHandler.h"

class AddBook : public RequestHandler
{
    AddBook(){};

    void addBook(const std::string& book, const std::vector<std::string>& authors, Poco::Net::HTTPServerResponse& resp);

public:
    static Poco::Net::HTTPRequestHandler* create();

    void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp);
};

#endif // NETLIB_ADDBOOK_H
