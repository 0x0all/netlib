#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/Application.h>

#include "Logger.h"
#include "RequestHandler.h"

using namespace Poco;
using namespace Poco::Net;

const char* HttpParam::Book = "book";
const char* HttpParam::Authors = "authors";
const char* HttpParam::Author = "author";
const char* HttpParam::Anum = "num";

std::string RequestHandler::getParam(const URI::QueryParameters& params, const std::string& name)
{
    for (auto& it : params)
    {
        if (it.first == name)
            return it.second;
    }
    Error("Requester param '%s' not found!", name);
    return std::string("");
}

void RequestHandler::send(Poco::Net::HTTPServerResponse& resp, Poco::Net::HTTPResponse::HTTPStatus status,
    const std::string& data)
{
    resp.setStatus(status);
    resp.setContentType("text/html");
    resp.send() << data;
}
