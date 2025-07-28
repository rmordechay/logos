#pragma once
#include "data/LgsErrors.h"
#include "data/LgsWarnings.h"

struct LgsLocation;

class LgsErrHandler {
public:
    bool successful = true;
    vector<LgsError> errors;
    vector<LgsWarning> warnings;

    void setUnsuccessful();
    void handleError(const LgsError& lgsErr, const LgsLocation* location, const vector<string>& args = {});
    void addErrors(vector<LgsError> newErrors);
    ~LgsErrHandler() = default;
};
