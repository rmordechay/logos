#pragma once
#include "data/LgsErrors.h"
#include "data/LgsWarnings.h"
#include <vector>

class LgsApp;
struct LgsLocation;

class LgsErrHandler {
public:
    bool successful = true;
    std::vector<LgsError> errors;
    std::vector<LgsWarning> warnings;

    void setUnsuccessful();
    void addError(const LgsBaseMsg& lgsErr, const std::vector<std::string>& args = {});
    void addError(const LgsBaseMsg& lgsErr, const LgsLocation* location, const std::string& filePath, const std::vector<std::string>& args);
    void addWarning(const LgsBaseMsg& lgsErr, const LgsLocation* location, const std::vector<std::string>& args = {});
    void mergeErrors(LgsErrHandler& other);
    void mergeErrorsWithLock(LgsErrHandler& other);
    void printErrors() const;
};
