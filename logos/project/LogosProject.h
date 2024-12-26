#ifndef PROJECT_H
#define PROJECT_H
#include <string>
#include <vector>


class LogosFile;
class LogosPackage;


class LogosProject {
public:
    std::string rootPath;
    LogosPackage* rootPackage;

    explicit LogosProject(const std::string& path);
    void scanProject() const;
    ~LogosProject();
};

#endif // PROJECT_H
