#include "input.hpp"
#include "logger.hpp"


using namespace baton;

InputServer::InputServer(const int port_number, const Logger& logger):port_number(port_number),logger(logger){};

void InputServer::setup(){

    if((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == ETIMEDOUT){
        this->logger.error("Timed out when trying to acquire socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if(setsockopt(this->server_fd, SOL_SOCKET,SO_REUSEADDR, &opt, sizeof(opt))){
        this->logger.error("Failed to set socket options");
        exit(EXIT_FAILURE);
    }

    this->logger.info("Finished setuping up the server");
};


