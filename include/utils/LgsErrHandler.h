#pragma once
#include "data/LgsErrors.h"
#include "data/LgsWarnings.h"
#include "utils/LgsUtils.h"

struct Location;

class LgsErrHandler {
public:
    bool successful = true;
    vector<LgsError> errors;
    vector<LgsWarning> warnings;

    void setUnsuccessful();
    void handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args = {});
    void addErrors(vector<LgsError> newErrors);
    ~LgsErrHandler() = default;
};
