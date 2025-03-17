#ifndef LOGOSANALYSER_H
#define LOGOSANALYSER_H
#include "../logos/LgsErrors.h"

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
    string formatErrorMsg(LgsErrCode code, const vector<string>& args = {});
    void printError(LgsErrCode code, const vector<string>& args = {});
};


inline string LgsAnalyser::formatErrorMsg(const LgsErrCode code, const vector<string>& args) {
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
    return "Error: " + result + '\n';
}

inline void LgsAnalyser::printError(const LgsErrCode code, const vector<string>& args) {
    cout << "Error: " << formatErrorMsg(code, args) << endl;
}

inline void LgsAnalyser::setUnsuccessful() {
    if (!successful) return;
    successful = false;
}

#endif //LOGOSANALYSER_H
