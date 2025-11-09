#include "utils/LgsErrHandler.h"
#include "codegen/LgsLLVMGen.h"
#include "logos/LgsApp.h"

void LgsErrHandler::setUnsuccessful() {
    successful = false;
}

void LgsErrHandler::addError(const LgsBaseError& lgsErr, const std::vector<std::string>& args) {
    setUnsuccessful();
    LgsError err(formatErrorMsg(lgsErr.msg, args), lgsErr.code);
    errors.emplace_back(err);
}

void LgsErrHandler::addError(const LgsBaseError& lgsErr, const LgsLocation* location, const std::string& filePath, const std::vector<std::string>& args) {
    setUnsuccessful();
    LgsError err(formatErrorMsg(lgsErr.msg, args), lgsErr.code);
    if (location) {
        err.location = *location;
        err.filePath = filePath;
        errors.emplace_back(err);
    } else {
        errors.emplace_back(err);
    }
}

void LgsErrHandler::addWarning(const LgsBaseError& lgsErr, const LgsLocation* location, const std::vector<std::string>& args) {
    const auto result = formatErrorMsg(lgsErr.msg, args);
    if (location) {
        warnings.emplace_back(LgsWarning(result, lgsErr.code, *location));
    } else {
        warnings.emplace_back(LgsWarning(result, lgsErr.code));
    }
}

void LgsErrHandler::mergeErrors(LgsErrHandler& other) {
    if (!other.successful) {
        setUnsuccessful();
        errors.insert(errors.end(), other.errors.begin(), other.errors.end());
        if (!other.warnings.empty()) {
            warnings.insert(warnings.end(), other.warnings.begin(), other.warnings.end());
        }
    } else if (!other.warnings.empty()) {
        warnings.insert(warnings.end(), other.warnings.begin(), other.warnings.end());
    }
}

void LgsErrHandler::mergeErrorsWithLock(LgsErrHandler& other) {
    std::lock_guard lock(mtx);
    mergeErrors(other);
}
