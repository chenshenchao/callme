#ifndef CALLME_ERROR_H_INCLUDED
#define CALLME_ERROR_H_INCLUDED

#include <exception>
#include <format>
#include <memory>

namespace callme {
    struct interpret_exception : public std::exception {
        template<class... A>
        interpret_exception(int code, const std::format_string<A...> fmt, A&&... args):
            exception(std::format(fmt, args...).c_str(), code) {}

    };

    struct lexical_exception : public interpret_exception {
        template<class... A>
        lexical_exception(int code, const std::format_string<A...> fmt, A&&... args):
            interpret_exception(code, fmt, args...) {}

        template<class... A>
        lexical_exception(const std::format_string<A...> fmt, A&&... args) :
            lexical_exception(100, fmt, args...) {}
    };

    struct syntax_exception : public interpret_exception {
        template<class... A>
        syntax_exception(int code, const std::format_string<A...> fmt, A&&... args) :
            interpret_exception(code, fmt, args...) {}
    };

    struct runtime_exception: public interpret_exception {
        template<class... A>
        runtime_exception(int code, const std::format_string<A...> fmt, A&&... args) :
            interpret_exception(code, fmt, args...) {}
    };
}

#endif
