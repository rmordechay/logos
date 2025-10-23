#pragma once

struct LgsFileMetadata;
struct LgsAppConfigs;
class LgsParam;
class LgsExpr;
struct LgsError;
struct LgsBaseError;
class LgsFile;
class LgsErrHandler;
struct LgsLocation;
class LgsType;

#define EXPECTED_ERR(E, code) "Expected error: '" << std::string(E.msg) << "'" << std::string(code)

void execute(std::vector<const char*> mainArgs, const fs::path& execPath);
void logInfo(const std::string& text = "");
void logError(const std::string& errMsg, const std::string& suffix = "");
void logWarning(const std::string& msg, const std::string& path);
void exitWithError(const LgsBaseError& err, const std::vector<std::string>& args = {});
std::string formatErrorMsg(const std::string& msg, const std::vector<std::string>& args);
std::string prefixErrorLines(const std::string& text);
bool isLogosFile(const fs::path& filePath);
bool isLLVMFile(const fs::directory_entry& entry);
bool isLogosKeyword(const std::string& s);
std::string getFileText(const fs::path& filePath);
bool fileExists(const fs::path& entry, const std::vector<LgsFileMetadata>& filesMetadata);
void freeType(const LgsType* type);
void freeTypes(std::vector<LgsType*>& types);
void freeExpr(LgsExpr* expr);
void freeExprs(std::vector<LgsExpr*>& exprs);
void freeParams(std::vector<LgsParam>& params);
size_t hashStr(const char* key);
bool startsWith(const std::string& str, const std::string& prefix);
std::string getLine(const std::string& filename, size_t lineNumber);
std::string trim(const std::string& str);
std::string getFullPath(const LgsLocation& location, const std::string& filePath);
void combineHash(size_t& oldHash, size_t newHash);
void hashString(size_t& oldHash, const std::string& str);
void hashInt(size_t& oldHash, size_t val);