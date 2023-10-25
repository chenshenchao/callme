#include <iostream>
#include <filesystem>
#include <callme.h>

void print_parse(const std::string &path) {
    using namespace callme;

    try {
        std::unique_ptr<parser> parser(new_parser_from(path.c_str()));
        parser->parse();
    }
    catch (lexical_exception& e) {
        std::cout << "[LEX ERROR] " << e.what() << std::endl;
    }
    catch (syntax_exception& e) {
        std::cout << "[SYNTAX ERROR] " << e.what() << std::endl;
    }
}

int main() {
    std::locale::global(std::locale("zh_CN.utf8"));

    try {

        std::cout << "parser demo start." << std::endl;

        for (auto& fe : std::filesystem::directory_iterator(".")) {
            auto path = std::filesystem::absolute(fe.path()).string();
            if (path.ends_with(".cm")) {
                std::cout << "========" << path << "========" << std::endl;
                print_parse(path);
            }
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

	return 0;
}
