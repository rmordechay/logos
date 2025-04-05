#include "analysis/LgsProject.h"
#include "Logos.h"
#include <LgsMainFile.h>
#include <iostream>

using namespace std;

bool LgsProject::validateProject() const {
    if (!is_directory(paths->rootDir) || !is_directory(paths->srcDir)) {
        printError(E10010.msg);
        return false;
    }
    if (!exists(paths->srcDir / "Main.lgs")) {
        printError(E10008.msg);
        return false;
    }
    return true;
}

void LgsProject::checkDuplicateFiles() const {
    map<string, vector<LgsFile*>> duplicates;
    for (const auto& file : files) {
        duplicates[file->name].emplace_back(file);
    }
    if (duplicates.empty()) return;
    for (const auto &duplicate : duplicates) {
        if (duplicate.second.size() <= 1) continue;
        ostringstream errMsg;
        for (const auto &file : duplicate.second) {
            errMsg << "\n\t - " + file->absPath;
        }
        printError(E10007.msg, {duplicate.first, errMsg.str()});
    }
}
