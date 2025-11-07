#pragma once
#include <filesystem>
#include <vector>

class LgsStmt;
struct LgsFileMetadata;
struct LgsAppConfigs;
class LgsParam;
class LgsSubType;
class LgsExpr;
struct LgsError;
struct LgsBaseError;
class LgsFile;
class LgsErrHandler;
struct LgsLocation;
class LgsType;
namespace fs = std::filesystem;

#define EXPECTED_ERR(E, code) "Expected error: '" << std::string(E.msg) << "'" << std::string(code)
#define HASH_VECTOR(vec, hash) for (const auto e : vec) e->hashNode(hash)
#define HASH_MAP(map, hash) for (const auto [_, v] : map) v->hashNode(hash)

void execute(const fs::path& execPath, std::vector<const char*> mainArgs = {});
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
size_t hashStr(const std::string& key);
bool startsWith(const std::string& str, const std::string& prefix);
std::string getLine(const std::string& filename, size_t lineNumber);
std::string trim(const std::string& str);
std::string getFullPath(const LgsLocation& location, const std::string& filePath);
void combineNodeHash(size_t& oldHash, size_t newHash);
void hashNodeString(size_t& oldHash, const std::string& str);
void hashNodeInt(size_t& oldHash, size_t val);
time_t getLastWritten(const fs::path& filePath);

void freeExpr(const LgsExpr* expr);
void freeExprs(std::vector<LgsExpr*>& exprs);
void freeStmt(const LgsStmt* stmt);
void freeParams(std::vector<LgsParam>& params);
void freeType(const LgsType* type);
template<typename T>
void freeTypes(std::vector<T*>& types) {
    for (const auto type : types) {
        freeType(static_cast<LgsType*>(type));
    }
    types.clear();
}
