#ifndef LOGOSANALYSER_H
#define LOGOSANALYSER_H
#include "LgsError.h"

#include <iostream>
#include <map>
#include <mutex>
#include <vector>
#include <string>

using namespace std;

class LgsAnalyser {
public:
    std::mutex mtx;
    bool successful = true;

    void setUnsuccessful();
    void printError(LgsErrCode code, const vector<string>& args = {});
};


inline void LgsAnalyser::printError(const LgsErrCode code, const vector<string>& args) {
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

inline void LgsAnalyser::setUnsuccessful() {
    if (successful) {
        std::unique_lock lock(mtx);
        successful = false;
    }
}

#endif //LOGOSANALYSER_H
