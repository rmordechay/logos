#ifndef LOGOSERRORS_H
#define LOGOSERRORS_H
#include <map>


const std::map<int, std::string> LOGOS_ERRORS = {
    {100, "Main function is not defined in Main.lgs file."},
    {101, "The left-hand type '{}' is not equal to the right-hand type '{}'."},
};

#endif //LOGOSERRORS_H
