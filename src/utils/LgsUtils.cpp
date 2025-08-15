#include "utils/LgsUtils.h"
#include "LgsType.h"
#include "configs/LgsDefinitions.h"
#include "utils/LgsErrHandler.h"

const std::unordered_set<std::string> LOGOS_KEYWORDS = {"object", "single", "self", "Self", "interface", "extern", "pub", "implements", "const", "enum",  "vec2", "vec3", "vec4", "if", "else", "for", "break", "continue", "return", "and", "or", "not", "in"};

void logInfo(const std::string& text) {
    std::cout << text;
}

void logErr(const std::string& text) {
    std::cerr << text << '\n';
}

bool isLogosFile(const fs::directory_entry& entry) {
    return entry.is_regular_file() && entry.path().extension().string() == LGS_FILE_EXTENSION;
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

void freeType(const LgsType* type) {
    if (!type) return;
    if (type->isPrimitive) return;
    // delete type;
}

std::string getFullPath(const LgsLocation& location) {
    return std::string(location.filePath) + ":" + std::to_string(location.lineStart) + ":" + std::to_string(location.posInLine);
}

std::string getFullRelPath(const LgsLocation& location) {
    const auto pos = std::string(location.filePath).rfind(std::string(LGS_SRC_DIR));
    fs::path relPath;
    if (pos != std::string::npos) {
        relPath = std::string(location.filePath).substr(pos + std::strlen(LGS_SRC_DIR) + 1);
    }
    return std::string(relPath) + ":" + std::to_string(location.lineStart) + ":" + std::to_string(location.posInLine);
}