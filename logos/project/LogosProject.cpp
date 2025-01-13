#include "LogosProject.h"
#include "LogosConfigs.h"
#include "LogosPackage.h"

LogosProject::LogosProject(const std::string& path) {
    this->rootPath = path;
    this->rootPackage = new LogosPackage(LOGOS_SOURCE_PACKAGE, rootPath);
    this->semAnalyser = new SemAnalyser(*rootPackage);
    this->codeGenerator = new CodeGenerator();
}

void LogosProject::scanProject() const {
    rootPackage->scanPackage();
    semAnalyser->analyseProject();
    codeGenerator->run();
}
