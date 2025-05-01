#include "LgsErrorHandler.h"
#include "LgsGlobals.h"
#include <iostream>

#define ERROR_STR "\033[1;31mError:\033[0m "

void LgsErrorHandler::setUnsuccessful() {
    successful = false;
}

void LgsErrorHandler::handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args) {
    setUnsuccessful();
    const auto errMsg = formatMsg(lgsErr.msg, args);
    errors.emplace_back(LgsError{.msg = errMsg, .errCode = lgsErr.errCode});
    cout <<  ERROR_STR << errMsg << endl;
    if (location) {
        const auto lineNumber = to_string(location->lineNumber);
        const auto pos = to_string(location->posInLine);
        assert(filePath != "");
        const auto fullPath = filePath.string() + ":" + lineNumber + ":" + pos;
        const auto path = "\t   at " + fullPath;
        cout << path << "\n---" << endl;
    }
}

string LgsErrorHandler::formatMsg(const string& errMsg, const vector<string>& args) const {
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
