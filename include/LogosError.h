#ifndef LOGOSERRORS_H
#define LOGOSERRORS_H
#include <map>

using namespace std;

const map<int, string> LOGOS_ERRORS = {
    {1000, "main() function is not defined in Main.lgs file."},
    {1001, "The left-hand type '{}' is not equal to the right-hand type '{}'."},
    {1002, "{} is not iterable"},
    {1003, "Number of arguments does not much. Expected: {}, Given: {}"},
    {1004, "Function {} must return {}"},
    {1005, "{} is not a member of {}"},
};

const map<int, string> LOGOS_WARNINGS = {
    {5000, "{} is never used"},
};

inline void printError(const int code, const vector<string>& args = {}) {
    const auto error = LOGOS_ERRORS.find(code);
    auto pos = 0;
    auto argIndex = 0;
    auto result = error->second;
    while ((pos = result.find("{}", pos)) != string::npos && argIndex < args.size()) {
        result.replace(pos, 2, args[argIndex]);
        pos += args[argIndex].length();
        argIndex++;
    }
    std::cout << result << std::endl;
}

inline void printError(const int code, const Position& position, const vector<string>& args = {}) {
    const auto error = LOGOS_ERRORS.find(code);
    auto pos = 0;
    auto argIndex = 0;
    auto result = error->second;
    while ((pos = result.find("{}", pos)) != string::npos && argIndex < args.size()) {
        auto str = args[argIndex];
        result.replace(pos, 2, str);
        pos += str.length();
        argIndex++;
    }
    std::cout << "Error at " << position.filePath << ", line " << position.lineNumber << '\n';
    std::cout << '\t' << result << '\n';
}

#endif //LOGOSERRORS_H
