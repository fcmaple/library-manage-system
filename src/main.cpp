
#include "server.hpp"

int main(int argc,char** argv){

    int port = atoi(argv[1]);
    std::shared_ptr<socketServer> server(new socketServer(port));
    
    server->run();
}