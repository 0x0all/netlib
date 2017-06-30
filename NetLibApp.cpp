#include <Poco/Net/HTTPServer.h>
#include <Poco/Process.h>
#include <Poco/Util/IntValidator.h>
#include <iostream>
#include <signal.h>

#include "HandlerFactory.h"
#include "Logger.h"
#include "NetLibApp.h"

#include "AddBook.h"
#include "DelBook.h"
#include "GetAuthors.h"
#include "GetBooks.h"
#include "GetBooksAnum.h"
#include "HttpPerf.h"

using namespace Poco::Net;
using namespace Poco::Util;

void signalHandler(int)
{
    Poco::Util::ServerApplication::terminate();
}

void NetLibApp::defineOptions(Poco::Util::OptionSet& options)
{
    // default options
    Poco::Util::LayeredConfiguration& config = Poco::Util::Application::instance().config();
    config.setInt("port", 8080);
    config.setString("dbuser", "netlibuser");
    config.setString("dbpassword", "123");
    config.setString("dbname", "netlib");
    config.setString("dbhost", "127.0.0.1");

    Application::defineOptions(options);
    options.addOption(
        Option("port", "p", "Port for incoming requests")
            .argument("value")
            .binding("port"));
}

void NetLibApp::initialize(Application& app)
{
    signal(SIGINT, signalHandler);

    HandlerFactory::Register("/add_book", &AddBook::create);
    HandlerFactory::Register("/del_book", &DelBook::create);
    HandlerFactory::Register("/get_books", &GetBooks::create);
    HandlerFactory::Register("/get_authors", &GetAuthors::create);
    HandlerFactory::Register("/get_books_anum", &GetBooksAnum::create);
    HandlerFactory::Register("/perf", &HttpPerf::create);

    ServerApplication::initialize(app);
}

int NetLibApp::main(const std::vector<std::string>&)
{
    Poco::Util::LayeredConfiguration& config = Poco::Util::Application::instance().config();

    Info("Start NetLib server at %i", config.getInt("port"));
    HTTPServer s(new HandlerFactory, ServerSocket(config.getInt("port")), new HTTPServerParams);
    s.start();
    waitForTerminationRequest();
    s.stop();
    Info("Stop NetLib server");

    return 0;
}

POCO_SERVER_MAIN(NetLibApp);
