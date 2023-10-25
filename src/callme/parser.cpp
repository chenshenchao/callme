#include "parser.h"
#include "lexer.h"
#include "error.h"
#include <memory>
#include <cstring>
#include <format>
#include <deque>

namespace callme {
    class parser_implement : public parser {
        std::unique_ptr<lexer> lexer;
        std::deque<callme::lexeme*> queue;
    public:
        parser_implement(callme::lexer* lexer) : lexer(lexer) {}

        virtual ~parser_implement() {
            while (!queue.empty()) {
                delete queue.front();
                queue.pop_front();
            }
        }

        virtual void parse() override {
            next_lexeme();

            while (queue.front()->get_token() != token::eof) {
                switch (queue.front()->get_token()) {
                case token::keyword_import:
                    match_import();
                    break;
                case token::keyword_export:
                    match_export();
                    break;
                case token::keyword_val:
                case token::keyword_var:
                    match_define();
                    break;
                default:
                    throw error(
                        "[{},{}] 该语法不能出现在全局作用域: {}",
                        queue.front()->get_row(),
                        queue.front()->get_column(),
                        queue.front()->get_content()
                    );
                }
            }
        }
    private:
        void match_import() {

        }

        void match_export() {

        }

        void match_define() {
            match_token(token::identifier);
            match_token(token::symbol_equal);
            next_lexeme();
            switch (queue.front()->get_token()) {
            case token::symbol_square_left:
                //
                return;
            case token::symbol_curly_left:
                switch (peek_lexeme(1)->get_token()) {
                case token::identifier:
                    switch (peek_lexeme(2)->get_token()) {
                    case token::symbol_colon:
                        match_object();
                        return;
                    case token::symbol_arrow:
                    case token::symbol_comma:
                        match_function();
                        return;
                    }
                    break;
                case token::symbol_arrow:
                    match_function();
                    return;
                }
                throw error(
                    "[{},{}] 预期 [对象定义] 或 [函数定义] 不匹配",
                    queue.front()->get_row(),
                    queue.front()->get_column(),
                    queue.front()->get_content()
                );
            }
        }

        void match_object() {

        }

        void match_function() {

        }

        bool match_token(token token, bool is_strict=true) {
            next_lexeme();
            auto the_token = queue.front()->get_token();
            if (the_token != token) {
                if (is_strict) {
                    int row = queue.front()->get_row();
                    int column = queue.front()->get_column();
                    const char* content = queue.front()->get_content();
                    switch (the_token) {
                    case token::identifier:
                        throw error(
                            "[{}, {}] 预期 [标识符] 不匹配 {}",
                            row,
                            column,
                            content
                        );
                    default:
                        throw error(
                            "[{}, {}] 预期 [{}] 不匹配",
                            row,
                            column,
                            content
                        );
                    }
                }
                else {
                    return false;
                }
            }
            return true;
        }

        template<class... A>
        syntax_exception error(const std::string& fmt, A &&...args) {
            auto message = std::vformat(fmt, std::make_format_args(args...));
            auto m = new char[message.size() + 1];
            std::memcpy(m, message.c_str(), message.size());
            m[message.size()] = 0;
            return syntax_exception(m);
        }

        void next_lexeme() {
            if (!queue.empty()) {
                queue.pop_front();
            }
            queue.push_back(lexer->pop_lexeme());
        }

        const lexeme *peek_lexeme(int index) {
            while (queue.size() <= index) {
                queue.push_back(lexer->pop_lexeme());
            }
            return queue[index];
        }
    };

    CALLME_API parser* new_parser(const char* script) {
        std::unique_ptr<lexer> lexer(new_lexer(script));
        return new parser_implement(lexer.release());
    }

    CALLME_API parser* new_parser_from(const char* path) {
        std::unique_ptr<lexer> lexer(new_lexer_from(path));
        return new parser_implement(lexer.release());
    }
}
