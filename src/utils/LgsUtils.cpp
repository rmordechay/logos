#include "utils/LgsUtils.h"
#include "LgsType.h"
#include "configs/LgsDefinitions.h"
#include "files/LgsFile.h"
#include "types/LgsStr.h"

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
    if (path != "") {
        logInfo(path);
    }
}

void formatAndLogError(const LgsBaseError& lgsErr, const std::vector<std::string>& args) {
    std::string msg;
    formatErrorMsg(lgsErr, args, msg);
    logError(msg + '\n');
}

void formatErrorMsg(const LgsBaseError& lgsErr, const std::vector<std::string>& args, std::string& result) {
    auto pos = 0;
    auto argIndex = 0;
    result = std::string(lgsErr.msg);
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

void cleanStr(std::string& value) {
    value.erase(0, 1);
    value.pop_back();
}

std::string getFileText(const fs::path& filePath) {
    if (!fs::exists(filePath)) return "";
    std::ifstream file(filePath);
    if (!file.is_open()) return "";
    std::stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

std::string removeUnderscores(const std::string& input) {
    std::string result = input;
    result.erase(remove(result.begin(), result.end(), '_'), result.end());
    return result;
}

void freeType(LgsType* type) {
    if (!type) return;
    if (type->isPrimitive) return;
    if (type->isUnknown()) return;
    // delete type;
}

void freeExpr(const LgsExpr* expr) {
    if (!expr) return;
    delete expr;
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
