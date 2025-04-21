#include "logos/LogosProject.h"

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
#include "types/LgsChar.h"
#include "utils/ThreadPool.h"

#include <iostream>

using namespace std;
extern char **environ;
std::mutex projectMtx;

bool LogosProject::loadProject() {
    if (!projectAnalyser.validateProject()) return false;
    setupActiveEnv();
    if (!projectAnalyser.successful) return false;
    loadFiles();
    if (!errors.empty()) return false;
    projectAnalyser.resolveGlobalTypes(files);
    return projectAnalyser.successful;
}

void LogosProject::loadFiles() {
    thread tSrcFiles([this] { loadSrcFiles(); });
    thread tGlobals([this] { loadGlobals(); });
    tSrcFiles.join();
    tGlobals.join();
}

void LogosProject::loadSrcFiles() {
    vector<LgsFile*> files;
    ThreadPool threadPool;
    threadPool.start();
    parseSrcFiles(paths.srcDir, threadPool);
    threadPool.wait();
}

void LogosProject::loadEnvFiles() {
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

void LogosProject::setupActiveEnv() {
    setEnvVars();
    parseAppFile(paths.appFilePath);
    loadEnvFiles();
    checkRequiredEnvVars();
}

void LogosProject::parseSrcFiles(const string& path, ThreadPool& threadPool) {
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

void LogosProject::parseSrcFile(const directory_entry& entry) {
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
    lock_guard lock(projectMtx);
    files.emplace_back(file);
    errors.insert(errors.end(), antlerConverter.errors.begin(), antlerConverter.errors.end());
    if (file->name == LOGOS_MAIN_FILE_NAME) {
        mainFile = dynamic_cast<LgsMainFile*>(file);
    }
}

void LogosProject::parseAppFile(path fileEntry) {
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

void LogosProject::parseEnvFile(path fileEntry) {
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

string LogosProject::getFileText(path filePath) const {
    ifstream file(canonical(filePath));
    stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

void LogosProject::loadGlobals() const {
    globals.addFunc(new LgsPrint({LgsParam(new LgsInt())}));
    globals.addFunc(new LgsPrint({LgsParam(new LgsFloat())}));
    globals.addFunc(new LgsPrint({LgsParam(new LgsStr())}));
    globals.addFunc(new LgsPrint({LgsParam(new LgsChar())}));
    globals.addFunc(new LgsPrint({LgsParam(new LgsBool())}));
    globals.addSymbol(LgsSys::name, LgsSymbol(new LgsSys()));
    globals.addSymbol(LgsEnv::name, LgsSymbol(new LgsEnv()));
    globals.addSymbol("ROOT_PATH", LgsSymbol(new LgsVarDec("ROOT_PATH", new LgsStr(), new LgsStrConst(paths.rootDirAbs))));
}

void LogosProject::checkRequiredEnvVars() {
    for (const auto& requireEnvVar : appFile->requireEnvVars) {
        for (const auto envFile : envFiles) {
            projectAnalyser.checkRequiredEnvVar(requireEnvVar, envFile);
        }
    }
}

void LogosProject::setEnvVars() const {
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

void LogosProject::asJSON() {
    std::cout << mainFile->asJSON().dump(2) << '\n';
    return;
}

bool LogosProject::isLogosFile(const directory_entry& entry) const {
    return entry.is_regular_file() && entry.path().extension().string() == LOGOS_FILE_EXTENSION;
}
