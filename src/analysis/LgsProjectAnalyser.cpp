#include "analysis/LgsProjectAnalyser.h"
#include "Logos.h"
#include "stmts/LgsVarDec.h"

void LgsProjectAnalyser::checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile) {
    auto found = false;
    for (const auto& varDec : envFile->varDecs) {
        if (requireEnvVar.name == varDec->name && requireEnvVar.type->equals(varDec->type)) {
            found = true;
            break;
        }
    }
    if (!found) {
        handleError(E10020, nullptr, {envFile->name, requireEnvVar.name});
    }
}

bool LgsProjectAnalyser::validateProject() {
    if (!is_directory(paths.rootDir) || !is_directory(paths.srcDir)) {
        handleError(E10010, nullptr);
        return false;
    }

    if (!exists(paths.appFilePath)) {
        handleError(E10008, nullptr);
        return false;
    }
    return true;
}

void LgsProjectAnalyser::checkDuplicateFiles(const vector<LgsFile*>& files) {
    map<string, vector<LgsFile*>> duplicates;
    for (const auto& file : files) {
        duplicates[file->name].emplace_back(file);
    }
    if (duplicates.empty()) return;
    for (const auto& [name, duplicate] : duplicates) {
        if (duplicate.size() <= 1) continue;
        ostringstream errMsg;
        for (const auto &file : duplicate) {
            errMsg << "\n\t - " + file->absPath;
        }
        handleError(E10007, nullptr, {name, errMsg.str()});
    }
}
