#include "HttpPerf.h"

#include "HandlerFactory.h"
#include "Logger.h"

using namespace Poco;
using namespace Poco::Net;

HTTPRequestHandler* HttpPerf::create()
{
    return new HttpPerf();
}

void HttpPerf::handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& resp)
{
    URI uri(req.getURI());
    // std::string book = getParam(uri.getQueryParameters(), HttpParam::Book);
    send(resp, HTTPResponse::HTTP_BAD_REQUEST, "OK");
}
