#include <iostream>
#include "HttpServer.h"

/**
 * Main entrypoint of program
 */
int main(int argc, char* argv[])
{
    // You can specify port numbers to use on the command line, although I haven't finished it yet.
    int port = 8080;
    if (argc == 2)
    {
        int tmp_port = (int)(argv[1][0] - '0');

        if (tmp_port < 1025) {
            std::cerr << "Invalid port number! Must be over 1024" << std::endl;
            return 1;
        }
    }
    
    HttpServer server(port);
    server.listen();

    return 0;
}
