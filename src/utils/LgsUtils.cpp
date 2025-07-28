#include "utils/LgsUtils.h"
#include "LgsType.h"
#include "builtin/LgsBuiltins.h"
#include "data/LgsDefinitions.h"
#include "data/PlatformData.h"
#include "utils/LgsErrHandler.h"


void a() {
    vector<string> strings = {
        "apple", "banana", "cherry", "date", "elderberry"
    };

    unordered_map<string, streampos> stringOffsets;

    ofstream out("strings.dat", ios::binary);
    for (const auto& str : strings) {
        const auto pos = out.tellp();
        auto len = str.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(str.data(), len);
        stringOffsets[str] = pos;
    }
    out.close();

    // Debug: print offsets
    for (const auto& [s, offset] : stringOffsets) {
        cout << s << " at " << offset << "\n";
    }
}

void logInfo(const string& text) {
    cout << text << NEW_LINE;
}

void logErr(const string& text) {
    cerr << text << NEW_LINE;
}

bool isLogosFile(const directory_entry& entry) {
    return entry.is_regular_file() && entry.path().extension().string() == LOGOS_FILE_EXTENSION;
}

bool isLLVMFile(const directory_entry& entry) {
    return entry.is_regular_file() && entry.path().extension().string() == ".ll";
}

bool isCharPointer(const clang::QualType qt) {
    if (!qt->isPointerType()) return false;
    const auto pointeeType = qt->getPointeeType();
    return pointeeType->isCharType();
}

bool isLogosKeyword(const string& s) {
    return LOGOS_KEYWORDS.find(s) != LOGOS_KEYWORDS.end();
}

void cleanStr(string& value) {
    value.erase(0, 1);
    value.pop_back();
}

string getFileText(path filePath) {
    if (!exists(filePath)) return "";
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
    // delete type;
}

bool isBuiltinName(const string& name, const Location* location, LgsErrHandler& errHandler) {
    const auto isLgsBuiltin = name == LgsSizeOf::name || name == LgsPrint::name;
    if (isLgsBuiltin) {
        errHandler.handleError(E10053, location, {name});
        return true;
    }
    return false;
}
