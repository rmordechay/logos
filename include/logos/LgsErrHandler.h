#pragma once
#include "data/LgsErrors.h"
#include "data/LgsWarnings.h"
#include <filesystem>



struct Location;

class LgsErrHandler {
public:
    bool successful = true;
    vector<LgsError> errors;
    vector<LgsWarning> warnings;
    filesystem::path filePath;

    void setUnsuccessful();
    void handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args = {});
    string formatMsg(const string& errMsg, const vector<string>& args = {}) const;
    ~LgsErrHandler() = default;
};


