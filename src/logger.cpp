#include "logger.hpp"

#include <chrono>
#include <ctime>
#include <format>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;
using namespace Color;

void Logger::log(string message,
                 Logger::Level log_level = Logger::Level::DEBUG) const {

  if (log_level <= this->log_level) {
    const Modifier def(Code::FG_DEFAULT);
    auto t = time(nullptr);
    auto tm = *localtime(&t);

    stringstream output;

    switch (log_level) {
    case Logger::Level::ERROR: {
      const Modifier red(Code::FG_RED);
      cout << red << "[ERROR] " << message << " ["
             << put_time(&tm, "%d-%m-%Y %H-%M-%S") << "]" << def << endl;
      break;
    }
    case Logger::Level::WARN: {
      const Modifier yellow(Code::FG_YELLOW);
      cout << yellow << "[WARN] " << message << " ["
             << put_time(&tm, "%d-%m-%Y %H-%M-%S") << "]" << def << endl;
      break;
    }
    case Logger::Level::INFO: {
      const Modifier green(Code::FG_GREEN);
      cout << green << "[INFO] " << message << " ["
             << put_time(&tm, "%d-%m-%Y %H-%M-%S") << "]" << def << endl;
      break;
    }
    case Logger::Level::DEBUG: {
      const Modifier magenta(Code::FG_MAGENTA);
      cout << magenta << "[DEBUG] " << message << " ["
             << put_time(&tm, "%d-%m-%Y %H-%M-%S") << "]" << def << endl;
      break;
    }
    case Logger::Level::NONE:
      break;
    }

  }
}

void Logger::error(string message) const {
  Logger::log(message, Logger::Level::ERROR);
};

void Logger::warn(string message) const {
  Logger::log(message, Logger::Level::WARN);
};

void Logger::info(string message) const {
  Logger::log(message, Logger::Level::INFO);
};

void Logger::debug(string message) const {
  Logger::log(message, Logger::Level::DEBUG);
};
