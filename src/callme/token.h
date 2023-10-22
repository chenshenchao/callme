#ifndef CALLME_TOKEN_H_INCLUDED
#define CALLME_TOKEN_H_INCLUDED

namespace callme {
    enum token {
        eof = -1,       // 文件结尾
        literal_null,   // null
        literal_true,   // true
        literal_false,  // false
        literal_number, // 数字字面量
        literal_string, // 字符串字面量

        symbol_question, // ?
        symbol_dot, // .
        symbol_arrow, // ->
        symbol_comma, // ,
        symbol_colon, // :
        symbol_semicolon, // ;
        symbol_equal, // ==


        identifier, // 标识符

        keyword_return, // 返回
        keyword_import, // 导入
        keyword_export, // 导出
        keyword_var, // var 可变量
        keyword_val, // val 不变量

    };
}

#endif
