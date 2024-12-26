#ifndef LOGOSFILE_H
#define LOGOSFILE_H
#include "LogosParser.h"


#include <filesystem>
#include <string>

class LogosFile {
public:
    std::string code;
    std::string name;
    std::string path;
    LogosParser::LogosFileContext* fileCtx;

    explicit LogosFile(const std::string& code, const std::filesystem::path& path);
    void parseFile();
};

#endif //LOGOSFILE_H
