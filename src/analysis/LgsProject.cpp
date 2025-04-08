#include "analysis/LgsProject.h"
#include "AntlrConverter.h"
#include "LgsAppFile.h"
#include "LgsGlobals.h"
#include "Logos.h"
#include "LogosLexer.h"
#include "LogosParser.h"
#include "ThreadPool.h"
#include "builtin/LgsEnv.h"
#include "builtin/LgsSys.h"
#include "../../include/symbols/builtin/LgsPrint.h"
#include <iostream>

using namespace std;
extern char **environ;

bool LgsProject::loadProject() {
    if (!validateProject()) return false;
    setupActiveEnv();
    if (!successful) return false;
    loadFiles();
    return successful;
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
    parseSrcFiles(paths.srcDir, threadPool);
    threadPool.wait();
}

void LgsProject::loadEnvFiles() {
    vector<LgsEnvFile*> files;
    ThreadPool threadPool;
    threadPool.start();
    for (const auto& entry : directory_iterator(paths.envsDir)) {
        if (!isLogosFile(entry)) continue;
        threadPool.runTask([entry, this] {
            parseEnvFile(entry);
        });
    }
    threadPool.wait();
}

void LgsProject::setupActiveEnv() {
    setEnvVars();
    parseAppFile(paths.appFilePath);
    loadEnvFiles();
    checkRequiredEnvVars();
}

void LgsProject::parseSrcFiles(const string& path, ThreadPool& threadPool) {
    for (const auto& entry : directory_iterator(path)) {
        if (isLogosFile(entry)) {
            threadPool.runTask([entry, this] {
                parseSrcFile(entry);
            });
        } else if (is_directory(entry.path())) {
            parseSrcFiles(entry.path(), threadPool);
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
    file->relPath = relative(absFilePath, paths.rootDir).lexically_relative(LOGOS_SRC_DIR);
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
            activeEnv.name = varDec->expr->asStrConst()->value;
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
    auto envFile = AntlerConverter::getEnvFile(parser.logosEnvFile(), absFilePath);
    envFiles.emplace_back(envFile);
}

string LgsProject::getFileText(path filePath) const {
    ifstream file(canonical(filePath));
    stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

void LgsProject::loadGlobals() const {
    globals.addFunc(new LgsPrint({LgsParam(new LgsInt())}));
    globals.addFunc(new LgsPrint({LgsParam(new LgsFloat())}));
    globals.addFunc(new LgsPrint({LgsParam(new LgsStr())}));
    globals.addFunc(new LgsPrint({LgsParam(new LgsChar())}));
    globals.addFunc(new LgsPrint({LgsParam(new LgsBool())}));
    globals.addSymbol(LgsSys::name, LgsSymbol(new LgsSys()));
    globals.addSymbol(LgsEnv::name, LgsSymbol(new LgsEnv()));
    globals.addSymbol("ROOT_PATH", LgsSymbol(new LgsVarDec("ROOT_PATH", nullptr, new LgsStrConst("djkfh"))));
}

void LgsProject::checkRequiredEnvVars() {
    for (const auto& requireEnvVar : appFile->requireEnvVars) {
        for (const auto envFile : envFiles) {
            checkRequiredEnvVar(requireEnvVar, envFile);
        }
    }
}

void LgsProject::checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile) {
    auto found = false;
    for (const auto& varDec : envFile->varDecs) {
        if (requireEnvVar.name == varDec->name && requireEnvVar.type->equals(varDec->type)) {
            found = true;
            break;
        }
    }
    if (!found) {
        printError(E10020.msg, {envFile->name, requireEnvVar.name});
        successful = false;
    }
}

bool LgsProject::validateProject() const {
    if (!is_directory(paths.rootDir) || !is_directory(paths.srcDir)) {
        printError(E10010.msg);
        return false;
    }

    if (!exists(paths.appFilePath)) {
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

void LgsProject::setEnvVars() const {
    for (char **env = environ; *env != nullptr; ++env) {
        string entry(*env);
        const auto pos = entry.find('=');
        if (pos != string::npos) {
            auto key = entry.substr(0, pos);
            const auto value = entry.substr(pos + 1);
            activeEnv.envVars[key] = value;
        }
    }
}

bool LgsProject::isLogosFile(const directory_entry& entry) const {
    return entry.is_regular_file() && entry.path().extension().string() == LOGOS_FILE_EXTENSION;
}