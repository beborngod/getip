#include "ParceSocket.hxx"

std::string ParceSocket::getResponce(std::string const &ip, bool doArguments)
{
    asio::io_context io;
    asio::ip::tcp::resolver resolver(io);
    asio::ip::tcp::socket socket(io);

    asio::connect(socket, resolver.resolve(MAIN_API, "80")); //connect to socket

    std::string arguments = API_ARGUMENTS;

    if (doArguments)
        arguments += ip;

    http::request<http::string_body> req(http::verb::get, arguments, 11); //do request

    req.set(http::field::host, MAIN_API);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(socket, req); // gotten request

    std::string responce;

    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(socket, buffer, res);

    responce = beast::buffers_to_string(res.body().data()); // gotten responce 

    socket.shutdown(asio::ip::tcp::socket::shutdown_both); //close socket
    return responce;
}

std::string ParceSocket::getFieldFromJson(std::string const &json, std::string const &field)
{
    std::stringstream jsonEncoded(json);
    property_tree::ptree root;
    property_tree::read_json(jsonEncoded, root); // written data in root

    if (root.empty())
        return "No socket json found!";

    return root.get<std::string>(field);
}

void ParceSocket::showJson(std::string const &json)
{
    for (size_t i = 0; i != json.length(); ++i)
    {
        if (json[i] == ',')
            std::cout << '\n';
        else if (json[i] == '"' or json[i] == '{' or json[i] == '}')
            continue;
        else if (json[1 + i] == ':')
            std::cout << " ";
        else if ((json[i] == ':'))
            std::cout << json[i] << ' ';
        else
            std::cout << json[i];
    }
    std::cout << '\n';
}
