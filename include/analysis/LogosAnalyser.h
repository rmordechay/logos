#ifndef LOGOSANALYSER_H
#define LOGOSANALYSER_H
#include "LogosError.h"

#include <iostream>
#include <map>
#include <mutex>

using namespace std;

class LogosAnalyser {
public:
    std::mutex mtx;
    bool successful = true;

    void setUnsuccessful();
    void printError(LogosErrCode code, const vector<string>& args = {});
};


inline void LogosAnalyser::printError(const LogosErrCode code, const vector<string>& args) {
    setUnsuccessful();
    const auto error = LOGOS_ERRORS.find(code);
    auto pos = 0;
    auto argIndex = 0;
    auto result = error->second;
    while ((pos = result.find(ERROR_PLACE_HOLDER, pos)) != string::npos && argIndex < args.size()) {
        result.replace(pos, ERROR_PLACE_HOLDER.size(), args[argIndex]);
        pos += args[argIndex].length();
        argIndex++;
    }
    std::cout << "Error: " << result << '\n';
}

inline void LogosAnalyser::setUnsuccessful() {
    if (successful) {
        std::unique_lock lock(mtx);
        successful = false;
    }
}

#endif //LOGOSANALYSER_H
