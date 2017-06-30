#ifndef NETLIBAPP_H
#define NETLIBAPP_H

#include <Poco/Util/ServerApplication.h>

class NetLibApp : public Poco::Util::ServerApplication
{
public:
    NetLibApp() {}
    ~NetLibApp() {}

    void defineOptions(Poco::Util::OptionSet& options) override;
    void initialize(Application& app) override;

    int main(const std::vector<std::string>& args) override;
};

#endif // NETLIBAPP_H
