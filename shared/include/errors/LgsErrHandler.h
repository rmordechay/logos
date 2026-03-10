#pragma once
#include <vector>
#include <mutex>
#include <string>

#include "LgsTokens.h"

struct LgsBaseMsg;
class LgsApp;

struct LgsError {
    std::string msg;
    size_t errCode;
    LgsLocation location;
    std::string filePath = "";

    LgsError(const std::string& msg, const size_t errCode) : msg(msg), errCode(errCode) {}
    LgsError(const std::string& msg, const size_t errCode, const LgsLocation& location) : msg(msg), errCode(errCode), location(location) {}
};

struct LgsWarning {
    std::string msg;
    size_t errCode;
    LgsLocation location;

    LgsWarning(const std::string& msg, size_t errCode) : msg(msg), errCode(errCode) {}
    LgsWarning(const std::string& msg, size_t errCode, const LgsLocation& location) : msg(msg), errCode(errCode), location(location) {}
};

class LgsErrHandler {
public:
    bool successful = true;
    std::vector<LgsError> errors;
    std::vector<LgsWarning> warnings;

    void setUnsuccessful();
    void addError(const LgsBaseMsg& lgsErr, const std::vector<std::string>& args);
    void addError(const LgsBaseMsg& lgsErr, const LgsLocation* location, const std::string& filePath, const std::vector<std::string>& args);
    void addWarning(const LgsBaseMsg& lgsErr, const LgsLocation* location, const std::vector<std::string>& args);
    void mergeErrors(LgsErrHandler& other);
    void mergeErrorsWithLock(LgsErrHandler& other, std::mutex& mtx);
    void printErrors() const;
};
