#pragma once
#include "exprs/LgsBinaryExpr.h"

class LgsExpr;
struct LgsError;
struct LgsBaseError;
class LgsFile;
class LgsErrHandler;
struct LgsLocation;
class LgsType;

#define EXPECTED_ERR(E, code) "Expected error: '" << std::string(E.msg) << "'" << std::string(code)

void logInfo(const std::string& text = "");
void logError(const std::string& msg, const std::string& path = "");
void formatAndLogError(const LgsBaseError& lgsErr, const std::vector<std::string>& args = {});
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
bool startsWith(const std::string& str, const std::string& prefix);
std::string getTextFromFile(const std::string& filename, const LgsLocation& location);
std::string getLine(const std::string& filename, size_t lineNumber);
std::string trim(const std::string& str);
std::string getFullPath(const LgsLocation& location, const std::string& filePath);
std::string getOpAsText(LgsOperator op);
