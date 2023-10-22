#ifndef CALLME_LEXEME_H_INCLUDED
#define CALLME_LEXEME_H_INCLUDED

#include "api.h"
#include "token.h"

namespace callme {
    struct lexeme {
        virtual ~lexeme() noexcept {}
        virtual int get_row() const noexcept = 0;
        virtual int get_column() const noexcept = 0;
        virtual token get_token() const noexcept = 0;
        virtual const char* get_content() const noexcept = 0;
    };

    CALLME_API lexeme* new_lexeme(
        int row,
        int column,
        callme::token token,
        const char* content
    );
}

#endif
