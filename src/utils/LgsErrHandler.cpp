#include "utils/LgsErrHandler.h"
#include "logos/LgsCodeGen.h"
#include "utils/LgsUtils.h"
#define MSG_PLACEHOLDER "%s"
#define MSG_PADDING_PLACEHOLDER "%p"

void LgsErrHandler::setUnsuccessful() {
    successful = false;
}

void LgsErrHandler::addError(const LgsBaseError& lgsErr, LgsLocation* location, const std::vector<std::string>& args) {
    setUnsuccessful();
    std::string result;
    formatErrorMsg(lgsErr, args, result);
    if (location) {
        errors.emplace_back(LgsError{.msg = strdup(result.c_str()), .errCode = lgsErr.errCode, .location = location});
    } else {
        errors.emplace_back(LgsError{.msg = strdup(result.c_str()), .errCode = lgsErr.errCode});
    }
}

void LgsErrHandler::mergeErrors(LgsErrHandler& other) {
    setUnsuccessful();
    errors.insert(errors.end(), other.errors.begin(), other.errors.end());
}
