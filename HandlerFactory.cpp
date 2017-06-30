#include <cassert>

#include <Poco/Util/Application.h>

#include "HandlerFactory.h"
#include "Logger.h"

std::map<std::string, HandlerFactory::HandlerCreator> HandlerFactory::_handlers;

// I do not use any synchronization here because for read-only structure it is not necessary
// and waste of CPU
Poco::Net::HTTPRequestHandler* HandlerFactory::getHandler(const std::string& func)
{
    auto found = _handlers.find(func);
    if (found != std::end(_handlers))
        return found->second();

    Error("Function '%s' not found!", func);
    return nullptr;
}

void HandlerFactory::Register(const std::string& func, const HandlerCreator& creator)
{
    // One cannot change _handlers after ServerApplication started!
    assert(!Poco::Util::Application::instance().initialized());

    Info("Register function '%s'", func);
    _handlers[func] = creator;
}

Poco::Net::HTTPRequestHandler* HandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
    Info("Request URI: %s", request.getURI());
    std::string func = request.getURI().substr(0, request.getURI().find('?'));
    return HandlerFactory::getHandler(func);
}
