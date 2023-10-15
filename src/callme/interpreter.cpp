#include "interpreter.h"

namespace callme {
	class interpreter_implement : public interpreter {
	public:
        CALLME_API void interpreter(const char* script) {

		}
	};

    CALLME_API interpreter* new_interpreter() {
		return new interpreter_implement();
	}
}
