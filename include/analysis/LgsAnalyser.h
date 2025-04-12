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
    string formatMsg(const string& errMsg, const vector<string>& args = {}) const;
    void printError(const string& errMsg, const vector<string>& args = {}) const;
};


inline string LgsAnalyser::formatMsg(const string& errMsg, const vector<string>& args) const {
    auto pos = 0;
    auto argIndex = 0;
    auto result = errMsg;
    while ((pos = result.find(ERROR_PLACEHOLDER, pos)) != string::npos && argIndex < args.size()) {
        result.replace(pos, ERROR_PLACEHOLDER.size(), args[argIndex]);
        pos += args[argIndex].length();
        argIndex++;
    }
    return result;
}

inline void LgsAnalyser::printError(const string& errMsg, const vector<string>& args) const {
    cout << "Error: " << formatMsg(errMsg, args) << '\n';
}

inline void LgsAnalyser::setUnsuccessful() {
    if (!successful) return;
    successful = false;
}

#endif //LOGOSANALYSER_H
