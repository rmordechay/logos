#ifndef LOGOSPACKAGE_H
#define LOGOSPACKAGE_H
#include "LogosFile.h"

#include <string>
#include <vector>

class LogosPackage {
public:
    std::string name;
    std::string path;
    std::vector<LogosFile*> files;
    std::vector<LogosPackage*> packages;
    LogosFile* mainFile;

    explicit LogosPackage(const std::string& name, const std::string& path);
    void scanPackage();
    static LogosFile* readLogosFile(const std::filesystem::path& path);
    static bool isLogosFile(const std::filesystem::directory_entry& filePath);
    static bool isMainFile(const std::filesystem::directory_entry& filePath);
    ~LogosPackage();
};


#endif // LOGOSPACKAGE_H
