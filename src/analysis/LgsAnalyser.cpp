#include "analysis/LgsAnalyser.h"

#include "CodeGenMetadata.h"
#include "LgsFile.h"

string LgsAnalyser::formatMsg(const string& errMsg, const vector<string>& args) const {
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

void LgsAnalyser::handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args) {
    setUnsuccessful();
    const auto errMsg = formatMsg(lgsErr.msg, args);
    errors.emplace_back(LgsError{.errCode = lgsErr.errCode, .msg = errMsg});
    cout <<  "Error: "  << errMsg << endl;
    if (location) {
        assert(location->lineNumber != 0);
        const auto lineNumber = to_string(location->lineNumber);
        const auto pos = to_string(location->posInLine);
        const auto fullPath = file->absPath + ":" + lineNumber + ":" + pos;
        const auto path = "\tat " + fullPath;
        cout << path << endl;
    }
}

void LgsAnalyser::setUnsuccessful() {
    successful = false;
}