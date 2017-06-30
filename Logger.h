#ifndef NETLIB_LOG_H
#define NETLIB_LOG_H

#include <Poco/Util/ServerApplication.h>
#include <Poco/Format.h>

inline Poco::Logger& NetLibLogger()
{
    return Poco::Util::ServerApplication::instance().logger();
}

template <typename T>
inline void Debug(T&& t)
{
    NetLibLogger().debug(t);
}
template <typename... Args>
inline void Debug(Args... args)
{
    NetLibLogger().debug(Poco::format(args...));
}

template <typename T>
inline void Info(T&& t)
{
    NetLibLogger().information(t);
}
template <typename... Args>
inline void Info(Args... args)
{
    NetLibLogger().information(Poco::format(args...));
}

template <typename T>
inline void Warn(T&& t)
{
    NetLibLogger().warning(t);
}
template <typename... Args>
inline void Warn(Args... args)
{
    NetLibLogger().warning(Poco::format(args...));
}

template <typename T>
inline void Error(T&& t)
{
    NetLibLogger().error(t);
}
template <typename... Args>
inline void Error(Args... args)
{
    NetLibLogger().error(Poco::format(args...));
}

#endif //NETLIB_LOG_H
