#include "SemaAnalyser.h"

bool SemaAnalyser::analyseCode(LogosPackage* rootPackage) {
    flattenTree(rootPackage);
    return true;
}

void SemaAnalyser::flattenTree(const LogosPackage* pkg) {
    for (const auto file : pkg->files) {
        files[file->name] = file;
    }
    for (const auto innerPkg : pkg->packages) {
        flattenTree(innerPkg);
    }
}
