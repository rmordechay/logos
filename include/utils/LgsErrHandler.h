#pragma once
#include "configs/LgsErrors.h"
#include "configs/LgsWarnings.h"

struct LgsLocation;

class LgsErrHandler {
public:
    bool successful = true;
    vector<LgsError> errors;
    vector<LgsWarning> warnings;

    void setUnsuccessful();
    void addError(const LgsBaseError& lgsErr, LgsLocation* location, const vector<string>& args = {});
    void mergeErrors(LgsErrHandler& other);
    ~LgsErrHandler() = default;
};
