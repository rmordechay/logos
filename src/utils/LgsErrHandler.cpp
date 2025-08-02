#include "utils/LgsErrHandler.h"

#include "LgsDefinitions.h"
#include "LgsLocation.h"

void LgsErrHandler::setUnsuccessful() {
    successful = false;
}

void LgsErrHandler::addError(const LgsError& lgsErr, const LgsLocation* location, const vector<string>& args) {
    setUnsuccessful();
    auto pos = 0;
    auto argIndex = 0;
    auto result = string(lgsErr.msg);
    while ((pos = result.find(LOGOS_MSG_PLACEHOLDER, pos)) != string::npos && argIndex < args.size()) {
        result.replace(pos, string(LOGOS_MSG_PLACEHOLDER).size(), args[argIndex]);
        pos += args[argIndex].length();
        argIndex++;
    }
    const auto finalResult = result + "\n\t   at " + location->getFullPath() + "\n---";
    errors.emplace_back(LgsError{.msg = strdup(finalResult.c_str()), .errCode = lgsErr.errCode});
}

void LgsErrHandler::copyErrors(vector<LgsError> newErrors) {
    setUnsuccessful();
    errors.insert(errors.end(), newErrors.begin(), newErrors.end());
}
