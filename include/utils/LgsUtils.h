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
struct LgsBaseMsg;
class LgsFile;
class LgsErrHandler;
struct LgsLocation;
class LgsType;
namespace fs = std::filesystem;

#define EXPECTED_ERR(E, code) "Expected error: '" << std::string(E.msg) << "'" << std::string(code)
#define HASH_VECTOR(vec, hash) for (const auto e : vec) e->hashNode(hash)
#define HASH_MAP(map, hash) for (const auto [_, v] : map) v->hashNode(hash)

void execute(const fs::path& execPath, std::vector<const char*> mainArgs = {});
bool runCmd(const char* cmd);
bool createDir(fs::path& dirPath);
bool isLogosFile(const fs::path& filePath);
bool isLogosKeyword(const std::string& s);
void printCliError(const LgsBaseMsg& err, const std::vector<std::string>& args = {});
std::string formatErrorMsg(const std::string& msg, const std::vector<std::string>& args);

std::string getFileText(const fs::path& filePath);
std::string getLine(const std::string& filename, size_t lineNumber);
std::string trim(const std::string& str);
std::string getFullPath(const LgsLocation& location, const std::string& filePath);
std::string scanEscapeStr(const std::string& value);
int32_t hashString(const std::string& str);
time_t getLastWritten(const fs::path& filePath);

void logInfo(const std::string& msg = "", bool withNewLine = false);
void logDebug(const std::string& msg, bool withNewLine = false);
void logError(const std::string& msg, const std::string& epilogue = "");
void logWarning(const std::string& msg);

void combineNodeHash(size_t& oldHash, size_t newHash);
void hashNodeString(size_t& oldHash, const std::string& str);
void hashNodeInt(size_t& oldHash, size_t val);

void freeExpr(LgsExpr* expr);
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
