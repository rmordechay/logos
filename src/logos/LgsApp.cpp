#include "logos/LgsApp.h"

#include "configs/LgsConfig.h"
#include "LogosLexer.h"
#include "analysis/AntlrConverter.h"
#include "analysis/SemaAnalyser.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "logos/LgsPaths.h"
#include "utils/ThreadPool.h"
#include "builtins/LgsBuiltins.h"
#include "builtins/LgsSystem.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "extern/LgsCLang.h"
#include "files/LgsAppFile.h"
#include "files/LgsEnvFile.h"
#include "funcs/LgsMainFunc.h"
#include "logos/LgsLinker.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsInterface.h"
#include "utils/LgsUtils.h"

extern char **environ;

enum LogLevel {
    INFO,
    DEBUG,
    ERROR,
};

void LgsApp::run() {
    // Validation
    if (!validate()) exitWithErrors();

    // Lexing and Parsing
    if (!parse()) exitWithErrors();

    // Semantic analysis
    if (!analyse()) exitWithErrors();

    // Code generation
    if (!generate()) exitWithErrors();

    // Linking
    if (!link()) exitWithErrors();

    // Running
    execv(paths.execFilePath.c_str(), args.data());
}

bool LgsApp::validate() {
    if (!is_directory(paths.rootDir) || !is_directory(paths.srcDir)) {
        errHandler.addError(E10010, nullptr);
        return false;
    }

    if (!exists(paths.appFilePath)) {
        errHandler.addError(E10008, nullptr);
        return false;
    }
    return true;
}

bool LgsApp::parse() {
    loadBuiltins();
    ThreadPool threadPool;
    for (const auto& entry : filesystem::recursive_directory_iterator(paths.srcDir)) {
        if (!isLogosFile(entry)) continue;
        threadPool.runTask([entry, this] {
            const auto absFilePath = filesystem::path(canonical(entry));
            const auto codeText = getFileText(absFilePath);
            parseSrcFile(codeText, absFilePath);
        });
    }
    threadPool.wait();
    return errHandler.successful && resolveExternalFiles();
}

bool LgsApp::analyse() {
    if (!resolveGlobalTypes()) exitWithErrors();
    ThreadPool threadPool;
    for (const auto file : files) {
        threadPool.runTask([file, this] {
            SemaAnalyser semaAnalyser(file, globals);
            semaAnalyser.analyse();
            if (!semaAnalyser.errHandler.successful) {
                lock_guard lock(mtx);
                errHandler.copyErrors(semaAnalyser.errHandler.errors);
            }
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::generate() const {
    initBuild();
    ThreadPool threadPool;
    for (const auto& file : files) {
        threadPool.runTask([file] {
            file->generateIR();
            if (!file->codeGen.IRModule) return;
            lock_guard lock(mtx);
        });
    }
    threadPool.wait();
    writeIRFiles();
    return errHandler.successful;
}

bool LgsApp::link() const {
    const LgsLinker linker(paths, files);
    return linker.link();
}

void LgsApp::parseSrcFile(const string& codeText, filesystem::path filePath) {
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto ast = parser.logosFile();
    if (parser.getNumberOfSyntaxErrors() != 0) {
        lock_guard lock(mtx);
        errHandler.setUnsuccessful();
        return;
    }
    AntlrConverter antlrConverter(filePath, globals);
    const auto file = antlrConverter.getLogosFile(ast);
    lock_guard lock(mtx);
    files.push_back(file);
    if (!antlrConverter.errHandler.successful) {
        errHandler.copyErrors(antlrConverter.errHandler.errors);
        return;
    }
    for (const auto externFile : file->externFiles) {
        externFiles.push_back(externFile);
    }
}

void LgsApp::parseEnvFile(filesystem::path fileEntry) {
    const auto absFilePath = new filesystem::path(filesystem::canonical(fileEntry));
    AntlrConverter antlerConverter(*absFilePath, globals);
    const auto codeText = getFileText(fileEntry);
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    auto file = antlerConverter.getEnvFile(parser.logosEnvFile());
    lock_guard lock(mtx);
    envFiles.emplace_back(file);
    errHandler.copyErrors(antlerConverter.errHandler.errors);
}

void LgsApp::parseAppFile(filesystem::path fileEntry) {
    const auto absFilePath = new filesystem::path(filesystem::canonical(fileEntry));
    AntlrConverter antlerConverter(*absFilePath, globals);
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

bool LgsApp::resolveGlobalTypes() {
    bool successful = true;
    for (const auto& file : files) {
        SemaAnalyser semaAnalyser(file, globals);
        if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto object : mainFile->objects) {
                semaAnalyser.resolveObjTypes(object);
            }
            for (const auto interface : mainFile->interfaces) {
                semaAnalyser.resolveInterfaceTypes(interface);
            }
            for (const auto group : mainFile->groups) {
                semaAnalyser.resolveGroupTypes(group);
            }
            for (const auto [_, func] : mainFile->funcs) {
                if (dynamic_cast<LgsMainFunc*>(func)) continue;
                semaAnalyser.resolveFuncTypes(func->funcType);
            }
        } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            semaAnalyser.resolveObjTypes(objFile->obj);
        } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
            semaAnalyser.resolveInterfaceTypes(interfaceFile->interface);
        }
        if (!semaAnalyser.errHandler.successful) {
            errHandler.copyErrors(semaAnalyser.errHandler.errors);
        }
        successful = successful && semaAnalyser.errHandler.successful;
    }
    return successful;
}

bool LgsApp::resolveExternalFiles() {
    lgsCLang.setCHeaderPaths();
    if (externFiles.empty()) return true;
    for (const auto externFile : externFiles) {
        lgsCLang.parseFile(externFile->value);
    }
    return lgsCLang.errHandler.successful;
}

void LgsApp::loadBuiltins() {
    globals.addSymbol(LgsSymbol(new LgsPrint(), false, true), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsSystem(), false, true), &errHandler);
}

