#include "utils/LgsUtils.h"
#include "LgsType.h"
#include "data/LgsDefinitions.h"
#include "files/LgsFile.h"
#include "funcs/LgsParam.h"
#include "types/iterables/LgsStr.h"

#define FNV_PRIME 16777619
#define MAX_STR_HASH_LEN 1024
#define MSG_PLACEHOLDER "%s"
#define MSG_PADDING_PLACEHOLDER "%p"

const std::unordered_set<std::string> LOGOS_KEYWORDS = {"object", "single", "self", "Self", "interface", "extern", "pub", "implements", "const", "enum",  "vec2", "vec3", "vec4", "if", "else", "for", "break", "continue", "return", "and", "or", "not", "in"};

void logInfo(const std::string& text) {
    std::cout << text;
}

void logError(const std::string& msg, const std::string& path) {
    logInfo(LGS_ERROR_STR + msg);
    // logInfo(LGS_ERROR_STR + msg);
    if (path != "") logInfo(path);
}

void logWarning(const std::string& msg, const std::string& path) {
    logInfo(LGS_WARN_STR + msg);
    if (path != "") logInfo(path);
}

void formatAndLogError(const std::string& msg, const std::vector<std::string>& args) {
    logError(formatErrorMsg(msg, args) + '\n');
}

std::string formatErrorMsg(const std::string& msg, const std::vector<std::string>& args) {
    auto pos = 0;
    auto argIndex = 0;
    auto result = std::string(msg);
    while ((pos = result.find(MSG_PLACEHOLDER, pos)) != std::string::npos && argIndex < args.size()) {
        result.replace(pos, std::strlen(MSG_PLACEHOLDER), args[argIndex]);
        pos += args[argIndex].length();
        argIndex++;
    }
    pos = 0;
    argIndex = 0;
    while ((pos = result.find(MSG_PADDING_PLACEHOLDER, pos)) != std::string::npos) {
        result.replace(pos, std::strlen(MSG_PADDING_PLACEHOLDER), LGS_ERROR_PADDING);
        pos += args[argIndex].length();
        argIndex++;
    }
    return result;
}

bool isLogosFile(const fs::path& filePath) {
    return fs::exists(filePath) && is_regular_file(filePath) && filePath.extension().string() == LGS_FILE_EXTENSION;
}

bool isLLVMFile(const fs::directory_entry& entry) {
    return entry.is_regular_file() && entry.path().extension().string() == ".ll";
}

bool isLogosKeyword(const std::string& s) {
    return LOGOS_KEYWORDS.find(s) != LOGOS_KEYWORDS.end();
}

bool validateTypeType(const std::string& name) {
    return isupper(name[0]);
}

std::string getFileText(const fs::path& filePath) {
    if (!fs::exists(filePath)) return "";
    std::ifstream file(filePath);
    if (!file.is_open()) return "";
    std::stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

void freeType(LgsType* type) {
    if (!type) return;
    if (type->isPrimitive) return;
    if (type->isUnknown()) return;
    // delete type;
}

void freeExpr(LgsExpr* expr) {
    if (!expr) return;
    expr->type = nullptr;
    delete expr;
}

void freeTypes(std::vector<LgsType*>& types) {
    for (const auto type : types) {
        freeType(type);
    }
    types.clear();
}

void freeExprs(std::vector<LgsExpr*>& exprs) {
    for (const auto expr : exprs) {
        freeExpr(expr);
    }
    exprs.clear();
}

void freeParams(std::vector<LgsParam>& params) {
    for (int i = 0; i < params.size(); ++i) {
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
        if (currentLine == lineNumber) {
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


