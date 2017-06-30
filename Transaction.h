#ifndef NETLIB_NETLIBSQL_H
#define NETLIB_NETLIBSQL_H

#include <Poco/Format.h>
#include <pqxx/connection.hxx>
#include <pqxx/transaction.hxx>

#include "Logger.h"
#include "SqlFormat.h"

namespace db {

struct Func {
    static const char* AddBook;
    static const char* DelBook;
    static const char* GetBooks;
    static const char* GetAuthors;
    static const char* GetBooksAnum;
};

class Transaction
{
    pqxx::connection connection;
    pqxx::work txn;

    template <class T>
    T execute(const std::string& sql);

public:
    Transaction();

    virtual ~Transaction() {}

    template <class T, class... Args>
    T call(const std::string& func, Args... args)
    {
        return execute<T>(Poco::format("SELECT %s(%s);", func, sqlprint(args...)));
    }

    void commit();
};

//-----------------------------------------------------------------------------------------

template <class T>
T resultsTo(const pqxx::result& results);

template <class T>
T Transaction::execute(const std::string& sql)
{
    try
    {
        Info("Sql: %s", sql);
        pqxx::result res = txn.exec(sql);
        return resultsTo<T>(res);
    }
    catch (pqxx::unique_violation& e)
    {
        throw;
    }
    catch (pqxx::sql_error& e)
    {
        Error("execute: %s. SQL: %s", std::string(e.what()), sql);
        throw;
    }
}

} // namespace db

#endif //NETLIB_NETLIBSQL_H
