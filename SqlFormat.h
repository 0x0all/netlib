#ifndef NETLIB_SQLFORMAT_H
#define NETLIB_SQLFORMAT_H

#include <string>

template <class T>
std::string fmttype(const T& t);

template <>
std::string fmttype<int>(const int&);
template <>
std::string fmttype<double>(const double&);
template <>
std::string fmttype<std::string>(const std::string&);
template <>
std::string fmttype<std::vector<std::string> >(const std::vector<std::string>&);

template <class T>
std::string fmtstr(const T& t)
{
    return fmttype<T>(t);
}

template <class T, class... Args>
std::string fmtstr(const T& t, Args... args)
{
    return fmttype<T>(t) + ',' + fmtstr(args...);
}

template <class... Args>
inline std::string sqlprint(Args... args)
{
    return fmtstr(args...);
}

#endif //NETLIB_SQLFORMAT_H
