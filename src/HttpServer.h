#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <boost/asio.hpp>

// HTTP response codes
const int HTTP_OK = 200;
const int HTTP_NOT_FOUND = 404;

using boost::asio::ip::tcp;

class HttpServer
{
    private:
        int port;

        std::string parse_request(tcp::socket &socket, boost::system::error_code &error_code);
        std::string build_response(std::string urlpath);
        std::string response_body(std::string filename, int &status_code);

    public:
        HttpServer(int port);
        void listen();
};

#endif
