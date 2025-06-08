#include "logos/LgsProject.h"

#include "files/LgsInterfaceFile.h"
#include "analysis/SemaAnalyser.h"
#include "analysis/AntlrConverter.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "files/LgsAppFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"

#include "logos/Logos.h"
#include "parser/LogosLexer.h"
#include "parser/LogosParser.h"
#include "stmts/LgsVarDec.h"
#include "symbols/builtin/LgsPrint.h"
#include "utils/ThreadPool.h"

using namespace std;
extern char **environ;

bool LogosProject::loadProject() {
    if (!validateProject()) return false;
    // setupActiveEnv();
    if (!errHandler.successful) return false;
    loadFiles();
    if (!errors.empty()) return false;
    if (!resolveGlobalTypes(files)) return false;
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
    const path absFilePath = canonical(entry);
    AntlerConverter antlerConverter;
    antlerConverter.errHandler.filePath = absFilePath;
    const auto codeText = getFileText(entry);
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto file = antlerConverter.getLogosFile(parser.logosFile(), absFilePath);
    lock_guard lock(mtx);
    files.emplace_back(file);
    errors.insert(errors.end(), antlerConverter.errHandler.errors.begin(), antlerConverter.errHandler.errors.end());
}

void LogosProject::parseEnvFile(path fileEntry) {
    const auto absFilePath = canonical(fileEntry);
    AntlerConverter antlerConverter;
    antlerConverter.errHandler.filePath = absFilePath;
    const auto codeText = getFileText(fileEntry);
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    auto file = antlerConverter.getEnvFile(parser.logosEnvFile());
    lock_guard lock(mtx);
    envFiles.emplace_back(file);
    errors.insert(errors.end(), antlerConverter.errHandler.errors.begin(), antlerConverter.errHandler.errors.end());
}

bool LogosProject::resolveGlobalTypes(const vector<LgsFile*>& files) const {
    for (const auto& file : files) {
        SemaAnalyser semaAnalyser(file);
        if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto object : mainFile->objects) {
                semaAnalyser.resolveObjTypes(object);
            }
            for (const auto group : mainFile->groups) {
                semaAnalyser.resolveGroupTypes(group);
            }
            for (const auto [_, func] : mainFile->funcs) {
                semaAnalyser.resolveFuncTypes(&func->funcType);
            }
        } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            semaAnalyser.resolveObjTypes(objFile->obj);
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

void LogosProject::parseAppFile(path fileEntry) {
    auto absFilePath = canonical(fileEntry);
    AntlerConverter antlerConverter;
    antlerConverter.errHandler.filePath = absFilePath;

    auto codeText = getFileText(fileEntry);
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);

    appFile = antlerConverter.getAppFile(parser.logosAppFile());
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

void LogosProject::loadGlobals() {
    globals.addSymbol(lgsPrint.funcType.name, LgsSymbol(&lgsPrint), &errHandler);
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

void LogosProject::checkRequiredEnvVars() {
    for (const auto& requireEnvVar : appFile->requireEnvVars) {
        for (const auto envFile : envFiles) {
            checkRequiredEnvVar(requireEnvVar, envFile);
        }
    }
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

void LogosProject::setEnvVars() {
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

void LogosProject::setupActiveEnv() {
    setEnvVars();
    parseAppFile(paths.appFilePath);
    loadEnvFiles();
    checkRequiredEnvVars();
}

void LogosProject::asJSON() const {
    return;
}

bool LogosProject::isLogosFile(const directory_entry& entry) const {
    return entry.is_regular_file() && entry.path().extension().string() == LOGOS_FILE_EXTENSION;
}
