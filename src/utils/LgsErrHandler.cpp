#include "utils/LgsErrHandler.h"
#include "codegen/LgsLLVMGen.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"

void LgsErrHandler::setUnsuccessful() {
    successful = false;
}

void LgsErrHandler::addError(const LgsBaseError& lgsErr, const LgsLocation* location, const std::vector<std::string>& args) {
    setUnsuccessful();
    const auto result = LGS_ERROR_PADDING + formatErrorMsg(lgsErr.msg, args);
    if (location) {
        assert(location->fileID != 0);
        errors.emplace_back(LgsError{.msg = result, .errCode = lgsErr.code, .location = *location});
    } else {
        errors.emplace_back(LgsError{.msg = result, .errCode = lgsErr.code});
    }
}

void LgsErrHandler::addWarning(const LgsBaseError& lgsErr, const LgsLocation* location, const std::vector<std::string>& args) {
    const auto result = LGS_ERROR_PADDING + formatErrorMsg(lgsErr.msg, args);
    if (location) {
        warnings.emplace_back(LgsWarning{.msg = result, .errCode = lgsErr.code, .location = *location});
    } else {
        warnings.emplace_back(LgsWarning{.msg = result, .errCode = lgsErr.code});
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