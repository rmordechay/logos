#include "utils/LgsErrHandler.h"
#include "configs/LgsDefinitions.h"
#include "logos/LgsCodeGen.h"

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

void LgsErrHandler::formatErrorMsg(const LgsBaseError& lgsErr, const std::vector<std::string>& args, std::string& result) {
    auto pos = 0;
    auto argIndex = 0;
    result = std::string(lgsErr.msg);
    while ((pos = result.find(MSG_PLACEHOLDER, pos)) != std::string::npos && argIndex < args.size()) {
        result.replace(pos, std::strlen(MSG_PLACEHOLDER), args[argIndex]);
        pos += args[argIndex].length();
        argIndex++;
    }
    pos = 0;
    argIndex = 0;
    while ((pos = result.find(MSG_PADDING_PLACEHOLDER, pos)) != std::string::npos) {
        result.replace(pos, std::strlen(MSG_PADDING_PLACEHOLDER), LGS_ERROR_PADDING);
        pos += args[argIndex].length();
        argIndex++;
    }
}

void LgsErrHandler::mergeErrors(LgsErrHandler& other) {
    setUnsuccessful();
    errors.insert(errors.end(), other.errors.begin(), other.errors.end());
}
