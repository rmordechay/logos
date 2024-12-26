#ifndef PROJECT_H
#define PROJECT_H
#include "SemAnalyser.h"
#include <string>

class LogosFile;
class LogosPackage;


class LogosProject {
public:
    std::string rootPath;
    LogosPackage* rootPackage;
    SemAnalyser* semAnalyser;

    explicit LogosProject(const std::string& path);
    void scanProject() const;
};

#endif // PROJECT_H
