#include "LogosProject.h"
#include "LogosConfigs.h"
#include "LogosPackage.h"

LogosProject::LogosProject(const std::string& path) {
    this->rootPath = path;
    this->rootPackage = new LogosPackage(LOGOS_SOURCE_PACKAGE, rootPath);
    this->semAnalyser = new SemAnalyser();
    this->codeGenerator = new CodeGenerator();
}

void LogosProject::scanProject() const {
    rootPackage->scanPackage();
    semAnalyser->analyseProject(rootPackage->mainFile);
    codeGenerator->run(semAnalyser->codeNodes);
}

LogosProject::~LogosProject() {
    delete semAnalyser;
    delete codeGenerator;
}
