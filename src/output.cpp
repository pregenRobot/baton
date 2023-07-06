#include "output.hpp"

using namespace std;
using namespace baton;

OutputClient::OutputClient(ClientOpts &client_opts)
    : target_server_port(client_opts.target_server_port),
      logger(client_opts.logger), write_size(client_opts.write_size),
      read_size(client_opts.read_size),
      buffer(new char[client_opts.max_buffer_size]()),
      target_server_address(client_opts.target_server_address){};

void OutputClient::start() { this->connect(); }

void OutputClient::connect() {
  if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == ETIMEDOUT) {
    this->logger.error("Timed out when trying to acquire socket");
    exit(EXIT_FAILURE);
  }

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(this->target_server_port);

  if (inet_pton(AF_INET, this->target_server_address, &server_address.sin_addr),
      sizeof(server_address) < 0) {
    this->logger.error(
        "Invalid address or IPv4 or IPv6 address is not supported");
    exit(EXIT_FAILURE);
  }

  if ((connect_status =
           ::connect(this->client_fd, (struct sockaddr *)&server_address,
                     sizeof(server_address))) < 0) {
    this->logger.error("Failed to connect to server");
    exit(EXIT_FAILURE);
  }
};

int OutputClient::read() {
  int valread;
  valread = ::read(this->client_fd, buffer, this->read_size);
  return valread;
}

void OutputClient::write(const string &message) {
  ::send(client_fd, message.c_str(), message.size(), 0);
  this->logger.info("Sent message back to the server");
}

void OutputClient::stop() {
  ::close(this->client_fd);
  this->logger.info("Closing client connection to the server");
}
