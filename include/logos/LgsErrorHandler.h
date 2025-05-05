#ifndef LGSERRORHANDLER_H
#define LGSERRORHANDLER_H
#include "LgsErrors.h"
#include "LgsWarnings.h"
#include <filesystem>
#include <vector>
#include <string>
#include <mutex>

struct Location;

class LgsErrorHandler {
public:
    bool successful = true;
    vector<LgsError> errors;
    vector<LgsWarning> warnings;
    filesystem::path filePath;

    void setUnsuccessful();
    void handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args = {});
    string formatMsg(const string& errMsg, const vector<string>& args = {}) const;
    ~LgsErrorHandler() = default;
};

#endif //LGSERRORHANDLER_H
