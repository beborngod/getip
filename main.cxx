#include "ParceSocket.hxx"
#include <boost/program_options.hpp>

namespace opt = boost::program_options;

int main(int argc, char const *argv[])
{
    opt::options_description desc("All options");

    std::string ipAddress;
    std::string field;

    desc.add_options()
    ("help,h", "produce help messange")
    ("domain,d", opt::value<std::string>(&ipAddress)/* ->default_value("example.com") */, "Get IP from domain")
    ("query,q", opt::value<std::string>(&ipAddress)/* ->default_value("myip") */, "IP address or Domain for parce")
    ("field,f", opt::value<std::string>(&field)/* ->default_value("myfield") */, "Json field for current parce");

    opt::variables_map vm;

    opt::store(opt::parse_command_line(argc, argv, desc), vm);

    opt::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << '\n';
        return 1;
    }

    else if(vm.count("domain"))
    {
        std::string json = ParceSocket::getResponce(ipAddress, 1);
        std::cout<<"IP : " << ParceSocket::getFieldFromJson(json, std::string("query")) << '\n';

        return 0;
    }

    else if (ipAddress.empty())
    {
        std::string json =  ParceSocket::getResponce("");

        ParceSocket::showJson(json);
    }
    
    else if (vm.count("query") and field.empty())
    {
        std::string json = ParceSocket::getResponce(ipAddress, 1);

        ParceSocket::showJson(json);
    }
    else if (vm.count("query") and not field.empty())
    {
        std::string json = ParceSocket::getResponce(ipAddress, 1);
        std::cout << ParceSocket::getFieldFromJson(json, field) << '\n';
    }

    return 0;
}
