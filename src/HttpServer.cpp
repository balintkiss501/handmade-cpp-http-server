#include "HttpServer.h"

HttpServer::HttpServer(int port)
{
    this->port = port;
}

/**
 * Parse filepath URL from incoming HTTP request
 */
std::string HttpServer::parse_request(tcp::socket &socket)
{
    boost::system::error_code error_code;

    std::regex url_path_regex("(\\/([^\\s]+)|\\/)");
    std::smatch url_path_match;

    std::vector<char> request_buffer(1024);
    socket.receive(boost::asio::buffer(request_buffer), {}, error_code);
    std::string request_str(request_buffer.data());
    std::regex_search(request_str, url_path_match, url_path_regex);

    return url_path_match[0];
}

/**
 * Read HTML file from ./public_html/
 */
std::string HttpServer::response_body(std::string filename, int &status_code)
{
    // TODO: This is a quick fix
    if ("/." != filename || "/.." != filename)
    {
        if ("/" == filename)
        {
            filename = "/index.html";
        }
        
        std::string filepath = "public_html" + filename;
        std::ifstream ifs(filepath.c_str());
        if (ifs)
        {
            std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            ifs.close();

            status_code = HTTP_OK;
            return content;
        }
    }

    status_code = HTTP_NOT_FOUND;
    return "<html><body><h1>404 not found</h1><p>There's no page. 404 error in your face.</p></body></html>";
}

/**
 * Build HTTP response
 */
std::string HttpServer::build_response(std::string urlpath)
{
    int status_code;

    std::string msg = response_body(urlpath, status_code);
    std::string message = "HTTP/1.0 ";
    message += std::to_string(status_code);

    switch(status_code)
    {
        case HTTP_OK:
            message += " OK\r\n";
            break;
        case HTTP_NOT_FOUND:
            message += " Not Found\r\n";
            break;
        default:
            message += " What?\r\n";
    }

    message += "Server: Handmade C++ HTTP Server\r\n";
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
 * Listening and handling incoming requests
 */
void HttpServer::listen()
{

    try
    {
        // Start server
        boost::asio::io_service io_service;
        tcp::endpoint localhost(tcp::v4(), this->port);
        tcp::acceptor acceptor(io_service, localhost);

        std::cout << "Server has started. Listening on address localhost:" << this->port 
            << " (that's 127.0.0.1:" << this->port << " for you Windows folks).\n\n"
            << "Now type this address into your browser." << std::endl;

        // Reply to incoming HTTP requests
        while (1)
        {
            boost::system::error_code error_code;
            
            // Accept connection
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            // Send HTTP response
            std::string filepath = parse_request(socket);
            boost::asio::write(socket, boost::asio::buffer(build_response(filepath)), error_code);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
