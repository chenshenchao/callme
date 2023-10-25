#include "lexer.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <format>
#include <cstring>
#include <map>
#include <set>
#include "token.h"
#include "error.h"

namespace callme {
    // 符号集
    std::set<char> symbols = { '?','.',':',',',';','=','+','-','*','/','<','>','{','}','[',']','(',')' };

    // 关键字表
    std::map<std::string, token> keywords = {
        {"null", token::keyword_null},
        {"true", token::keyword_true},
        {"false", token::keyword_false},
        {"return", token::keyword_return},
        {"import", token::keyword_import},
        {"export", token::keyword_export},
        {"as", token::keyword_as},
        {"var", token::keyword_var},
        {"val", token::keyword_val},
        {"if", token::keyword_if},
        {"else", token::keyword_else},
        {"loop", token::keyword_loop},
    };

    inline bool is_id_start(int code) {
        return std::isalpha(code) || code == '_';
    }

    class lexer_implement : public lexer {
        int index;
        int row;
        int column;
        int code;
        std::unique_ptr<std::istream> stream;
    public:
        lexer_implement(std::istream* stream) :
            index(0),
            row(1),
            column(0),
            code(' '),
            stream(stream) {}
        virtual ~lexer_implement() {}

        virtual lexeme* pop_lexeme() {
            // 取出字符
            pop_charcode();

            // 跳过无效字符和注释
            skip();

            // 文件结尾
            if (code == -1) {
                return new_lexeme(token::eof, "[eof]");
            }

            // 数字
            if (std::isdigit(code)) {
                return pop_number();
            }

            // 字符串
            if (code == '"') {
                return pop_string();
            }

            // 操作符
            if (symbols.find(code) != symbols.end()) {
                return pop_symbol();
            }

            // 标识符关键字或布尔值
            if (is_id_start(code)) {
                return pop_identifier();
            }

            throw error("[{}, {}] 未知字符: {:2x}", row, column, code);
        }

    private:
        /// <summary>
        /// 操作符
        /// </summary>
        /// <returns></returns>
        lexeme* pop_symbol() {
            // 匹配符号
            switch (code) {
            case '.':
                return new_lexeme(token::symbol_dot, ".");
            case ',':
                return new_lexeme(token::symbol_comma, ",");
            case ':':
                return new_lexeme(token::symbol_colon, ":");
            case ';':
                return new_lexeme(token::symbol_semicolon, ";");
            case '+':
                return new_lexeme(token::symbol_plus, "+");
            case '-':
                if (stream->peek() == '>') {
                    pop_charcode();
                    return new_lexeme(token::symbol_arrow, "->");
                }
                return new_lexeme(token::symbol_minus, "-");
            case '*':
                return new_lexeme(token::symbol_star, "*");
            case '/':
                return new_lexeme(token::symbol_slash, "/");
            case '=':
                if (stream->peek() == '=') {
                    pop_charcode();
                    return new_lexeme(token::symbol_equal_double, "==");
                }
                return new_lexeme(token::symbol_equal, "=");
            case '<':
                if (stream->peek() == '=') {
                    pop_charcode();
                    return new_lexeme(token::symbol_tip_left_equal, "<=");
                }
                return new_lexeme(token::symbol_tip_left, "<");
            case '>':
                if (stream->peek() == '=') {
                    pop_charcode();
                    return new_lexeme(token::symbol_tip_right_equal, ">=");
                }
                return new_lexeme(token::symbol_tip_right, ">");
            case '(':
                return new_lexeme(token::symbol_arc_left, "(");
            case ')':
                return new_lexeme(token::symbol_arc_right, ")");
            case '[':
                return new_lexeme(token::symbol_square_left, "[");
            case ']':
                return new_lexeme(token::symbol_square_right, "]");
            case '{':
                return new_lexeme(token::symbol_curly_left, "{");
            case '}':
                return new_lexeme(token::symbol_curly_right, "}");
            case '?':
                switch (stream->peek()) {
                case '.':
                    pop_charcode();
                    return new_lexeme(token::symbol_question_dot, "?.");
                case ':':
                    pop_charcode();
                    return new_lexeme(token::symbol_question_colon, "?:");
                }
            }

            throw error("[{},{}] 无效操作符 {:2x}", row, column, code);
        }

