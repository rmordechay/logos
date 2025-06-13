#include "logos/LgsErrHandler.h"
#include "LgsLocation.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsLogger.h"
#include "utils/LgsUtils.h"

void LgsErrHandler::setUnsuccessful() {
    successful = false;
}

void LgsErrHandler::handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args) {
    setUnsuccessful();
    const auto errMsg = formatMsg(lgsErr.msg, args);
    errors.emplace_back(LgsError{.msg = errMsg, .errCode = lgsErr.errCode});
    lock_guard lock(mtx);
    lgsLog(ERROR_STR + errMsg);
    if (location->filePath) {
        lgsLog("\t   at " + location->getFullPath(*location->filePath) + "\n---");
    }
}

string LgsErrHandler::formatMsg(const string& errMsg, const vector<string>& args) const {
    auto pos = 0;
    auto argIndex = 0;
    auto result = errMsg;
    while ((pos = result.find(ERROR_PLACEHOLDER, pos)) != string::npos && argIndex < args.size()) {
        result.replace(pos, ERROR_PLACEHOLDER.size(), args[argIndex]);
        pos += args[argIndex].length();
        argIndex++;
    }
    return result;
}
