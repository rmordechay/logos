#include "utils/LgsUtils.h"
#include "LgsType.h"
#include "builtins/LgsBuiltins.h"
#include "configs/LgsDefinitions.h"
#include "configs/PlatformData.h"
#include "utils/LgsErrHandler.h"

const unordered_set<string> LOGOS_KEYWORDS = {"object", "single", "self", "Self", "interface", "extern", "pub", "implements", "const", "enum",  "vec2", "vec3", "vec4", "if", "else", "for", "break", "continue", "return", "and", "or", "not", "in"};

void logInfo(const string& text) {
    cout << text << NEW_LINE;
}

void logErr(const string& text) {
    cerr << text << NEW_LINE;
}

bool isLogosFile(const filesystem::directory_entry& entry) {
    return entry.is_regular_file() && entry.path().extension().string() == LOGOS_FILE_EXTENSION;
}

bool isLLVMFile(const filesystem::directory_entry& entry) {
    return entry.is_regular_file() && entry.path().extension().string() == ".ll";
}

bool isLogosKeyword(const string& s) {
    return LOGOS_KEYWORDS.find(s) != LOGOS_KEYWORDS.end();
}

void cleanStr(string& value) {
    value.erase(0, 1);
    value.pop_back();
}

string getFileText(filesystem::path filePath) {
    if (!filesystem::exists(filePath)) return "";
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

bool isBuiltinName(const string& name, LgsLocation* location, LgsErrHandler& errHandler) {
    const auto isLgsBuiltin = name == LgsSizeOf::name || name == LgsPrint::name || name == LgsSystem::name;
    if (isLgsBuiltin) {
        errHandler.addError(E10053, location, {name});
        return true;
    }
    return false;
}

string getFullPath(const char* filePath, const int32_t lineStart, const int32_t posStart) {
    return string(filePath) + ":" + to_string(lineStart) + ":" + to_string(posStart);
}

string getFullPath(const LgsLocation& location) {
    return getFullPath(location.filePath, location.lineStart, location.posStart);
}

void findLibC() {
    clang::DiagnosticsEngine diags(new clang::DiagnosticIDs(), new clang::DiagnosticOptions(), new clang::DiagnosticConsumer());
    const auto vfs = vfs::getRealFileSystem();
    const auto target_triple = sys::getDefaultTargetTriple();
    auto driver = clang::driver::Driver("clang", target_triple, diags, "clang", vfs);
    const auto args = {"clang", "-c", "dummy.c"};
    const auto compilation = std::unique_ptr<clang::driver::Compilation>(driver.BuildCompilation(args));
    auto& toolChain = compilation->getDefaultToolChain();
    std::cout << driver.getClangProgramPath() << std::endl;
    std::cout << driver.ResourceDir << std::endl;
    std::cout << driver.SystemConfigDir << std::endl;
    std::cout << toolChain.getOSLibName().front() << std::endl;
}
