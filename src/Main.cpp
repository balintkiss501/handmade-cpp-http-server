#include <iostream>
#include "HttpServer.h"

const int DEFAULT_PORT = 8080;
const int UNALLOWED_PORT_BOUND = 1024;

/**
 * Main entrypoint of program
 */
int main(int argc, char *argv[])
{    
    // TODO: Command line arguments
    int port = DEFAULT_PORT;
    if (argc == 2)
    {
        int tmp_port = (int)(argv[1][0] - '0');

        if (tmp_port <= UNALLOWED_PORT_BOUND) {
            std::cerr << "Invalid port number! Must be over " << std::to_string(UNALLOWED_PORT_BOUND) << '\n';
            return EXIT_FAILURE;
        }
    }
    
    HttpServer server(port);
    server.listen();

    return EXIT_SUCCESS;
}
