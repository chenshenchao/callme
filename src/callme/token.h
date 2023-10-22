#ifndef CALLME_TOKEN_H_INCLUDED
#define CALLME_TOKEN_H_INCLUDED

namespace callme {
    enum token {
        eof = -1,       // 文件结尾
        literal_number, // 数字字面量
        literal_string, // 字符串字面量

        symbol_question_dot, // ?.
        symbol_question_colon, // ?:
        symbol_dot, // .
        symbol_arrow, // ->
        symbol_comma, // ,
        symbol_colon, // :
        symbol_semicolon, // ;
        symbol_equal, // =
        symbol_equal_double, // ==
        symbol_plus, // +
        symbol_minus, // -
        symbol_star, // *
        symbol_slash, // /
        symbol_tip_left, // <
        symbol_tip_left_equal, // <=
        symbol_tip_right, // >
        symbol_tip_right_equal, // >=
        symbol_curly_left, // {
        symbol_curly_right, // }
        symbol_square_left, // [
        symbol_square_right, // ]
        symbol_arc_left, // (
        symbol_arc_right, // )


        identifier, // 标识符

        keyword_null,   // null
        keyword_true,   // true
        keyword_false,  // false
        keyword_return, // 返回
        keyword_import, // 导入
        keyword_export, // 导出
        keyword_var, // var 可变量
        keyword_val, // val 不变量
        keyword_if, // if
        keyword_else, // else
        keyword_loop, // loop
    };
}

#endif
