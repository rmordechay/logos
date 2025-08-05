#pragma once

class LgsErrHandler;
struct LgsLocation;
class LgsType;

void logInfo(const string& text);
void logErr(const string& text);
bool isLogosFile(const filesystem::directory_entry& entry);
bool isLLVMFile(const filesystem::directory_entry& entry);
bool isLogosKeyword(const string& s);
void cleanStr(string& value);
string getFileText(filesystem::path filePath);
string removeUnderscores(const string& input);
void freeType(const LgsType* type);
bool isBuiltinName(const string& name, const LgsLocation* location, LgsErrHandler& errHandler);
string getFullPath(const LgsLocation& location);
