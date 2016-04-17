#ifndef HTTP_SERVER_H_
#define HTTP_SERVER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <regex>
#include <boost/asio.hpp>

// HTTP response codes
const int HTTP_OK = 200;
const int HTTP_NOT_FOUND = 404;


using boost::asio::ip::tcp;

/**
 * TODO
 * - Make it multithreaded
 */
class HttpServer
{
    private:
        int port;
        std::vector<std::unique_ptr<tcp::socket>> clients;
        std::vector<std::string> requests;

        void acceptConnection(boost::asio::io_service& io_service, tcp::acceptor& acceptor);
        void receiveRequest();
        void sendResponse();

        std::string parseRequest(const std::string request);
        std::string buildResponse(std::string urlpath);
        std::string responseBody(std::string& filename, int& status_code);

    public:
        HttpServer(const int port) : port(port) {};
        void listen();
};

#endif  // HTTP_SERVER_H_
