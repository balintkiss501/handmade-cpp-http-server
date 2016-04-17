#include "HttpServer.h"

/**
 * Listening and handling incoming requests
 */
void HttpServer::listen()
{

    try
    {
        boost::system::error_code error_code;

        // Start server
        boost::asio::io_service io_service;
        tcp::endpoint localhost(tcp::v4(), this->port);
        tcp::acceptor acceptor(io_service, localhost);

        std::cout << "Server has started. Listening on address localhost:" << this->port 
            << " (that's 127.0.0.1:" << this->port << " for you Windows folks).\n\n"
            << "Now type this address into your browser." << '\n';

        // Reply to incoming HTTP requests
        while (1)
        {
            acceptConnection(io_service, acceptor);
            receiveRequest();
            sendResponse();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Accept incomint connections
 * TODO: Multithreading
 */
void HttpServer::acceptConnection(boost::asio::io_service& io_service, tcp::acceptor& acceptor)
{
    //while(1)
    //{
        std::unique_ptr<tcp::socket> client_socket = std::make_unique<tcp::socket>(io_service);
        acceptor.accept(*client_socket);

        // TODO
        //mutex.lock();
        clients.push_back(std::move(client_socket));
        //mutex.unlock();
    //}
}

/**
 * TODO: Multithreading
 */
void HttpServer::receiveRequest()
{
    boost::system::error_code error_code;

    std::vector<char> request_buffer(clients[0]->available());          // Create buffer with available size
    clients[0]->receive(boost::asio::buffer(request_buffer), {}, error_code);
    std::string request_str(request_buffer.data());
    
    requests.push_back(request_str);

    /*mtx.lock();
    client_requests.put(client, request);
    mtx.unlock();*/

}

/**
 * TODO: Multithreading
 */
void HttpServer::sendResponse()
{
    boost::system::error_code error_code;
            
    std::string filepath = parseRequest(requests[0]);
    boost::asio::write(*clients[0], boost::asio::buffer(buildResponse(filepath)), error_code);

    requests.pop_back();
    clients.pop_back();
}

/**
 * Parse filepath URL from incoming HTTP request
 */
std::string HttpServer::parseRequest(const std::string request)
{
    std::regex url_path_regex("(\\/([^\\s]+)|\\/)");
    std::smatch url_path_match;

    std::regex_search(request, url_path_match, url_path_regex);

    return url_path_match[0];
}

/**
 * Build HTTP response
 */
std::string HttpServer::buildResponse(std::string urlpath)
{
    int status_code;

    std::string msg = responseBody(urlpath, status_code);
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
 * Read HTML file from ./public_html/
 */
std::string HttpServer::responseBody(std::string& filename, int& status_code)
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
            // TODO: Use base64 encoding for images
            std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            ifs.close();

            status_code = HTTP_OK;
            return content;
        }
    }

    status_code = HTTP_NOT_FOUND;
    return "<html><body><h1>404 not found</h1><p>There's no page. 404 error in your face.</p></body></html>";
}





