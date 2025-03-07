#ifndef LOGOSERRORS_H
#define LOGOSERRORS_H
#include <map>


const std::map<int, std::string> LOGOS_ERRORS = {
    {1000, "Main function is not defined in Main.lgs file."},
    {1001, "The left-hand type '{}' is not equal to the right-hand type '{}'."},
    {1002, "{} is not iterable"},
    {1003, "Number of arguments does not much. Expected: {}, Given: {}"},
    {1004, "Function {} must return {}"},
};

#endif //LOGOSERRORS_H
