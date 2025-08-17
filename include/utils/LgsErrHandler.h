#pragma once
#include "configs/LgsErrors.h"
#include "configs/LgsWarnings.h"

struct LgsLocation;

class LgsErrHandler {
public:
    bool successful = true;
    std::vector<LgsError> errors;
    std::vector<LgsWarning> warnings;

    void setUnsuccessful();
    static void formatErrorMsg(const LgsBaseError& lgsErr, const std::vector<std::string>& args, std::string& result);
    void addError(const LgsBaseError& lgsErr, LgsLocation* location, const std::vector<std::string>& args = {});
    void mergeErrors(LgsErrHandler& other);
    ~LgsErrHandler() = default;
};
