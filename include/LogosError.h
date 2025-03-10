#ifndef LOGOSERRORS_H
#define LOGOSERRORS_H
#include <map>

using namespace std;

enum LogosErrorNo {
    ERR_10000,
    ERR_10001,
    ERR_10002,
    ERR_10003,
    ERR_10004,
    ERR_10005,
    ERR_10006,
};

const map<LogosErrorNo, string> LOGOS_ERRORS = {
    {ERR_10000, "main() function is not defined in Main.lgs file."},
    {ERR_10001, "The left-hand type '{}' is not equal to the right-hand type '{}'."},
    {ERR_10002, "'{}' is not iterable."},
    {ERR_10003, "Number of arguments does not much. Expected: {}, Given: {}."},
    {ERR_10004, "Function {} must return {}."},
    {ERR_10005, "'{}' is not a member of '{}'."},
    {ERR_10006, "'{}' is not defined."},
};

const map<int, string> LOGOS_WARNINGS = {
    {5000, "{} is never used."},
};

#endif //LOGOSERRORS_H
