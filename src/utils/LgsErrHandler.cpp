#include "utils/LgsErrHandler.h"
#include "LgsLocation.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsLogger.h"

void LgsErrHandler::setUnsuccessful() {
    successful = false;
}

void LgsErrHandler::handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args) {
    setUnsuccessful();
    auto pos = 0;
    auto argIndex = 0;
    auto result = lgsErr.msg;
    while ((pos = result.find(ERROR_PLACEHOLDER, pos)) != string::npos && argIndex < args.size()) {
        result.replace(pos, ERROR_PLACEHOLDER.size(), args[argIndex]);
        pos += args[argIndex].length();
        argIndex++;
    }
    const auto finalResult = LOGOS_ERROR_STR + result + "\n\t   at " + location->getFullPath(location->filePath) + "\n---";
    errors.emplace_back(LgsError{.msg = finalResult, .errCode = lgsErr.errCode});
}