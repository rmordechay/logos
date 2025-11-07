#include "utils/LgsUtils.h"
#include "logos/LgsConfigs.h"
#include "LgsType.h"
#include "data/LgsDefinitions.h"
#include "data/LgsTokens.h"
#include "files/LgsFile.h"
#include "funcs/LgsParam.h"
#include <iostream>
#include <sstream>
#include <unistd.h>

struct LgsFileMetadata;

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

void logInfo(const std::string& text, const bool withNewLine) {
    if (withNewLine) std::cout << text << '\n';
    else std::cout << text;
}

void logDebug(const std::string& text, const bool withNewLine) {
    if (lgsConfigs.logLevel != LGS_DEBUG) return;
    if (withNewLine) std::cout << text << '\n';
    else std::cout << text;
}

std::string padErrorMsg(const std::string& text) {
    if (text.empty()) return LGS_ERROR_TEXT;
    std::string padding(std::strlen(LGS_ERROR_TEXT), ' ');
    std::stringstream input(text);
    std::stringstream result;
    std::string line;
    std::getline(input, line);
    result << LGS_COLORIZE_ERROR(LGS_ERROR_TEXT) << line;
    while (std::getline(input, line)) {
        result << '\n' << padding << line;
    }
    if (!text.empty() && text.back() == '\n') {
        result << '\n';
    }
    return result.str();
}

void logError(const std::string& errMsg, const std::string& epilogue) {
    const auto textWithErrors = padErrorMsg(errMsg);
    logInfo(textWithErrors);
    if (epilogue != "") logInfo(epilogue);
}

void logWarning(const std::string& msg, const std::string& path) {
    logInfo(LGS_COLORIZE("Warning: ", LGS_MSG_COLOR_YELLOW));
    if (path != "") logInfo(path);
}

bool isLogosFile(const fs::path& filePath) {
    return fs::exists(filePath) && is_regular_file(filePath) && filePath.extension().string() == LGS_FILE_EXTENSION;
}

bool isLogosKeyword(const std::string& s) {
    return LGS_KEYWORDS.contains(s);
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
    const auto start = std::find_if(str.begin(), str.end(), [](const unsigned char ch) {
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

time_t getLastWritten(const fs::path& filePath) {
    assert(fs::exists(filePath));
    const auto ftime = fs::last_write_time(filePath);
    const auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now()
        );
    return std::chrono::system_clock::to_time_t(sctp);
}

bool validateFilePath(fs::path& filePath) {
    if (!fs::exists(filePath)) return false;
    filePath = fs::canonical(filePath);
    return true;
}

bool createDir(fs::path& dirPath) {
    if (fs::exists(dirPath)) return true;
    if (!fs::create_directory(dirPath)) return false;
    dirPath = fs::canonical(dirPath);
    return true;
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

void combineNodeHash(size_t& oldHash, const size_t newHash) {
    oldHash ^= newHash + 0x9e3779b9 + (oldHash << 6) + (oldHash >> 2);
}

void hashNodeString(size_t& oldHash, const std::string& str) {
    combineNodeHash(oldHash, std::hash<std::string>{}(str));
}

void hashNodeInt(size_t& oldHash, const size_t val) {
    combineNodeHash(oldHash, std::hash<size_t>{}(val));
}

void freeExpr(const LgsExpr* expr) {
    if (!expr) return;
    delete expr;
}

void freeExprs(std::vector<LgsExpr*>& exprs) {
    for (const auto expr : exprs) {
        freeExpr(expr);
    }
    exprs.clear();
}

void freeStmt(const LgsStmt* stmt) {
    if (!stmt) return;
    delete stmt;
}

void freeParams(std::vector<LgsParam>& params) {
    for (size_t i = 0; i < params.size(); ++i) {
        const auto param = params[i];
        if (param.expr) {
            freeExpr(param.expr);
        } else if (param.type) {
            freeType(param.type);
        }
    }
    params.clear();
}

void freeType(const LgsType* type) {
    if (!type) return;
    if (type->isPrimitive) return;
    delete type;
}
