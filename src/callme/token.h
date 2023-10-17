#ifndef CALLME_TOKEN_H_INCLUDED
#define CALLME_TOKEN_H_INCLUDED

namespace callme {
    enum token {
        eof = -1,
        literal_null,
        literal_true,
        literal_false,
        literal_number,
        literal_string,

        symbol_,

        identifier,
    };
}

#endif
