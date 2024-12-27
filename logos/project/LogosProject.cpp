#include "LogosProject.h"
#include "LogosConfigs.h"
#include "LogosPackage.h"

LogosProject::LogosProject(const std::string& path) {
    rootPath = path;
    rootPackage = new LogosPackage(LOGOS_SOURCE_PACKAGE, rootPath);
    semAnalyser = new SemAnalyser(rootPackage);
    codeGenerator = new CodeGenerator();
}

void LogosProject::scanProject() const {
    rootPackage->scanPackage();
    semAnalyser->analyseProject();
    codeGenerator->generateCode(semAnalyser->astNodes);
}
