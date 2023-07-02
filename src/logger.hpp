#pragma once

#include <string>
#include <ostream>
namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_YELLOW   = 33,
        FG_BLUE     = 34,
        FG_MAGENTA  = 35,
        FG_CYAN     = 36,
        FG_DEFAULT  = 39,
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

using namespace std;

class Logger {

    public:
        enum class Level {
            NONE = 0,
            ERROR = 1,
            WARN = 2,
            INFO = 3,
            DEBUG = 4
        };

        Logger(Level log_level):log_level(log_level){};
        
        void log(string message, Level log_level) const;
        void error(string message) const;
        void warn(string message) const;
        void info(string message) const;
        void debug(string message) const;
    private:
        Level log_level;
};

