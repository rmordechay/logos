#include "../include/errors/LgsErrHandler.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include <algorithm>

void LgsErrHandler::setUnsuccessful() {
    successful = false;
}

void LgsErrHandler::addError(const LgsBaseMsg& lgsErr, const std::vector<std::string>& args) {
    setUnsuccessful();
    LgsError err(formatErrorMsg(lgsErr.msg, args), lgsErr.errCode);
    errors.emplace_back(err);
}

void LgsErrHandler::addError(const LgsBaseMsg& lgsErr, const LgsLocation* location, const std::string& filePath, const std::vector<std::string>& args) {
    setUnsuccessful();
    LgsError err(formatErrorMsg(lgsErr.msg, args), lgsErr.errCode);
    if (location) {
        err.location = *location;
        err.filePath = filePath;
        errors.emplace_back(err);
    } else {
        errors.emplace_back(err);
    }
}

void LgsErrHandler::addWarning(const LgsBaseMsg& lgsErr, const LgsLocation* location, const std::vector<std::string>& args) {
    const auto result = formatErrorMsg(lgsErr.msg, args);
    if (location) {
        warnings.emplace_back(LgsWarning(result, lgsErr.errCode, *location));
    } else {
        warnings.emplace_back(LgsWarning(result, lgsErr.errCode));
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

void LgsErrHandler::mergeErrorsWithLock(LgsErrHandler& other, std::mutex& mtx) {
    std::lock_guard lock(mtx);
    mergeErrors(other);
}

void LgsErrHandler::printErrors() const {
    for (size_t i = 0; i < errors.size(); ++i) {
        const auto err = errors[i];
        const auto column = err.location.columnStart;
        const auto line = err.location.lineStart;
        auto lineStr = getLine(err.filePath, line);
        const auto firstNonSpace = std::ranges::find_if(lineStr, [](const unsigned char c) { return !std::isspace(c); });
        const auto trimmedCount = std::distance(lineStr.begin(), firstNonSpace);
        if (err.filePath != "") {
            auto errMsg = trim(lineStr);
            int indent = column - trimmedCount - 2;
            if (indent < 0) {
                indent = 0;
            }
            errMsg += '\n' + std::string(indent, '~');
            errMsg += '^';
            int rest = lineStr.size() - column + 1;
            if (rest > 0) {
                errMsg += std::string(rest, '~');
            }
            errMsg += '\n' + err.msg;
            const auto path = "\n   at: " + getFullPath(err.location, err.filePath);
            logError(errMsg, path);
        } else {
            logError(err.msg);
        }
        if (i != errors.size() - 1) logInfo(LGS_MSG_LINE_SEPERATOR);
    }
    if (!errors.empty()) logInfo("\n");
}
