#include "input.hpp"
#include "logger.hpp"
#include <cerrno>
#include <iostream>
#include <string>
#include <thread>

using namespace baton;
using namespace std;

InputServer::InputServer(ServerOpts &server_opts)
    : port_number(server_opts.server_port_number), logger(server_opts.logger),
      buffer(new char[server_opts.max_buffer_size]()),
      read_size(server_opts.read_size), write_size(server_opts.write_size),
      keep_alive(false), is_connected(false){};

void InputServer::setup() {

  if ((this->fd = socket(AF_INET, SOCK_STREAM, 0)) == ETIMEDOUT) {
    this->logger.error("Timed out when trying to acquire socket");
    exit(EXIT_FAILURE);
  }

  int opt = 1;
  if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &opt,
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
  if (::bind(this->fd, (struct sockaddr *)&this->address, address_len)) {
    this->logger.error("Failed to bind to port");
    exit(EXIT_FAILURE);
  }
  this->logger.info("Finished binding the socket");
}

void InputServer::listen() {
  if (::listen(this->fd, 3) < 0) {
    this->logger.error("Failed to bind to port");
    exit(EXIT_FAILURE);
  }
  this->logger.info("Listening on port " + to_string(this->port_number));
}

void InputServer::accept() {

  size_t address_len = sizeof(this->address);
  if ((this->new_socket =
           ::accept(this->fd, (struct sockaddr *)&this->address,
                    (socklen_t *)&address_len)) < 0) {
  }
  this->is_connected = true;
  this->logger.info("Accepted connection request from the client");
}

void InputServer::stop() {

  this->keep_alive.store(false);
  ::close(this->new_socket);
  ::shutdown(this->fd, SHUT_RDWR);
  this->logger.info("Shutting down server");
}

int InputServer::read() {
  int valread;
  valread = ::read(this->new_socket, this->buffer, 2);
  cout << this->buffer << endl;
  return valread;
}

void InputServer::write(const string &message) {
  ::send(this->new_socket, message.c_str(), message.size(), 0);
  this->logger.info("Sent message back to the client");
}

void InputServer::thread_handler() {
  int valread;

  while (!this->is_connected) {
    this->accept();
  }

  while (this->keep_alive.load()) {

    valread = ::read(this->new_socket, this->buffer, this->read_size);

    // Failures
    if (valread == 0) {
      this->logger.info(
          "Client has gracefully disconnected. Closing client connection...");
      ::close(this->new_socket);
      continue;
    } else if (valread == -1) {
      if (errno == ECONNRESET || errno == EPIPE) {
        this->logger.error(
            "Client has disconnected ungracefully due to an error.");
        ::close(this->new_socket);
      }
      continue;
    }

    // this->logger.info("Read message from client");

    this->logger.info("Read message: " + string(this->buffer) +
                      " valread: " + to_string(valread));
  };
  int x = 0;
}

void InputServer::start() {
  this->setup();
  this->bind();
  this->listen();

  this->keep_alive.store(true);
  this->server_thread = ::thread(&InputServer::thread_handler, this);
}
