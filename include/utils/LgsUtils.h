#pragma once

class LgsExpr;
struct LgsError;
struct LgsBaseError;
class LgsFile;
class LgsErrHandler;
struct LgsLocation;
class LgsType;

void logInfo(const std::string& text = "");
void logError(const std::string& msg, const std::string& path = "");
void formatAndLogError(const LgsBaseError& lgsErr, const std::vector<std::string>& args);
void formatErrorMsg(const LgsBaseError& lgsErr, const std::vector<std::string>& args, std::string& result);
bool isLogosFile(const fs::path& filePath);
bool isLLVMFile(const fs::directory_entry& entry);
bool isLogosKeyword(const std::string& s);
void cleanStr(std::string& value);
std::string getFileText(const fs::path& filePath);
std::string removeUnderscores(const std::string& input);
void freeType(LgsType* type);
void freeExpr(const LgsExpr* expr);
size_t hashStr(const char* key);
