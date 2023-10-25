#ifndef CALLME_ERROR_H_INCLUDED
#define CALLME_ERROR_H_INCLUDED

#include <exception>
#include <format>
#include <string>
#include <memory>

namespace callme {
    struct interpret_exception : public std::exception {
        interpret_exception(int code, const char *message):
            exception(message, code) {}
    };

    struct lexical_exception : public interpret_exception {
        lexical_exception(int code, const char *message):
            interpret_exception(code, message) {}

        lexical_exception(const char* message) :
            lexical_exception(100, message) {}
    };

    struct syntax_exception : public interpret_exception {
        syntax_exception(int code, const char* message) :
            interpret_exception(code, message) {}

        syntax_exception(const char* message) :
            interpret_exception(200, message) {}
    };

    struct runtime_exception: public interpret_exception {
        runtime_exception(int code, const char* message) :
            interpret_exception(code, message) {}
    };
}

#endif
