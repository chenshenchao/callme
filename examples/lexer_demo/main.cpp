#include <iostream>
#include <memory>
#include <callme.h>

int main() {
    using namespace callme;
    std::cout << "lexer demo start" << std::endl;

    std::unique_ptr<lexer> lexer(new_lexer_from("simple.cm"));

    return 0;
}
