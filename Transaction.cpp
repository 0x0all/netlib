#include <Poco/Util/Application.h>

#include "Logger.h"
#include "Transaction.h"

using namespace Poco;

namespace db {

const char* Func::AddBook = "add_book";
const char* Func::DelBook = "del_book";
const char* Func::GetBooks = "get_books";
const char* Func::GetAuthors = "get_authors";
const char* Func::GetBooksAnum = "get_books_anum";

namespace {
    std::string connectionParams()
    {
        Poco::Util::LayeredConfiguration& cfg = Poco::Util::Application::instance().config();
        return Poco::format("user=%s password=%s dbname=%s hostaddr=%s",
            cfg.getString("dbuser"), cfg.getString("dbpassword"),
            cfg.getString("dbname"), cfg.getString("dbhost"));
    }
}

template <>
int resultsTo<int>(const pqxx::result& results)
{
    if (results.at(0).at(0).is_null())
        return -1;
    return results.at(0).at(0).as<int>();
}

template <>
std::vector<std::string> resultsTo<std::vector<std::string> >(const pqxx::result& results)
{
    std::vector<std::string> rv;
    for (const auto& s : results)
        rv.push_back(s[0].as<std::string>());
    return rv;
}

//----------------------------------------------------------------------------------

Transaction::Transaction()
    : connection(connectionParams())
    , txn(connection)
{
}

void Transaction::commit()
{
    txn.commit();
}

} // namespace db
