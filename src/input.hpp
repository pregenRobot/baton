#pragma once

#include "logger.hpp"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "common.hpp"
#include "string"

namespace baton {
typedef int server_fd;

class InputServer {

public:
  const int port_number;
  const Logger &logger;
  const int read_size;

  server_fd server_fd;
  int new_socket;
  struct sockaddr_in address;
  int max_buffer_size;
  char* buffer;

  InputServer(ServerOpts& server_opts);


  void start();
  void read();
  void write(const string& message);
  void stop();

private:
  void setup();
  void bind();
  void listen();
  void accept();

};
} // namespace baton
