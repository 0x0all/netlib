#ifndef NETLIB_HANDLERFACTORY_H
#define NETLIB_HANDLERFACTORY_H

#include <map>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

class HandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
    typedef Poco::Net::HTTPRequestHandler* (*HandlerCreator)();

    static std::map<std::string, HandlerCreator> _handlers;
    static Poco::Net::HTTPRequestHandler* getHandler(const std::string& func);

public:
    virtual Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

    // Warning: calling this function after starting a ServerApplication causes assertion failure!
    static void Register(const std::string& func, const HandlerCreator& creator);
};

#endif //NETLIB_HANDLERFACTORY_H
