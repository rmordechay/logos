#ifndef PROJECT_H
#define PROJECT_H
#include <filesystem>
#include <string>
#include <vector>
#include "LogosFile.h"
namespace fs = std::filesystem;

class Project {
public:
    explicit Project(const std::string& path);
    ~Project();
    void scanProject();
    void addLogosFile(const fs::directory_entry& entry);
    void scanPackage(const std::string& packagePath);
    static void parseFile(const LogosFile *logosFile);

private:
    std::string dirPath;
    std::vector<LogosFile*> files;
};

#endif // PROJECT_H
