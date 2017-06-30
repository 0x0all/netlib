#ifndef NETLIB_REQUESTHANDLER_H
#define NETLIB_REQUESTHANDLER_H

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/URI.h>

struct HttpParam {
    static const char* Book;
    static const char* Authors;
    static const char* Author;
    static const char* Anum;
};

class RequestHandler : public Poco::Net::HTTPRequestHandler
{
protected:
    RequestHandler(){};

    std::string getParam(const Poco::URI::QueryParameters& params, const std::string& name);

    void send(Poco::Net::HTTPServerResponse& resp, Poco::Net::HTTPResponse::HTTPStatus status,
        const std::string& data = "\n");
};

#endif //NETLIB_REQUESTHANDLER_H
