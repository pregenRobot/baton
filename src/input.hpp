#pragma once

#include "common.hpp"
#include "logger.hpp"
#include "string"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace baton {
typedef int server_fd;

typedef struct ServerOpts {
  Logger &logger;
  int server_port_number;
  int max_buffer_size;
  int read_size = DEF_METADATA_SIZE;
  int write_size = 4;
} ServerOpts;

class InputServer {

public:
  const int port_number;
  const Logger &logger;
  const int read_size;
  const int write_size;

  server_fd server_fd;
  int new_socket;
  struct sockaddr_in address;
  int max_buffer_size;
  char *buffer;

  InputServer(ServerOpts &server_opts);

  void start();
  int read();
  void write(const string &message);
  void stop();

private:
  void setup();
  void bind();
  void listen();
  void accept();
};
} // namespace baton
