#include "LogosProject.h"

#include "LogosConfigs.h"

#include "LogosPackage.h"
#include "antlr4-runtime/antlr4-runtime.h"
#include <fstream>
#include <sstream>

using namespace antlr4;

LogosProject::LogosProject(const std::string& path) {
    rootPath = path;
    rootPackage = new LogosPackage(LOGOS_SOURCE_PACKAGE, rootPath);
}

void LogosProject::scanProject() const {
    rootPackage->scanPackage();
}


LogosProject::~LogosProject() {
    delete rootPackage;
}
