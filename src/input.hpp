#pragma once

#include "logger.hpp"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace baton {
typedef int server_fd;

class InputServer {

public:
  const int port_number;
  const Logger &logger;
  static server_fd server_fd;
  InputServer(const int port_number, const Logger &logger);
  void setup();
};
} // namespace baton
