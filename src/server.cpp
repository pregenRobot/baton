

#include "input.hpp"
#include "logger.hpp"
#include "output.hpp"
#include <chrono>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <thread>
#include <torch/torch.h>
#include <unistd.h>

#define OUT_PORT 9876
#define IN_PORT 6789

using namespace std;
using namespace torch;
using namespace baton;
int main(int argc, char **argv) {

  Logger logger = Logger(Logger::Level::DEBUG);
  ServerOpts s_opts = {.logger = logger,
                       .server_port_number = 9876,
                       .max_buffer_size = 1024,
                       .read_size = 1024};

  InputServer input_server(s_opts);
  input_server.start();

  ClientOpts c_opts = {.logger = logger,
                       .max_buffer_size = 1024,
                       .write_size = 1024,
                       .read_size = 1024,
                       .target_server_address = "127.0.0.1",
                       .target_server_port = 9876};

  OutputClient output_client(c_opts);
  output_client.start();

  output_client.client_thread.join();
  input_server.server_thread.join();
}
