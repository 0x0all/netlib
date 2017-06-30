#include "GetAuthors.h"

#include "HandlerFactory.h"
#include "Logger.h"
#include "Transaction.h"

using namespace Poco;
using namespace Poco::Net;

HTTPRequestHandler* GetAuthors::create()
{
    return new GetAuthors();
}

void GetAuthors::getAuthors(const std::string& book, Poco::Net::HTTPServerResponse& resp)
{
    try
    {
        db::Transaction txn;
        std::vector<std::string> authors = txn.call<std::vector<std::string> >(db::Func::GetAuthors, book);
        if (authors.empty())
            send(resp, HTTPResponse::HTTP_NOT_FOUND, "Book not found\n");
        else
        {
            std::stringstream ss;
            for (auto a : authors)
                ss << a << std::endl;
            send(resp, HTTPResponse::HTTP_OK, ss.str());
        }
    }
    catch (pqxx::pqxx_exception& e)
    {
        Error(std::string(e.base().what()));
        send(resp, HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        throw;
    }
}

void GetAuthors::handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
{
    URI uri(req.getURI());

    std::string book = getParam(uri.getQueryParameters(), HttpParam::Book);
    if (book.empty())
        send(resp, HTTPResponse::HTTP_BAD_REQUEST);
    else
        getAuthors(book, resp);
}
