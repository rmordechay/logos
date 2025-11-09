#include "utils/LgsErrHandler.h"
#include "codegen/LgsLLVMGen.h"
#include "data/LgsDefinitions.h"
#include "logos/LgsApp.h"
#include "utils/LgsUtils.h"
#include <iostream>

std::string formatErrorMsg(const std::string& msg, const std::vector<std::string>& args);

void LgsErrHandler::setUnsuccessful() {
    successful = false;
}

void LgsErrHandler::addError(const LgsBaseError& lgsErr, const std::vector<std::string>& args) {
    setUnsuccessful();
    LgsError err(formatErrorMsg(lgsErr.msg, args), lgsErr.code);
    errors.emplace_back(err);
}

void LgsErrHandler::addError(const LgsBaseError& lgsErr, const LgsLocation* location, const std::string& filePath, const std::vector<std::string>& args) {
    setUnsuccessful();
    LgsError err(formatErrorMsg(lgsErr.msg, args), lgsErr.code);
    if (location) {
        err.location = *location;
        err.filePath = filePath;
        errors.emplace_back(err);
    } else {
        errors.emplace_back(err);
    }
}

void LgsErrHandler::addWarning(const LgsBaseError& lgsErr, const LgsLocation* location, const std::vector<std::string>& args) {
    const auto result = formatErrorMsg(lgsErr.msg, args);
    if (location) {
        warnings.emplace_back(LgsWarning(result, lgsErr.code, *location));
    } else {
        warnings.emplace_back(LgsWarning(result, lgsErr.code));
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

void LgsErrHandler::mergeErrorsWithLock(LgsErrHandler& other) {
    std::lock_guard lock(mtx);
    mergeErrors(other);
}

void exitWithErrors(LgsErrHandler& errHandler) {
    for (size_t i = 0; i < errHandler.errors.size(); ++i) {
        const auto err = errHandler.errors[i];
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
        if (i != errHandler.errors.size() - 1) logInfo(LGS_MSG_LINE_SEPERATOR);
    }
    if (!errHandler.errors.empty()) logInfo("\n");
    exit(EXIT_FAILURE);
}

void exitWithError(const LgsBaseError& err, const std::vector<std::string>& args) {
    const auto errMsg = formatErrorMsg(err.msg, args) + '\n';
    logError(errMsg);
    exit(EXIT_FAILURE);
}

std::string formatErrorMsg(const std::string& msg, const std::vector<std::string>& args) {
    size_t pos = 0;
    size_t argIndex = 0;
    auto result = std::string(msg);
    while ((pos = result.find(MSG_PLACEHOLDER, pos)) != std::string::npos && argIndex < args.size()) {
        result.replace(pos, std::strlen(MSG_PLACEHOLDER), args[argIndex]);
        pos += args[argIndex].length();
        argIndex++;
    }
    return result;
}
