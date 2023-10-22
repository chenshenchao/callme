#include "lexer.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <format>
#include <map>
#include "token.h"
#include "error.h"

namespace callme {
    // 关键字表
    std::map<std::string, token> keywords = {
        {"return", token::keyword_return},
        {"import", token::keyword_import},
        {"export", token::keyword_export},
        {"var", token::keyword_var},
        {"val", token::keyword_val},
    };

    class lexer_implement : public lexer {
        std::unique_ptr<std::istream> stream;
    public:
        lexer_implement(std::istream* stream) : stream(stream) {

        }

        virtual ~lexer_implement() {

        }

        virtual lexeme* pop_lexeme() {
            int c = stream->get();

            // skip 跳过空字符
            while (std::isspace(c)) {
                c = stream->get();
            }

            // 跳过单行注释
            if (c == '#') {
                while (c != '\n') {
                    c = stream->get();
                }
            }

            // 匹配符号
            switch (c) {
            case '-':
            case '+':
            case '=':
            case '>':
            case '<':
                stream->putback(c);
                return new_lexeme();
            }

            switch (c) {
            case  '"':
                return pop_string();
            }

            throw new lexical_exception("词法错误：未知符号{}", c);
        }

    private:
        lexeme* pop_bool() {
            return nullptr;
        }

        lexeme* pop_number() {
            return nullptr;
        }

        lexeme* pop_string() {
            return nullptr;
        }

        lexeme* pop_identifier() {
            return nullptr;
        }

        lexeme* pop_keyword() {
            return nullptr;
        }
    };

    CALLME_API lexer* new_lexer(const char* script) {
        std::unique_ptr<std::istringstream> stream(new std::istringstream(script));
        return new lexer_implement(stream.release());
    }

    CALLME_API lexer* new_lexer_from(const char* path) {
        std::unique_ptr<std::ifstream> stream(new std::ifstream(path));
        return new lexer_implement(stream.release());
    }
}
