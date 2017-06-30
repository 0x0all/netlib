#include <Poco/StringTokenizer.h>

#include "DelBook.h"
#include "HandlerFactory.h"
#include "Logger.h"
#include "Transaction.h"

using namespace Poco;
using namespace Poco::Net;

HTTPRequestHandler* DelBook::create()
{
    return new DelBook();
}

void DelBook::delBook(const std::string& book, Poco::Net::HTTPServerResponse& resp)
{
    try
    {
        db::Transaction txn;
        int bid = txn.call<int>(db::Func::DelBook, book);
        txn.commit();
        if (bid > 0)
        {
            Info(" Book '%s' deleted, bid=%i", book, bid);
            send(resp, HTTPResponse::HTTP_OK, "Deleted\n");
        }
        else
            send(resp, HTTPResponse::HTTP_NOT_FOUND, "Book not found\n");
    }
    catch (pqxx::pqxx_exception& e)
    {
        Error(std::string(e.base().what()));
        send(resp, HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        throw;
    }
}

void DelBook::handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
{
    URI uri(req.getURI());

    std::string book = getParam(uri.getQueryParameters(), HttpParam::Book);
    if (book.empty())
        send(resp, HTTPResponse::HTTP_BAD_REQUEST);
    else
        delBook(book, resp);
}