void LgsApp::loadEnvFiles() {
    ThreadPool threadPool;
    for (const auto& entry : filesystem::directory_iterator(paths.envsDir)) {
        if (!isLogosFile(entry)) continue;
        threadPool.runTask([entry, this] {
            parseEnvFile(entry);
        });
    }
    threadPool.wait();
}

void LgsApp::checkRequiredEnvVars() {
    for (const auto& requireEnvVar : appFile->requireEnvVars) {
        for (const auto envFile : envFiles) {
            auto found = false;
            for (const auto& varDec : envFile->varDecs) {
                if (requireEnvVar.name == varDec->name && requireEnvVar.type->equals(varDec->type)) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                errHandler.addError(E10020, nullptr, {envFile->name, requireEnvVar.name});
            }
        }
    }
}

void LgsApp::setEnvVars() {
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

void LgsApp::setupActiveEnv() {
    setEnvVars();
    parseAppFile(paths.appFilePath);
    loadEnvFiles();
    checkRequiredEnvVars();
}

void LgsApp::initBuild() {
    remove_all(paths.buildDir);
    create_directories(paths.buildDir);
    create_directories(paths.buildIR);
    LgsCodeGen::initLLVM();
}

void LgsApp::writeIRFiles() const {
    for (const auto file : files) {
        const auto module = file->codeGen.IRModule;
        if (!module) continue;
        if constexpr (WRITE_IR_TO_FILE) {
            const auto filePath = (paths.buildIR / module->getName().str()).string() + ".ll";
            error_code EC;
            raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
            module->print(textFile, nullptr);
        }
        if constexpr (LOG_LEVEL == DEBUG) {
            module->print(outs(), nullptr);
            logInfo("\n-----\n\n");
        }
    }
}

void LgsApp::exitWithErrors() const {
    for (int i = 0; i < errHandler.errors.size(); ++i) {
        const auto lgsError = errHandler.errors[i];
        const auto finalResult = string(lgsError.msg) + "\n\t    at " + getFullPath(*lgsError.location);
        logInfo(LOGOS_ERROR_STR + string(finalResult));
        if (i != errHandler.errors.size() - 1) logInfo("\n---");
        free((void*)lgsError.msg);
        free((void*)lgsError.location->filePath);
    }
    return exit(1);
}

LgsApp::~LgsApp() {
    for (const auto file : files) {
        delete file;
    }
}
