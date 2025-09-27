#include "utils/LgsUtils.h"
#include "LgsType.h"
#include "data/LgsDefinitions.h"
#include "files/LgsFile.h"
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
    result = LGS_ERROR_PADDING + result;
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

void freeExpr(LgsExpr* expr) {
    if (!expr) return;
    expr->type = nullptr;
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

std::string getTextFromFile(const std::string& filename, const LgsLocation& location) {
    std::ifstream file(filename, std::ios::binary);
    const auto start = location.indexStart;
    const auto end = location.indexEnd;
    if (start >= end) return "";
    file.seekg(start);
    std::string result(end - start, '\0');
    file.read(result.data(), end - start);
    return result;
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
    return filePath + ":" + std::to_string(location.lineStart) + ":" + std::to_string(location.posInLine);
}

std::string getOpAsText(const LgsOperator op) {
    switch (op) {
    case ADD:
        return "+";
    case SUB:
        return "-";
    case MUL:
        return "*";
    case DIV:
        return "/";
    case MOD:
        return "%";
    case EQ:
        return "==";
    case NE:
        return "!=";
    case LT:
        return "<";
    case GT:
        return ">";
    case GE:
        return ">=";
    case LE:
        return "<=";
    case AND:
        return "and";
    case OR:
        return "or";
    case BIT_AND:
        return "&";
    case BIT_OR:
        return "|";
    case BIT_XOR:
        return "^";
    case LSHIFT:
        return "<<";
    case RSHIFT:
        return ">>";
    case IN:
        return "in";
    case NOOP:
        break;
    }
    return "NOOP";
}
