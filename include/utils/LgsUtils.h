#pragma once

class LgsParam;
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
void logWarning(const std::string& msg, const std::string& path);
void formatAndLogError(const std::string& msg, const std::vector<std::string>& args = {});
std::string formatErrorMsg(const std::string& msg, const std::vector<std::string>& args);
bool isLogosFile(const fs::path& filePath);
bool isLLVMFile(const fs::directory_entry& entry);
bool isLogosKeyword(const std::string& s);
bool validateTypeType(const std::string& name);
std::string getFileText(const fs::path& filePath);
void freeType(LgsType* type);
void freeTypes(std::vector<LgsType*>& types);
void freeExpr(LgsExpr* expr);
void freeExprs(std::vector<LgsExpr*>& exprs);
void freeParams(std::vector<LgsParam>& params);
size_t hashStr(const char* key);
bool startsWith(const std::string& str, const std::string& prefix);
std::string getLine(const std::string& filename, size_t lineNumber);
std::string trim(const std::string& str);
std::string getFullPath(const LgsLocation& location, const std::string& filePath);