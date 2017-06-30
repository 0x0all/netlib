#include <Poco/Format.h>

#include "SqlFormat.h"

template <>
std::string fmttype<int>(const int& i)
{
    return Poco::format("%i", i);
}

template <>
std::string fmttype<double>(const double& d)
{
    return Poco::format("%f", d);
}

template <>
std::string fmttype<std::string>(const std::string& str)
{
    return Poco::format("'%s'", str);
}

template <>
std::string fmttype<std::vector<std::string> >(const std::vector<std::string>& v)
{
    std::string rv("'{");
    for (size_t i = 0; i < v.size(); i++)
    {
        if (i > 0)
            rv += ",";
        rv += v[i];
    }
    rv += "}'";
    return rv;
}
