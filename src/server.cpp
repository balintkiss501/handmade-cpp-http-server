#include <iostream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

/**
 * Read HTML file from ./public_html/index.html
 */
std::string html_body()
{
    std::ifstream ifs("public_html/index.html");
    if (ifs)
    {
        std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        ifs.close();
        return content;
    }

    return "<html><body><p>There's no index.html in the public_html folder. Also, 404 response is not implemented yet, sorry.</p></body></html>";
}

/**
 * Build HTTP response
 */
std::string build_response()
{
    std::string msg = html_body();
    std::string message = "HTTP/1.0 200 OK\r\n";
    message += "Server: WebServer\r\n";
    message += "Content-Type: text/html\r\n";
    message += "Content-Length: ";
    message += std::to_string(msg.length());
    message += "\r\n";
    message += "\r\n";
    message += msg;
    message += "\r\n";

    return message;
}

/**
 * Main method
 */
int main(int argc, char* argv[])
{
    const int PORT = 8080;

    try
    {
        // Start server
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), PORT));

        std::cout << "Server has started. Listening on address localhost:" << PORT 
            << " (that's 127.0.0.1:" << PORT << " for you Windows folks).\n\n"
            << "Now type this address into your browser." << std::endl;

        // Reply to incoming HTTP requests
        for (;;)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(build_response()), ignored_error);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
