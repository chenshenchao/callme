#ifndef CALLME_RUNTIME_ANY_H_INCLUDED
#define CALLME_RUNTIME_ANY_H_INCLUDED

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <variant>

namespace callme::runtime {
    typedef double any_number;
    typedef std::string any_string;
    typedef std::vector<any> any_array;
    typedef std::map<std::string, any> any_object;
    typedef std::variant<any_number, any_string, any_array, any_object> any;
}

#endif
