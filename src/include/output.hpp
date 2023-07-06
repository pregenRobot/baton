#pragma once

#include "common.hpp"
#include "logger.hpp"
#include <arpa/inet.h>
#include <atomic>
#include <stdio.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

namespace baton {
typedef int client_fd;

typedef struct ClientOpts {
  Logger &logger;
  int max_buffer_size;
  int write_size;
  int read_size = DEF_METADATA_SIZE;
  string target_server_address;
  int target_server_port;
} ClientOpts;

class OutputClient {

private:
  void connect();

  const int target_server_port;
  string target_server_address;

  const Logger &logger;

  const int write_size;
  const int read_size;
  int max_buffer_size;
  char *buffer;

  client_fd client_fd;
  struct sockaddr_in server_address;
  int connect_status;

public:
  OutputClient(ClientOpts &client_opts);

  atomic<bool> keep_alive;
  thread client_thread;

  void start();
  int read();
  void write(const string &message);
  void stop();
  void thread_handler();
};
} // namespace baton
