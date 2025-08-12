#pragma once

class LgsErrHandler;
struct LgsLocation;
class LgsType;

void logInfo(const string& text = "");
void logErr(const string& text);
bool isLogosFile(const fs::directory_entry& entry);
bool isLLVMFile(const fs::directory_entry& entry);
bool isLogosKeyword(const string& s);
void cleanStr(string& value);
string getFileText(const fs::path& filePath);
string removeUnderscores(const string& input);
void freeType(const LgsType* type);
string getFullPath(const LgsLocation& location);