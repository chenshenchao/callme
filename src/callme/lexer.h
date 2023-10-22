#ifndef CALLME_LEXER_H_INCLUDED
#define CALLME_LEXER_H_INCLUDED

#include "api.h"
#include "lexeme.h"

namespace callme {
    struct lexer {
        virtual ~lexer() noexcept {};
        virtual lexeme* pop_lexeme() = 0;
    };

    CALLME_API lexer* new_lexer(const char *script);
    CALLME_API lexer* new_lexer_from(const char *path);
}

#endif
