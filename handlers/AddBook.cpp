#include <Poco/StringTokenizer.h>

#include "AddBook.h"
#include "HandlerFactory.h"
#include "Logger.h"
#include "Transaction.h"

using namespace Poco;
using namespace Poco::Net;

namespace {

std::vector<std::string> parseAuthors(const std::string& param)
{
    StringTokenizer toks(param, ",", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
    std::vector<std::string> rv(std::begin(toks), std::end(toks));
    return rv;
}

} // namespace

HTTPRequestHandler* AddBook::create()
{
    return new AddBook();
}

void AddBook::addBook(const std::string& book, const std::vector<std::string>& authors, Poco::Net::HTTPServerResponse& resp)
{
    try
    {
        db::Transaction txn;
        int bid = txn.call<int>(db::Func::AddBook, book, authors);
        txn.commit();
        Info(" Book '%s' added, bid=%i", book, bid);
        send(resp, HTTPResponse::HTTP_OK, "Book added\n");
    }
    catch (pqxx::unique_violation& e)
    {
        Error("Book already exists!");
        send(resp, HTTPResponse::HTTP_NOT_ACCEPTABLE, "Book already exists!\n");
    }
    catch (pqxx::pqxx_exception& e)
    {
        Error(std::string(e.base().what()));
        send(resp, HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        throw;
    }
}

void AddBook::handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
{
    URI uri(req.getURI());

    std::string book = getParam(uri.getQueryParameters(), HttpParam::Book);
    std::vector<std::string> authors = parseAuthors(getParam(uri.getQueryParameters(), HttpParam::Authors));

    if (book.empty() || authors.empty())
        send(resp, HTTPResponse::HTTP_BAD_REQUEST, "Bad request!\n");
    else
        addBook(book, authors, resp);
}
