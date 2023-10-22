#include <iostream>
#include <memory>
#include <callme.h>
#include <format>

int main() {
    using namespace callme;

    try {
        std::cout << "lexer demo start" << std::endl;

        std::unique_ptr<lexer> lexer(new_lexer_from("simple.cm"));

        std::unique_ptr<lexeme> lexeme;
        do {
            lexeme.reset(lexer->pop_lexeme());

            auto log = std::format("[{}, {}] {}", lexeme->get_row(), lexeme->get_column(), lexeme->get_content());
            std::cout << log << std::endl;
        } while (lexeme->get_token() != token::eof);
    }
    catch (lexical_exception &e) {
        std::cout << e.what() << std::endl;
    }

    std::cin.get();
    return 0;
}
