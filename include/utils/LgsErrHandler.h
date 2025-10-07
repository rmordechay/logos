#pragma once
#include "data/LgsErrors.h"
#include "data/LgsWarnings.h"

struct LgsLocation;

class LgsErrHandler {
public:
    bool successful = true;
    std::vector<LgsError> errors;
    std::vector<LgsWarning> warnings;

    void setUnsuccessful();
    void addError(const LgsBaseError& lgsErr, const LgsLocation* location, const std::vector<std::string>& args = {});
    void addWarning(const LgsBaseError& lgsErr, const LgsLocation* location, const std::vector<std::string>& args = {});
    void mergeErrors(LgsErrHandler& other);
};
