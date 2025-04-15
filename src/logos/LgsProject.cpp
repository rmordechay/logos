#include "logos/LgsProject.h"
#include "analysis/AntlrConverter.h"
#include "files/LgsAppFile.h"
#include "logos/LgsGlobals.h"
#include "logos/Logos.h"
#include "parser/LogosLexer.h"
#include "parser/LogosParser.h"
#include "symbols/builtin/LgsEnv.h"
#include "symbols/builtin/LgsSys.h"
#include "symbols/builtin/LgsPrint.h"
#include "symbols/types/LgsBool.h"
#include "utils/ThreadPool.h"

#include <iostream>

using namespace std;
extern char **environ;

bool LgsProject::loadProject() {
    if (!projectAnalyser.validateProject()) return false;
    setupActiveEnv();
    if (!projectAnalyser.successful) return false;
    loadFiles();
    if (!errors.empty()) return false;
    return projectAnalyser.successful;
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
    AntlerConverter antlerConverter;
    antlerConverter.filePath = absFilePath;
    const auto file = antlerConverter.getLogosFile(parser.logosFile(), absFilePath);
    file->relPath = relative(absFilePath, paths.rootDir).lexically_relative(LOGOS_SRC_DIR);
    lock_guard lock(mtx);
    files.emplace_back(file);
    errors.insert(errors.end(), antlerConverter.errors.begin(), antlerConverter.errors.end());
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
    AntlerConverter antlerConverter;
    appFile = antlerConverter.getAppFile(parser.logosAppFile(), absFilePath);
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
    AntlerConverter antlerConverter;
    auto envFile = antlerConverter.getEnvFile(parser.logosEnvFile(), absFilePath);
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
    globals.addSymbol("ROOT_PATH", LgsSymbol(new LgsVarDec("ROOT_PATH", new LgsStr(), new LgsStrConst(paths.rootDirAbs))));
}

void LgsProject::checkRequiredEnvVars() {
    for (const auto& requireEnvVar : appFile->requireEnvVars) {
        for (const auto envFile : envFiles) {
            projectAnalyser.checkRequiredEnvVar(requireEnvVar, envFile);
        }
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