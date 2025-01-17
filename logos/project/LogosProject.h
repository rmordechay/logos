#ifndef PROJECT_H
#define PROJECT_H
#include "CodeGenerator.h"
#include "SemAnalyser.h"
#include <string>

class LogosFile;
class LogosPackage;


class LogosProject {
public:
    std::string rootPath;
    LogosPackage* rootPackage;
    SemAnalyser* semAnalyser;
    CodeGenerator* codeGenerator;

    explicit LogosProject(const std::string& path);
    void scanProject() const;
    ~LogosProject();
};

#endif // PROJECT_H
