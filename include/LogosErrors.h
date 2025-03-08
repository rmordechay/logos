#ifndef LOGOSERRORS_H
#define LOGOSERRORS_H
#include <map>

using namespace std;

const std::map<int, std::string> LOGOS_ERRORS = {
    {1000, "Main function is not defined in Main.lgs file."},
    {1001, "The left-hand type '%s' is not equal to the right-hand type '%s'."},
    {1002, "%s is not iterable"},
    {1003, "Number of arguments does not much. Expected: %s, Given: %s"},
    {1004, "Function %s must return %s"},
};

const std::map<int, std::string> LOGOS_WARNINGS = {
    {5000, "%s is never used"},
};

inline void printError(const size_t code, ...) {
    char buffer[256];
    const auto error = LOGOS_ERRORS.find(code);
    va_list args;
    va_start(args, code);
    vsnprintf(buffer, sizeof(buffer), error->second.c_str(), args);
    va_end(args);
    std::cout << string(buffer) << '\n';
}

#endif //LOGOSERRORS_H
