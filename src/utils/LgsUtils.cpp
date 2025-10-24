#include "utils/LgsUtils.h"
#include "LgsType.h"
#include "data/LgsDefinitions.h"
#include "data/LgsTokens.h"
#include "files/LgsFile.h"
#include "funcs/LgsParam.h"
#include "types/iterables/LgsStr.h"
#include <numeric>

#define FNV_PRIME 16777619
#define MAX_STR_HASH_LEN 1024
#define MSG_PLACEHOLDER "%s"

struct LgsFileMetadata;

void execute(std::vector<const char*> mainArgs, const fs::path& execPath) {
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

void logInfo(const std::string& text) {
    std::cout << text;
}

void logError(const std::string& errMsg, const std::string& suffix) {
    logInfo(prefixErrorLines(errMsg));
    if (suffix != "") logInfo(suffix);
}

void logWarning(const std::string& msg, const std::string& path) {
    logInfo(LGS_COLORIZE("Warning: ", LGS_MSG_COLOR_YELLOW));
    if (path != "") logInfo(path);
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

std::string prefixErrorLines(const std::string& text) {
    if (text.empty()) return LGS_ERROR_TEXT;
    std::string padding(std::strlen(LGS_ERROR_TEXT), ' ');
    std::stringstream input(text);
    std::stringstream result;
    std::string line;
    bool first = true;
    while (std::getline(input, line)) {
        if (first) {
            result << LGS_COLORIZE_ERROR(LGS_ERROR_TEXT) << line;
            first = false;
        } else {
            result << '\n' << padding << line;
        }
    }
    if (!text.empty() && text.back() == '\n') {
        result << '\n';
    }
    return result.str();
}

bool isLogosFile(const fs::path& filePath) {
    return fs::exists(filePath) && is_regular_file(filePath) && filePath.extension().string() == LGS_FILE_EXTENSION;
}

bool isLLVMFile(const fs::directory_entry& entry) {
    return entry.is_regular_file() && entry.path().extension().string() == ".ll";
}

bool isLogosKeyword(const std::string& s) {
    return LGS_KEYWORDS.find(s) != LGS_KEYWORDS.end();
}

std::string getFileText(const fs::path& filePath) {
    if (!fs::exists(filePath)) return "";
    std::ifstream file(filePath);
    if (!file.is_open()) return "";
    std::stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

bool fileExists(const fs::path& entry, const std::vector<LgsFileMetadata>& filesMetadata) {
    for (auto metadata : filesMetadata) {
        if (metadata.path == entry) {
            return true;
        }
    }
    return false;
}

void freeType(const LgsType* type) {
    if (!type) return;
    if (type->isPrimitive) return;
    // delete type;
}

void freeTypes(std::vector<LgsType*>& types) {
    for (const auto type : types) {
        freeType(type);
    }
    types.clear();
}

void freeExpr(LgsExpr* expr) {
    if (!expr) return;
    expr->type = nullptr;
    delete expr;
}

void freeExprs(std::vector<LgsExpr*>& exprs) {
    for (const auto expr : exprs) {
        freeExpr(expr);
    }
    exprs.clear();
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

size_t hashStr(const char* key) {
    size_t hash = 2166136261u;
    while (*key) {
        hash ^= static_cast<unsigned char>(*key++);
        hash *= FNV_PRIME;
        hash %= MAX_STR_HASH_LEN;
    }
    return hash;
}

bool startsWith(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
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

void combineNodeHash(size_t& oldHash, const size_t newHash) {
    oldHash ^= newHash + 0x9e3779b9 + (oldHash << 6) + (oldHash >> 2);
}

void hashNodeString(size_t& oldHash, const std::string& str) {
    combineNodeHash(oldHash, std::hash<std::string>{}(str));
}

void hashNodeInt(size_t& oldHash, const size_t val) {
    combineNodeHash(oldHash, std::hash<size_t>{}(val));
}

