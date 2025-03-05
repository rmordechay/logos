#ifndef LOGOSERRORS_H
#define LOGOSERRORS_H
#include <map>


const std::map<int, std::string> LOGOS_ERRORS = {
    {100, "Main function is not defined in Main.lgs file."},
    {101, "The left-hand type '{}' is not equal to the right-hand type '{}'."},
    {102, "{} is not iterable"},
    {103, "Number of arguments does not much. Expected: {}, Given: {}"},
    {104, "Function {} must return {}"},
};

#endif //LOGOSERRORS_H
