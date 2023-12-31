﻿#include "lexeme.h"
#include <string>

namespace callme {
    class lexeme_implement : public lexeme {
        int row;
        int column;
        token token;
        std::string content;
    public:
        lexeme_implement(
            int row,
            int column,
            callme::token token,
            const char *content
        ) :
            row(row),
            column(column),
            token(token),
            content(content)
        {}

        virtual int get_row() const noexcept override { return row; }
        virtual int get_column() const noexcept override { return column; }
        virtual callme::token get_token() const noexcept override { return token; }
        virtual const char* get_content() const noexcept override { return content.c_str(); }
    };

    CALLME_API lexeme* new_lexeme(
        int row,
        int column,
        callme::token token,
        const char* content
    ) {
        return new lexeme_implement(
            row,
            column,
            token,
            content
        );
    }
}
