#pragma once

class LgsErrHandler;
struct LgsLocation;
class LgsType;

enum LogLevel {
    INFO,
    DEBUG,
    ERROR,
};

void logInfo(const string& text);
void logErr(const string& text);
bool isLogosFile(const directory_entry& entry);
bool isLLVMFile(const directory_entry& entry);
bool isCharPointer(clang::QualType qt);
bool isLogosKeyword(const string& s);
void cleanStr(string& value);
string getFileText(path filePath);
string removeUnderscores(const string& input);
void freeType(const LgsType* type);
bool isBuiltinName(const string& name, const LgsLocation* location, LgsErrHandler& errHandler);
