#include "LgsUtils.h"
#include "LgsConfigs.h"
#include "LgsDefinitions.h"
#include "LgsTokens.h"
#include "errors/LgsErrors.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <unistd.h>

void execute(const fs::path& execPath, std::vector<const char*> mainArgs) {
    const auto path = const_cast<char*>(execPath.c_str());
    mainArgs.insert(mainArgs.begin(), path);
    if (mainArgs.empty() || mainArgs.back() != nullptr) {
        mainArgs.push_back(nullptr);
    }
    std::vector<char*> argv;
    argv.reserve(mainArgs.size());
    for (const auto arg : mainArgs) {
        argv.push_back(const_cast<char*>(arg));
    }
    execv(path, argv.data());
    perror("Logos execution failed.");
    exit(EXIT_FAILURE);
}

std::string padAndColorErrorMsg(const std::string& text) {
    if (text.empty()) return LGS_ERROR_TEXT;
    std::string padding(std::strlen(LGS_ERROR_TEXT), ' ');
    std::stringstream input(text);
    std::stringstream result;
    std::string line;
    std::getline(input, line);
    result << LGS_COLORIZE(LGS_ERROR_TEXT, LGS_MSG_COLOR_RED) << line;
    while (std::getline(input, line)) {
        result << '\n' << padding << line;
    }
    if (!text.empty() && text.back() == '\n') {
        result << '\n';
    }
    return result.str();
}

bool runCmd(const char* cmd) {
    switch (lgsConfigs.os) {
    case MAC_OS:
    case LINUX:
        return std::system(cmd) == 0;
    case WINDOWS:
    case UNKNOWN_OS:
        break;
    }
    assert(0);
}

bool createDir(fs::path& dirPath) {
    if (fs::exists(dirPath)) return true;
    if (!fs::create_directory(dirPath)) return false;
    dirPath = fs::canonical(dirPath);
    return true;
}

bool isLogosFile(const fs::path& filePath) {
    return fs::exists(filePath) && is_regular_file(filePath) && filePath.extension().string() == LGS_FILE_EXTENSION;
}

std::string getFileText(const fs::path& filePath) {
    if (!fs::exists(filePath)) return "";
    std::ifstream file(filePath);
    if (!file.is_open()) return "";
    std::stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

std::string getLine(const std::string& filename, const size_t lineNumber) {
    std::ifstream file(filename);
    std::string line;
    int currentLine = 1;
    while (std::getline(file, line)) {
        if (static_cast<size_t>(currentLine) == lineNumber) {
            break;
        }
        currentLine++;
    }
    file.close();
    const auto commentPos = line.find("//");
    if (commentPos != std::string::npos) {
        return line.substr(0, commentPos);
    }
    return line;
}

std::string trim(const std::string& str) {
    const auto start = std::ranges::find_if(str, [](const unsigned char ch) {
        return !std::isspace(ch);
    });
    const auto end = std::find_if(str.rbegin(), str.rend(), [](const unsigned char ch) {
        return !std::isspace(ch);
    }).base();
    return start < end ? std::string(start, end) : std::string();
}

std::string getFullPath(const LgsLocation& location, const std::string& filePath) {
    return filePath + ":" + std::to_string(location.lineStart) + ":" + std::to_string(location.columnStart);
}

std::string scanEscapeStr(const std::string& value) {
    std::string out;
    out.reserve(value.size());
    for (unsigned char c : value) {
        switch (c) {
        case '\n': out += "\\n"; break;
        case '\t': out += "\\t"; break;
        case '\r': out += "\\r"; break;
        case '\\': out += "\\\\"; break;
        case '\"': out += "\\\""; break;
        case '\'': out += "\\\'"; break;
        case '\b': out += "\\b"; break;
        case '\f': out += "\\f"; break;
        case '\v': out += "\\v"; break;
        case '\0': out += "\\0"; break;
        default: out += c; break;
        }
    }
    return out;
}

size_t hashString(const std::string& str) {
    assert(str != "");
    return std::hash<std::string_view>{}(str);
}

time_t getLastWritten(const fs::path& filePath) {
    assert(fs::exists(filePath));
    const auto ftime = fs::last_write_time(filePath);
    const auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now()
    );
    return std::chrono::system_clock::to_time_t(sctp);
}

void logInfo(const std::string& msg, const bool withNewLine) {
    if (withNewLine) std::cout << msg << '\n';
    else std::cout << msg;
}

void logDebug(const std::string& msg, const bool withNewLine) {
    if (lgsConfigs.logLevel != LGS_DEBUG) return;
    if (withNewLine) std::cout << msg << '\n';
    else std::cout << msg;
}

void logError(const std::string& msg, const std::string& epilogue) {
    const auto textWithErrors = padAndColorErrorMsg(msg);
    logInfo(textWithErrors);
    if (epilogue != "") logInfo(epilogue);
}

void logWarning(const std::string& msg) {
    logInfo(LGS_COLORIZE(LGS_WARNING_TEXT, LGS_MSG_COLOR_YELLOW) + msg);
}

void printCliError(const LgsBaseMsg& err, const std::vector<std::string>& args) {
    const auto errMsg = formatErrorMsg(err.msg, args) + '\n';
    logError(errMsg);
}

std::string formatErrorMsg(const char* msg, const std::vector<std::string>& args) {
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

void formatErrorMsg(const char* msg, char* out, const size_t count, va_list args) {
    std::string result(msg);
    size_t pos = 0;
    for (size_t i = 0; i < count; i++) {
        const auto arg = va_arg(args, const char*);
        pos = result.find(MSG_PLACEHOLDER, pos);
        if (pos == std::string::npos) break;
        result.replace(pos, strlen(MSG_PLACEHOLDER), arg);
        pos += strlen(arg);
    }
    std::strncpy(out, result.c_str(), LGS_STR_BUFFER_SIZE - 1);
    out[LGS_STR_BUFFER_SIZE - 1] = '\0';
}

void combineNodeHash(size_t& oldHash, const size_t newHash) {
    oldHash ^= newHash + 0x9e3779b9 + (oldHash << 6) + (oldHash >> 2);
}

void hashNodeString(size_t& oldHash, const std::string& str) {
    combineNodeHash(oldHash, hashString(str));
}

void hashNodeInt(size_t& oldHash, const size_t val) {
    combineNodeHash(oldHash, val);
}
