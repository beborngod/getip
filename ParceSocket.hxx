#pragma once

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>

const static std::string MAIN_API = "ip-api.com";
const static std::string API_ARGUMENTS = "/json/";

namespace http = boost::beast::http;

using namespace boost;

class ParceSocket
{
public:
    static std::string getResponce(std::string const &ip, bool doArguments = false);
    static std::string getFieldFromJson(std::string const &json,std::string const &field);
    static void showJson(std::string const &json);
};
