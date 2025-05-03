#include "logos/LgsProject.h"

#include "LgsInterfaceFile.h"
#include "analysis/AntlrConverter.h"
#include "builtin/LgsReflect.h"
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
    if (!validateProject()) return false;
    setupActiveEnv();
    if (!errHandler.successful) return false;
    loadFiles();
    if (!errors.empty()) return false;
    resolveGlobalTypes(files);
    return errHandler.successful;
}


void LogosProject::resolveGlobalTypes(const vector<LgsFile*>& files) {
    for (const auto& file : files) {
        if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto& object : mainFile->objects) {
                resolveObjMemberTypes(object);
            }
            for (const auto& func : mainFile->getAllFuncs()) {
                resolveFuncTypes(&func->funcType);
            }
        } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            resolveObjMemberTypes(objFile->obj);
        } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
            auto overloads = interfaceFile->interface->getAllMethods();
            for (const auto& overload : overloads) {
                resolveFuncTypes(&overload->funcType);
            }
        }
    }
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

void LogosProject::resolveObjMemberTypes(LgsObject* const& obj) {
    for (const auto& [_, field] : obj->fields) {
        field->type = resolveType(field->type, &errHandler);
        field->parent = obj;
    }
    for (const auto& overload : obj->getAllMethods()) {
        resolveFuncTypes(&overload->funcType);
    }
    for (int i = 0; i < obj->implements.size(); ++i) {
        obj->implements[i] = resolveType(obj->implements[i], &errHandler);
    }
}

void LogosProject::resolveFuncTypes(LgsFuncType* signature) {
    signature->type = resolveType(signature->type, &errHandler);
    for (int i = 0; i < signature->params.size(); ++i) {
        const auto lgsParam = signature->params[i];
        signature->params[i].type = resolveType(signature->params[i].type, &errHandler);
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

void LogosProject::parseSrcFile(path entry) {
    const auto absFilePath = canonical(entry);
    const auto codeText = getFileText(entry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    AntlerConverter antlerConverter;
    antlerConverter.errHandler.filePath = absFilePath;
    const auto file = antlerConverter.getLogosFile(parser.logosFile(), absFilePath);
    file->relPath = relative(absFilePath, paths.rootDir).lexically_relative(LOGOS_SRC_DIR);
    lock_guard lock(projectMtx);
    files.emplace_back(file);
    errors.insert(errors.end(), antlerConverter.errHandler.errors.begin(), antlerConverter.errHandler.errors.end());
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

void LogosProject::loadGlobals() {
    globals.addFunc(new LgsPrint({LgsParam(&LGS_INT)}));
    globals.addFunc(new LgsPrint({LgsParam(new LgsFloat())}));
    globals.addFunc(new LgsPrint({LgsParam(&LGS_STR)}));
    globals.addFunc(new LgsPrint({LgsParam(new LgsChar())}));
    globals.addFunc(new LgsPrint({LgsParam(&LGS_BOOL)}));
    globals.addSymbol(LgsSys::name, LgsSymbol(new LgsSys()), &errHandler);
    globals.addSymbol(LgsEnv::name, LgsSymbol(new LgsEnv()), &errHandler);
    globals.addSymbol(LgsReflect::name, LgsSymbol(new LgsReflect()), &errHandler);
    globals.addSymbol("ROOT_PATH", LgsSymbol(new LgsVarDec("ROOT_PATH", &LGS_STR, new LgsStrConst(paths.rootDirAbs))), &errHandler);
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
    std::cout << mainFile->asJSON().dump(2) << '\n';
    return;
}

bool LogosProject::isLogosFile(const directory_entry& entry) const {
    return entry.is_regular_file() && entry.path().extension().string() == LOGOS_FILE_EXTENSION;
}
