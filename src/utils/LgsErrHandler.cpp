#include "utils/LgsErrHandler.h"
#include "LgsDefinitions.h"

void LgsErrHandler::setUnsuccessful() {
    successful = false;
}

void LgsErrHandler::addError(const LgsError& lgsErr, LgsLocation* location, const vector<string>& args) {
    setUnsuccessful();
    auto pos = 0;
    auto argIndex = 0;
    auto result = string(lgsErr.msg);
    while ((pos = result.find(LOGOS_MSG_PLACEHOLDER, pos)) != string::npos && argIndex < args.size()) {
        result.replace(pos, string(LOGOS_MSG_PLACEHOLDER).size(), args[argIndex]);
        pos += args[argIndex].length();
        argIndex++;
    }
    pos = 0;
    argIndex = 0;
    while ((pos = result.find(LOGOS_MSG_PADDING_PLACEHOLDER, pos)) != string::npos) {
        result.replace(pos, string(LOGOS_MSG_PADDING_PLACEHOLDER).size(), ERROR_PADDING);
        pos += args[argIndex].length();
        argIndex++;
    }
    if (location) {
        errors.emplace_back(LgsError{.msg = strdup(result.c_str()), .errCode = lgsErr.errCode, .location = location});
    } else {
        errors.emplace_back(LgsError{.msg = strdup(result.c_str()), .errCode = lgsErr.errCode});
    }
}

void LgsErrHandler::copyErrors(vector<LgsError> newErrors) {
    setUnsuccessful();
    errors.insert(errors.end(), newErrors.begin(), newErrors.end());
}
