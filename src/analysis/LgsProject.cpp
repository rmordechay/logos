#include "analysis/LgsProject.h"
#include "AntlrConverter.h"
#include "LgsAppFile.h"
#include "LgsGlobals.h"
#include "Logos.h"
#include "LogosLexer.h"
#include "LogosParser.h"
#include "ThreadPool.h"
#include "builtin/LgsEnvObject.h"
#include "builtin/LgsSys.h"
#include "funcs/LgsPrint.h"

#include <iostream>

using namespace std;

bool LgsProject::loadProject() {
    if (!validateProject()) return false;
    setAppEnv();
    loadFiles();
    return true;
}

void LgsProject::loadFiles() {
    thread tSrcFiles([this] { loadSrcFiles(); });
    thread tGlobals([this] { loadGlobals(); });
    tSrcFiles.join();
    tGlobals.join();
}

void LgsProject::loadSrcFiles() {
    vector<LgsFile*> files;
    ThreadPool threadPool;
    threadPool.start();
    parseSrcFiles(paths->srcDir, threadPool);
    threadPool.wait();
    checkDuplicateFiles();
}

void LgsProject::setAppEnv() {
    const auto appFilePath = paths->rootDir / LOGOS_APP_FILE_NAME LOGOS_FILE_EXTENSION;
    if (!exists(appFilePath)) return;
    parseAppFile(appFilePath);
    checkEnvs();
}

void LgsProject::parseSrcFiles(const string& path, ThreadPool& threadPool) {
    for (const auto& entry : directory_iterator(path)) {
        if (isLogosFile(entry)) {
            threadPool.runTask([entry, this] {
                parseSrcFile(entry);
            });
        } else if (is_directory(entry.path())) {
            // parseSrcFiles(entry.path(), threadPool);
        }
    }
}

void LgsProject::parseSrcFile(const directory_entry& entry) {
    const auto absFilePath = canonical(entry);
    const auto codeText = getFileText(entry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto file = AntlerConverter::getLogosFile(parser.logosFile(), absFilePath);
    file->relPath = relative(absFilePath, paths->rootDir).lexically_relative(LOGOS_SRC_DIR);
    lock_guard lock(mtx);
    files.emplace_back(file);
    if (file->name == LOGOS_MAIN_FILE_NAME) {
        mainFile = dynamic_cast<LgsMainFile*>(file);
    }
}

void LgsProject::parseAppFile(path fileEntry) {
    auto absFilePath = canonical(fileEntry);
    auto codeText = getFileText(fileEntry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    appFile = AntlerConverter::getAppFile(parser.logosAppFile(), absFilePath);

    for (const auto& varDec : appFile->varDecs) {
        if (varDec->name == "name") {
            name = varDec->expr->asStrConst()->value;
        }
        if (varDec->name == "version") {
            version = varDec->expr->asStrConst()->value;
        }
        if (varDec->name == "activeEnv") {
            const auto activeEnv = varDec->expr->asStrConst()->value;
            const auto activeEnvPath = paths->envsDir / (activeEnv + LOGOS_FILE_EXTENSION);
            parseEnvFile(activeEnvPath);
        }
    }
}

void LgsProject::parseEnvFile(path fileEntry) {
    auto absFilePath = canonical(fileEntry);
    auto codeText = getFileText(fileEntry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    activeEnv = AntlerConverter::getEnvFile(parser.logosEnvFile(), absFilePath);
}

string LgsProject::getFileText(path filePath) const {
    ifstream file(canonical(filePath));
    stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

void LgsProject::loadGlobals() const {
    globals.funcs[LgsPrint::name] = {
        new LgsPrint({new LgsParam(new LgsInt())}),
        new LgsPrint({new LgsParam(new LgsFloat())}),
        new LgsPrint({new LgsParam(new LgsStr())}),
        new LgsPrint({new LgsParam(new LgsChar())}),
        new LgsPrint({new LgsParam(new LgsBool())}),
    };
    globals.symbols[LgsSys::name] = LgsSymbol(new LgsSys());
    globals.symbols[LgsEnvObject::name] = LgsSymbol(new LgsEnvObject());
}

void LgsProject::checkEnvs() const {
    for (const auto& requireEnvVar : appFile->requireEnvVars) {
        auto found = false;
        for (const auto& varDec : activeEnv->varDecs) {
            if (requireEnvVar.name == varDec->name) {
                found = true;
            }
        }
        if (!found) {
            // TODO finis logic
        }
    }
}

bool LgsProject::validateProject() const {
    if (!is_directory(paths->rootDir) || !is_directory(paths->srcDir)) {
        printError(E10010.msg);
        return false;
    }

    if (!exists(paths->srcDir / LOGOS_MAIN_FILE_NAME LOGOS_FILE_EXTENSION)) {
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
    for (const auto& [name, duplicate] : duplicates) {
        if (duplicate.size() <= 1) continue;
        ostringstream errMsg;
        for (const auto &file : duplicate) {
            errMsg << "\n\t - " + file->absPath;
        }
        printError(E10007.msg, {name, errMsg.str()});
    }
}

bool LgsProject::isLogosFile(const directory_entry& entry) const {
    return entry.is_regular_file() && entry.path().extension().string() == LOGOS_FILE_EXTENSION;
}