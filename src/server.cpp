

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
    string message = "Hello message from the server\0\n";
    input_server.write(message);
    input_server.stop();
}
