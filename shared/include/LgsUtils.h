#pragma once
#include <filesystem>
#include <vector>

struct LgsBaseMsg;
struct LgsLocation;
namespace fs = std::filesystem;

#define EXPECTED_ERR(E, code) "Expected error: '" << std::string(E.msg) << "'" << std::string(code)
#define HASH_VECTOR(vec, hash) for (const auto e : vec) e->hashNode(hash)
#define HASH_MAP(map, hash) for (const auto [_, v] : map) v->hashNode(hash)

void execute(const fs::path& execPath, std::vector<const char*> mainArgs = {});
bool runCmd(const char* cmd);
bool createDir(fs::path& dirPath);
bool isLogosFile(const fs::path& filePath);

std::string getFileText(const fs::path& filePath);
std::string getLine(const std::string& filename, size_t lineNumber);
std::string trim(const std::string& str);
std::string getFullPath(const LgsLocation& location, const std::string& filePath);
std::string scanEscapeStr(const std::string& value);
uint64_t hashString(const std::string& str);
time_t getLastWritten(const fs::path& filePath);

void logInfo(const std::string& msg = "", bool withNewLine = false);
void logDebug(const std::string& msg, bool withNewLine = false);
void logError(const std::string& msg, const std::string& epilogue = "");
void logWarning(const std::string& msg);
void printCliError(const LgsBaseMsg& err, const std::vector<std::string>& args = {});
std::string formatErrorMsg(const char* msg, const std::vector<std::string>& args);
void formatErrorMsg(const char* msg, char* out, const size_t count, va_list args);

void combineNodeHash(size_t& oldHash, size_t newHash);
void hashNodeString(size_t& oldHash, const std::string& str);
void hashNodeInt(size_t& oldHash, size_t val);
