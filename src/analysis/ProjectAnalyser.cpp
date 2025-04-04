#include "analysis/ProjectAnalyser.h"
#include <LgsMainFile.h>
#include <iostream>

using namespace std;

bool ProjectAnalyser::analyse() const {
    if (files.empty()) return false;
    analyseStructure();
    analyseEnvs();
    return successful;
}

void ProjectAnalyser::analyseEnvs() const {

}

void ProjectAnalyser::analyseStructure() const {
    bool hasMainFile = false;
    map<string, vector<LgsFile*>> duplicates;
    for (const auto& file : files) {
        if (dynamic_cast<LgsMainFile*>(file)) {
            hasMainFile = true;
            continue;
        }
        duplicates[file->name].emplace_back(file);
    }
    if (!hasMainFile) printError(E10008.msg);
    printDuplicateFiles(duplicates);
}

void ProjectAnalyser::printDuplicateFiles(const map<string, vector<LgsFile*>>& duplicates) const {
    for (const auto &duplicate : duplicates) {
        if (duplicate.second.size() <= 1) continue;
        ostringstream errMsg;
        for (const auto &file : duplicate.second) {
            errMsg << "\n\t - " + file->absPath;
        }
        printError(E10007.msg, {duplicate.first, errMsg.str()});
    }
}
