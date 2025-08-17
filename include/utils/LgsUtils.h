#pragma once

struct LgsError;
struct LgsBaseError;
class LgsFile;
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
void freeType(LgsType* type);
size_t hashStr(const char* key);
void formatErrorMsg(const LgsBaseError& lgsErr, const std::vector<std::string>& args, std::string& result);
void logError(const LgsError& err, const std::string& path);
