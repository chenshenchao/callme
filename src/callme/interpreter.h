#ifndef CALLME_INTERPRETER_H_INCLUDED
#define CALLME_INTERPRETER_H_INCLUDED

#include "api.h"

namespace callme {
	struct interpreter {
		CALLME_API void interpret(const char *script);
	};

    CALLME_API interpreter* new_interpreter();
}

#endif
