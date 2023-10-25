#ifndef CALLME_PARSER_H_INCLUDED
#define CALLME_PARSER_H_INCLUDED

#include "api.h"

namespace callme {
    struct parser {
        virtual ~parser() {}
        virtual void parse() = 0;
    };

    CALLME_API parser* new_parser(const char* script);
    CALLME_API parser* new_parser_from(const char* path);
}

#endif
