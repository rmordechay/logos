#ifndef LOGOSERRORS_H
#define LOGOSERRORS_H
#include <map>

using namespace std;

const map<int, string> LOGOS_ERRORS = {
    {1000, "main() function is not defined in Main.lgs file."},
    {1001, "The left-hand type '{}' is not equal to the right-hand type '{}'."},
    {1002, "'{}' is not iterable"},
    {1003, "Number of arguments does not much. Expected: {}, Given: {}"},
    {1004, "Function {} must return {}"},
    {1005, "'{}' is not a member of '{}'"},
    {1006, "'{}' is not defined"},
};

const map<int, string> LOGOS_WARNINGS = {
    {5000, "{} is never used"},
};

#endif //LOGOSERRORS_H
