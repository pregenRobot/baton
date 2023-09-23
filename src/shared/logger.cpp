#include "logger.hpp"

#include <chrono>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;
using namespace Color;

void Logger::log(string message, Logger::Level log_level,
                 const string caller) const {

  if (log_level <= this->log_level) {
    const Modifier def(Code::FG_DEFAULT);
    auto t = time(nullptr);
    auto tm = *localtime(&t);

    stringstream output;

    switch (log_level) {
    case Logger::Level::ERROR: {
      const Modifier red(Code::FG_RED);
      cout << red << "[ERROR - " << caller << "] " << message << " ["
           << put_time(&tm, "%d-%m-%Y %H-%M-%S") << "]" << def << endl;
      break;
    }
    case Logger::Level::WARN: {
      const Modifier yellow(Code::FG_YELLOW);
      cout << yellow << "[WARN - " << caller << "] " << message << " ["
           << put_time(&tm, "%d-%m-%Y %H-%M-%S") << "]" << def << endl;
      break;
    }
    case Logger::Level::INFO: {
      const Modifier green(Code::FG_GREEN);
      cout << green << "[INFO - " << caller << "] " << message << " ["
           << put_time(&tm, "%d-%m-%Y %H-%M-%S") << "]" << def << endl;
      break;
    }
    case Logger::Level::DEBUG: {
      const Modifier magenta(Code::FG_MAGENTA);
      cout << magenta << "[DEBUG - " << caller << "] " << message << " ["
           << put_time(&tm, "%d-%m-%Y %H-%M-%S") << "]" << def << endl;
      break;
    }
    case Logger::Level::NONE:
      break;
    }
  }
}

void Logger::error(string message, string caller) const {
  Logger::log(message, Logger::Level::ERROR, caller);
};

void Logger::warn(string message, string caller) const {
  Logger::log(message, Logger::Level::WARN, caller);
};

void Logger::info(string message, string caller) const {
  Logger::log(message, Logger::Level::INFO, caller);
};

void Logger::debug(string message, string caller) const {
  Logger::log(message, Logger::Level::DEBUG, caller);
};
