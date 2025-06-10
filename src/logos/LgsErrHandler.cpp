#include "LgsLocation.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"


void LgsErrHandler::setUnsuccessful() {
    successful = false;
}

void LgsErrHandler::handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args) {
    setUnsuccessful();
    const auto errMsg = formatMsg(lgsErr.msg, args);
    errors.emplace_back(LgsError{.msg = errMsg, .errCode = lgsErr.errCode});
    lock_guard lock(mtx);
    cout <<  ERROR_STR << errMsg << endl;
    if (location) {
        const auto fullPath = location->getFullPath(filePath);
        const auto path = "\t   at " + fullPath;
        cout << path << "\n---" << endl;
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
