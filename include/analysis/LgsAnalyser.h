#ifndef LOGOSANALYSER_H
#define LOGOSANALYSER_H
#include "LgsErrors.h"
#include <iostream>
#include <mutex>
#include <vector>
#include <string>

using namespace std;

class LgsAnalyser {
public:
    mutex mtx;
    bool successful = true;

    void setUnsuccessful();
    string formatErrorMsg(const string& errMsg, const vector<string>& args = {}) const;
    void printError(const string& errMsg, const vector<string>& args = {}) const;
};


inline string LgsAnalyser::formatErrorMsg(const string& errMsg, const vector<string>& args) const {
    auto pos = 0;
    auto argIndex = 0;
    auto result = errMsg;
    while ((pos = result.find(ERROR_PLACE_HOLDER, pos)) != string::npos && argIndex < args.size()) {
        result.replace(pos, ERROR_PLACE_HOLDER.size(), args[argIndex]);
        pos += args[argIndex].length();
        argIndex++;
    }
    return "Error: " + result;
}

inline void LgsAnalyser::printError(const string& errMsg, const vector<string>& args) const {
    cout << formatErrorMsg(errMsg, args) << '\n';
}

inline void LgsAnalyser::setUnsuccessful() {
    if (!successful) return;
    successful = false;
}

#endif //LOGOSANALYSER_H
