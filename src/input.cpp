#include "input.hpp"
#include "logger.hpp"
#include "common.hpp"
#include <string>
#include <iostream>

using namespace baton;

// InputServer::InputServer(const int port_number, const Logger &logger)
//     : port_number(port_number), logger(logger){};

InputServer::InputServer(ServerOpts& server_opts):
    port_number(server_opts.server_port_number),
    logger(server_opts.logger),
    buffer(new char[server_opts.max_buffer_size]),
    read_size(server_opts.read_size)
{};

void InputServer::setup() {

  if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == ETIMEDOUT) {
    this->logger.error("Timed out when trying to acquire socket");
    exit(EXIT_FAILURE);
  }

  int opt = 1;
  if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt,
                 sizeof(opt))) {
    this->logger.error("Failed to set socket options");
    exit(EXIT_FAILURE);
  }

  this->logger.info("Finished setuping up the socket");
};

void InputServer::bind() {
  this->address.sin_family = AF_INET;
  this->address.sin_addr.s_addr = INADDR_ANY;
  this->address.sin_port = htons(this->port_number);

  size_t address_len = sizeof(this->address);
  if (::bind(this->server_fd, (struct sockaddr *)&this->address, address_len)) {
    this->logger.error("Failed to bind to port");
    exit(EXIT_FAILURE);
  }
  this->logger.info("Finished binding the socket");
}

void InputServer::listen() {
  if (::listen(this->server_fd, 3) < 0) {
    this->logger.error("Failed to bind to port");
    exit(EXIT_FAILURE);
  }
  this->logger.info("Listening on port " + to_string(this->port_number));
}

void InputServer::accept() {

  size_t address_len = sizeof(this->address);
  if ((this->new_socket =
           ::accept(this->server_fd, (struct sockaddr *)&this->address,
                    (socklen_t *)&address_len)) < 0) {
  }
}

void InputServer::stop(){

    close(this->new_socket);
    ::shutdown(this->server_fd, SHUT_RDWR);
    this->logger.info("Shutting down server");
}

void InputServer::read(){
    int valread;
    valread = ::read(this->new_socket, this->buffer, this->read_size);
    cout << this->buffer << endl;
}

void InputServer::write(const string& message){
    ::send(this->new_socket, &message, message.size(), 0);
    this->logger.info("Sent message back to the client");
}

void InputServer::start(){
    this->setup();
    this->bind();
    this->listen();
    this->accept();
}
