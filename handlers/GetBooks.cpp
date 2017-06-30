#include "GetBooks.h"

#include "HandlerFactory.h"
#include "Logger.h"
#include "Transaction.h"

using namespace Poco;
using namespace Poco::Net;

HTTPRequestHandler* GetBooks::create()
{
    return new GetBooks();
}

void GetBooks::getBooks(const std::string& author, Poco::Net::HTTPServerResponse& resp)
{
    try
    {
        db::Transaction txn;
        std::vector<std::string> books = txn.call<std::vector<std::string> >(db::Func::GetBooks, author);
        if (books.empty())
            send(resp, HTTPResponse::HTTP_NOT_FOUND, "Author not found\n");
        else
        {
            std::stringstream ss;
            for (auto book : books)
                ss << book << std::endl;
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

void GetBooks::handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
{
    URI uri(req.getURI());

    std::string author = getParam(uri.getQueryParameters(), HttpParam::Author);
    if (author.empty())
        send(resp, HTTPResponse::HTTP_BAD_REQUEST);
    else
        getBooks(author, resp);
}
