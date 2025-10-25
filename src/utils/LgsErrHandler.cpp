#include "utils/LgsErrHandler.h"
#include "codegen/LgsLLVMGen.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"

void LgsErrHandler::setUnsuccessful() {
    successful = false;
}

void LgsErrHandler::addError(const LgsBaseError& lgsErr, const LgsLocation* location, const std::vector<std::string>& args) {
    setUnsuccessful();
    LgsError err(formatErrorMsg(lgsErr.msg, args), lgsErr.code);
    if (location) {
        err.location = *location;
        errors.emplace_back(err);
    } else {
        errors.emplace_back(err);
    }
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

void LgsErrHandler::exitWithErrors() const {
    for (size_t i = 0; i < errors.size(); ++i) {
        const auto err = errors[i];
        const auto column = err.location.columnStart;
        const auto line = err.location.lineStart;
        auto lineStr = getLine(err.filePath, line);
        const auto firstNonSpace = std::find_if(lineStr.begin(), lineStr.end(), [](const unsigned char c) { return !std::isspace(c); });
        const auto trimmedCount = std::distance(lineStr.begin(), firstNonSpace);
        auto errMsg = trim(lineStr);
        errMsg += '\n' + std::string(column - trimmedCount - 2, '~');
        errMsg += '^';
        int rest = lineStr.size() - column + 1;
        if (rest > 0) {
            errMsg += std::string(rest, '~');
        }
        errMsg += '\n' + err.msg;
        const auto path = "\n   at: " + getFullPath(err.location, err.filePath);
        logError(errMsg, path);
        if (i != errors.size() - 1) logInfo(LGS_MSG_LINE_SEPERATOR);
    }
    if (!errors.empty()) logInfo("\n");
    exit(EXIT_FAILURE);
}
