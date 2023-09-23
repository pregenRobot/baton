#pragma once

#include "common.hpp"
#include "logger.hpp"
#include "string"
#include <atomic>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

namespace baton {
typedef int server_fd;

typedef struct ServerOpts {
  Logger &logger;
  int server_port_number;
  int max_buffer_size;
  int read_size;
  int write_size = DEF_METADATA_SIZE;
} ServerOpts;

class InputServer {

private:
  const int port_number;
  const Logger &logger;
  const int read_size;
  const int write_size;

  server_fd fd;
  int new_socket;
  struct sockaddr_in address;
  int max_buffer_size;

  char *buffer;
  void setup();
  void bind();
  void listen();
  void accept();
  void thread_handler();

  bool is_connected;

public:
  InputServer(ServerOpts &server_opts);

  atomic<bool> keep_alive;
  thread server_thread;

  void start();
  int read();
  void write(const string &message);
  void stop();
};
} // namespace baton
