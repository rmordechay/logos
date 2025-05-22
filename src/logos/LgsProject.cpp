#include "logos/LgsProject.h"

#include "LgsInterfaceFile.h"
#include "Platform.h"
#include "analysis/AntlrConverter.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "files/LgsAppFile.h"
#include "logos/LgsGlobals.h"
#include "logos/Logos.h"
#include "parser/LogosLexer.h"
#include "parser/LogosParser.h"
#include "symbols/builtin/LgsPrint.h"
#include "utils/ThreadPool.h"
#include <iostream>

using namespace std;
extern char **environ;
std::mutex projectMtx;

bool LogosProject::loadProject(const vector<char*>& args) {
    if (!validateProject()) return false;
    // setupActiveEnv();
    if (!errHandler.successful) return false;
    loadFiles();
    if (!errors.empty()) return false;
    if (!resolveGlobalTypes(files)) return false;
    mainFile->mainFunc->setArgs(args);
    return errHandler.successful;
}


bool LogosProject::validateProject() {
    if (!is_directory(paths.rootDir) || !is_directory(paths.srcDir)) {
        errHandler.handleError(E10010, nullptr);
        return false;
    }

    if (!exists(paths.appFilePath)) {
        errHandler.handleError(E10008, nullptr);
        return false;
    }
    return true;
}

void LogosProject::checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile) {
    auto found = false;
    for (const auto& varDec : envFile->varDecs) {
        if (requireEnvVar.name == varDec->name && requireEnvVar.type->equals(varDec->type)) {
            found = true;
            break;
        }
    }
    if (!found) {
        errHandler.handleError(E10020, nullptr, {envFile->name, requireEnvVar.name});
    }
}

void LogosProject::checkDuplicateFiles(const vector<LgsFile*>& files) {
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
        errHandler.handleError(E10007, nullptr, {name, errMsg.str()});
    }
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

bool LogosProject::resolveGlobalTypes(const vector<LgsFile*>& files) const {
    for (const auto& file : files) {
        SemaAnalyser semaAnalyser(file);
        if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto& object : mainFile->objects) {
                semaAnalyser.resolveObjMemberTypes(object);
            }
            for (const auto [_, func] : mainFile->funcs) {
                semaAnalyser.resolveFuncTypes(&func->funcType);
            }
        } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            semaAnalyser.resolveObjMemberTypes(objFile->obj);
        } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
            auto methods = interfaceFile->interface->methods;
            for (const auto& [_, method] : methods) {
                semaAnalyser.resolveFuncTypes(&method->funcType);
            }
        }
        if (!semaAnalyser.errHandler.successful) return false;
    }
    return true;
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

void LogosProject::parseSrcFile(path entry) {
    const auto absFilePath = canonical(entry);
    AntlerConverter antlerConverter;
    antlerConverter.errHandler.filePath = absFilePath;

    const auto codeText = getFileText(entry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto file = antlerConverter.getLogosFile(parser.logosFile(), absFilePath);
    lock_guard lock(projectMtx);
    files.emplace_back(file);
    errors.insert(errors.end(), antlerConverter.errHandler.errors.begin(), antlerConverter.errHandler.errors.end());
    if (file->name == LOGOS_MAIN_FILE_NAME) {
        mainFile = dynamic_cast<LgsMainFile*>(file);
    }
}

void LogosProject::parseEnvFile(path fileEntry) {
    const auto absFilePath = canonical(fileEntry);
    AntlerConverter antlerConverter;
    antlerConverter.errHandler.filePath = absFilePath;

    const auto codeText = getFileText(fileEntry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    auto file = antlerConverter.getEnvFile(parser.logosEnvFile(), absFilePath);
    lock_guard lock(projectMtx);
    envFiles.emplace_back(file);
    errors.insert(errors.end(), antlerConverter.errHandler.errors.begin(), antlerConverter.errHandler.errors.end());
}

void LogosProject::parseAppFile(path fileEntry) {
    auto absFilePath = canonical(fileEntry);
    AntlerConverter antlerConverter;
    antlerConverter.errHandler.filePath = absFilePath;

    auto codeText = getFileText(fileEntry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);

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

string LogosProject::getFileText(path filePath) const {
    ifstream file(canonical(filePath));
    stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

void LogosProject::loadGlobals() {
    globals.addSymbol(lgsPrint.funcType.name, LgsSymbol(&lgsPrint), &errHandler);
}

void LogosProject::checkRequiredEnvVars() {
    for (const auto& requireEnvVar : appFile->requireEnvVars) {
        for (const auto envFile : envFiles) {
            checkRequiredEnvVar(requireEnvVar, envFile);
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

void LogosProject::asJSON() const {
    cout << mainFile->asJSON().dump(2) << '\n';
    return;
}

bool LogosProject::isLogosFile(const directory_entry& entry) const {
    return entry.is_regular_file() && entry.path().extension().string() == LOGOS_FILE_EXTENSION;
}
