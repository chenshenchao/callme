#include <iostream>
#include <memory>
#include <callme.h>
#include <format>
#include <filesystem>
#include <string>
#include <codecvt>

// 没用到。
std::string utf8tomb(const std::string &source) {
    auto& f = std::use_facet<std::codecvt<char, char, std::mbstate_t>>(std::locale());
    std::mbstate_t mbs = std::mbstate_t();
    std::string target(source.size() * f.max_length(), '\0');
    const char* from_next;
    char* to_next;
    f.out(mbs, &source[0], &source[source.size()], from_next,
        &target[0], &target[target.size()], to_next);
    target.resize(to_next - &target[0]);
    return target;
}

void print_lexeme(std::string path) {
    using namespace callme;
    try {
        std::unique_ptr<lexer> lexer(new_lexer_from(path.c_str()));
        std::unique_ptr<lexeme> lexeme;
        do {
            lexeme.reset(lexer->pop_lexeme());
            auto content = lexeme->get_content();
            auto log = std::format("[{}, {}] {}", lexeme->get_row(), lexeme->get_column(), content);
            std::cout << log << std::endl;
        } while (lexeme->get_token() != token::eof);
    }
    catch (lexical_exception& e) {
        std::cout << "[LEX ERROR] " << e.what() << std::endl;
    }
}

int main() {
    std::locale::global(std::locale("zh_CN.utf8"));

    try {
        std::cout << "lexer demo start" << std::endl;

        for (auto& fe : std::filesystem::directory_iterator(".")) {
            auto path = std::filesystem::absolute(fe.path()).string();
            if (path.ends_with(".cm")) {
                std::cout << "========" << path << "========" << std::endl;
                print_lexeme(path);
            }
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    std::cin.get();
    return 0;
}