        /// <summary>
        /// 数字词素
        /// </summary>
        /// <returns></returns>
        lexeme* pop_number() {
            std::stringstream buffer;
            buffer << (char)code;

            int c = stream->peek();

            // 点号前数字
            while (std::isdigit(c)) {
                pop_charcode();
                buffer << (char)code;
                c = stream->peek();
            }

            // 点号以及后面的数字
            if (c == '.') {
                pop_charcode();
                buffer << (char)code;
                c = stream->peek();

                if (!std::isdigit(c)) {
                    throw error("[{}, {}] 无效数字 {:2x}", row, column, code);
                }

                while (std::isdigit(c)) {
                    pop_charcode();
                    buffer << (char)code;
                    c = stream->peek();
                }
            }

            return new_lexeme(token::literal_number, buffer.str().c_str());
        }

        /// <summary>
        /// 字符串
        /// </summary>
        /// <returns></returns>
        lexeme* pop_string() {
            if (code != '"') {
                throw error("[{},{}] 无效字符串 {:2x}", row, column, code);
            }

            std::stringstream buffer;
            pop_charcode();
            do {
                // 字符转义
                if (code == '\\') {
                    pop_charcode();
                    switch (code) {
                    case '0':
                        code = '\0';
                        break;
                    case 't':
                        code = '\t';
                        break;
                    case 'n':
                        code = '\n';
                        break;
                    case 'r':
                        code = '\r';
                        break;
                    case '\\':
                        code = '\\';
                        break;
                    case '"':
                        code = '"';
                        break;
                    default:
                        throw error("[{},{}] 无效字符转义 {:2x}", row, column, code);
                    }
                }
                buffer << (char)code;
                pop_charcode();
            } while (code != '"');

            return new_lexeme(token::literal_string, buffer.str().c_str());
        }

        lexeme* pop_identifier() {
            if (!is_id_start(code)) {
                throw error("[{},{}] 无效标识符 {:2x}", row, column, code);
            }
            std::stringstream buffer;
            buffer << (char)code;

            int c = stream->peek();
            while (std::isalnum(c) || c == '_') {
                pop_charcode();
                buffer << (char)code;
                c = stream->peek();
            }

            // 关键字
            auto text = buffer.str();
            auto key = keywords.find(text);
            if (key != keywords.end()) {
                return new_lexeme(key->second, key->first.c_str());
            }

            // 标识符
            return new_lexeme(token::identifier, text.c_str());
        }

        /// <summary>
        /// 跳过无意义符号
        /// </summary>
        void skip() {
            // 跳过 BOM
            if (code == 0xEF && index == 1) {
                pop_charcode();
                if (code == 0xBB) {
                    pop_charcode();
                    if (code == 0xBF) {
                        pop_charcode();
                        column = 1;
                        skip();
                        return;
                    }
                }
                throw error("[{},{}] 无效 BOM 头 {:2x}", row, column, code);
            }

            // 跳过空字符
            while (std::isspace(code)) {
                pop_charcode();
            }

            // 跳过注释
            if (code == '#') {
                do {
                    pop_charcode();
                } while (code != '\n');
                skip();
            }
        }

        /// <summary>
        /// 弹出一个字符编码
        /// </summary>
        void pop_charcode() {
            code = stream->get();

            // \r \r\n => \n
            if (code == '\r') {
                int n = stream->peek();
                code = n == '\n' ? stream->get() : '\n';
            }

            // 换行处理
            if (code == '\n') {
                ++row;
                column = 0;
            }
            else {
                ++column;
            }
            ++index;
        }

        // TODO utf8 支持
        template<class... A>
        lexical_exception error(const std::string &fmt, A &&...args) {
            auto message = std::vformat(fmt, std::make_format_args(args...));
            auto m = new char[message.size() + 1];
            std::memcpy(m, message.c_str(), message.size());
            m[message.size()] = 0;
            return lexical_exception(m);
        }

        /// <summary>
        /// 生成一个词素
        /// </summary>
        /// <param name="token"></param>
        /// <param name="content"></param>
        /// <returns></returns>
        lexeme* new_lexeme(token token, const char* content) {
            std::string c(content);
            return callme::new_lexeme(
                row,
                column - (c == "[eof]" ? 0 : c.size() - 1),
                token,
                content
            );
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
