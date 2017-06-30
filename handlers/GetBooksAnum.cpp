#include "GetBooksAnum.h"
#include <Poco/NumberParser.h>

#include "HandlerFactory.h"
#include "Logger.h"
#include "Transaction.h"

using namespace Poco;
using namespace Poco::Net;

HTTPRequestHandler* GetBooksAnum::create()
{
    return new GetBooksAnum();
}

void GetBooksAnum::getBooksAnum(const std::string& anumstr, Poco::Net::HTTPServerResponse& resp)
{
    try
    {
        int anum = Poco::NumberParser::parse(anumstr);
        db::Transaction txn;
        std::vector<std::string> books = txn.call<std::vector<std::string> >(db::Func::GetBooksAnum, anum);
        std::stringstream ss;
        for (auto book : books)
            ss << book << std::endl;
        send(resp, HTTPResponse::HTTP_OK, ss.str());
    }
    catch (pqxx::pqxx_exception& e)
    {
        Error(std::string(e.base().what()));
        send(resp, HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        throw;
    }
    catch (Poco::SyntaxException& e)
    {
        send(resp, HTTPResponse::HTTP_BAD_REQUEST, "Bad request!\n");
        throw;
    }
}

void GetBooksAnum::handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
{
    URI uri(req.getURI());
    std::string anumstr = getParam(uri.getQueryParameters(), HttpParam::Anum);
    getBooksAnum(anumstr, resp);
}
