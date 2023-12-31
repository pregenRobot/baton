#pragma once

#include <ostream>
#include <string>
namespace Color {
enum Code {
  FG_RED = 31,
  FG_GREEN = 32,
  FG_YELLOW = 33,
  FG_BLUE = 34,
  FG_MAGENTA = 35,
  FG_CYAN = 36,
  FG_DEFAULT = 39,
};
class Modifier {
  Code code;

public:
  Modifier(Code pCode) : code(pCode) {}
  friend std::ostream &operator<<(std::ostream &os, const Modifier &mod) {
    return os << "\033[" << mod.code << "m";
  }
};
} // namespace Color

using namespace std;

class Logger {

public:
  enum class Level { NONE = 0, ERROR = 1, WARN = 2, INFO = 3, DEBUG = 4 };

  Logger(Level log_level) : log_level(log_level){};

  void error(string message, string caller = __builtin_FUNCTION()) const;
  void warn(string message, string caller = __builtin_FUNCTION()) const;
  void info(string message, string caller = __builtin_FUNCTION()) const;
  void debug(string message, string caller = __builtin_FUNCTION()) const;

private:
  Level log_level;
  void log(string message, Level log_level, const string caller) const;
};
