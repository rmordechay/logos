#pragma once

class LgsErrHandler;
struct LgsLocation;
class LgsType;

void logInfo(const std::string& text = "");
void logErr(const std::string& text);
bool isLogosFile(const fs::directory_entry& entry);
bool isLLVMFile(const fs::directory_entry& entry);
bool isLogosKeyword(const std::string& s);
void cleanStr(std::string& value);
std::string getFileText(const fs::path& filePath);
std::string removeUnderscores(const std::string& input);
void freeType(const LgsType* type);
std::string getFullPath(const LgsLocation& location);
std::string getFullRelPath(const LgsLocation& location);