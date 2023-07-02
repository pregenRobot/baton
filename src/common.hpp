#pragma once

#include "logger.hpp"


typedef struct{
    int server_port_number;
    Logger &logger;
    int max_buffer_size;
    int read_size;

} ServerOpts;

