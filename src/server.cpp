

#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <torch/torch.h>
#include <unistd.h>
#include "logger.hpp"
#include "common.hpp"
#include "input.hpp"

#define OUT_PORT 9876
#define IN_PORT 6789

using namespace std;
using namespace torch;
using namespace baton;
int main(int argc, char **argv) {

    Logger logger = Logger(Logger::Level::DEBUG);
    ServerOpts opts = {.server_port_number = 9876, .logger = logger, .max_buffer_size = 1024, .read_size = 1024};

    InputServer input_server = InputServer(opts);
    input_server.start();
    input_server.read();
    input_server.write("Hello message from the server");
    input_server.stop();





  // cout << "[INFO] Started Server" << endl;

  // int server_fd, new_socket, valread;
  // struct sockaddr_in address;
  // int addrlen = sizeof(address);
  // int opt = 1;
  // char buffer[1024] = {0};

  // string hello = "Hello from server";

  // if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
  //   perror("[ERR] Failed to open socket");
  //   exit(EXIT_FAILURE);
  // }

  // cout << "[INFO] Opened socket" << endl;

  // if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
  //   perror("[ERR] Set socket opt failure");
  //   exit(EXIT_FAILURE);
  // }

  // cout << "[INFO] Set socket options" << endl;

  // address.sin_family = AF_INET;
  // address.sin_addr.s_addr = INADDR_ANY;
  // address.sin_port = htons(IN_PORT);

  // if (::bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
  //   perror("[ERR] Failed to bind to socket");
  //   exit(EXIT_FAILURE);
  // }

  // cout << "[INFO] Binded to Socket" << endl;

  // if (listen(server_fd, 3) < 0) {
  //   perror("[ERR] Failed to listen to socket");
  //   exit(EXIT_FAILURE);
  // }

  // cout << "[INFO] Listening to Socket" << endl;

  // if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
  //                          (socklen_t *)&addrlen)) < 0) {
  //   perror("[ERR] Failed to accept from socket");
  //   exit(EXIT_FAILURE);
  // }

  // cout << "[INFO] Accepted from Socket" << endl;

  // valread = read(new_socket, buffer, 1024);
  // cout << buffer << endl;
  // ::send(new_socket, &hello, hello.size(), 0);
  // cout << "[INFO] Sent message back to client";
  // close(new_socket);
  // shutdown(server_fd, SHUT_RDWR);
  // return 0;
}
