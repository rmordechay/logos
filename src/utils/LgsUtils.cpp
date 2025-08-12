#include "utils/LgsUtils.h"
#include "LgsType.h"
#include "configs/LgsDefinitions.h"
#include "utils/LgsErrHandler.h"

const unordered_set<string> LOGOS_KEYWORDS = {"object", "single", "self", "Self", "interface", "extern", "pub", "implements", "const", "enum",  "vec2", "vec3", "vec4", "if", "else", "for", "break", "continue", "return", "and", "or", "not", "in"};

void logInfo(const string& text) {
    cout << text;
}

void logErr(const string& text) {
    cerr << text << '\n';
}

bool isLogosFile(const fs::directory_entry& entry) {
    return entry.is_regular_file() && entry.path().extension().string() == LGS_FILE_EXTENSION;
}

bool isLLVMFile(const fs::directory_entry& entry) {
    return entry.is_regular_file() && entry.path().extension().string() == ".ll";
}

bool isLogosKeyword(const string& s) {
    return LOGOS_KEYWORDS.find(s) != LOGOS_KEYWORDS.end();
}

void cleanStr(string& value) {
    value.erase(0, 1);
    value.pop_back();
}

string getFileText(fs::path filePath) {
    if (!fs::exists(filePath)) return "";
    ifstream file(filePath);
    if (!file.is_open()) return "";
    stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

string removeUnderscores(const string& input) {
    string result = input;
    result.erase(remove(result.begin(), result.end(), '_'), result.end());
    return result;
}

void freeType(const LgsType* type) {
    if (!type) return;
    if (type->isPrimitive) return;
    delete type;
}

string getFullPath(const LgsLocation& location) {
    return string(location.filePath) + ":" + to_string(location.lineStart) + ":" + to_string(location.posInLine);
}