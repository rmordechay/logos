#include "logos/LgsApp.h"
#include "LogosLexer.h"
#include "analysis/AntlrConverter.h"
#include "analysis/SemaAnalyser.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "logos/Platform.h"
#include "utils/ThreadPool.h"
#include "builtin/LgsBuiltins.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "extern/LgsCLang.h"
#include "files/LgsAppFile.h"
#include "files/LgsEnvFile.h"
#include "funcs/LgsMainFunc.h"
#include "logos/LgsConfig.h"
#include "logos/LgsLinker.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsInterface.h"
#include "utils/LgsIRUtils.h"

extern char **environ;

void LgsApp::run() {
    // Validation
    if (!validate()) handleExitWithErrors();

    // Lexing and Parsing
    if (!parse()) handleExitWithErrors();

    // Semantic analysis
    if (!analyse()) handleExitWithErrors();

    // Code generation
    if (!generate()) handleExitWithErrors();

    // Linking
    if (!link(paths)) handleExitWithErrors();

    // Running
    execv(paths.execFilePath.c_str(), args.data());
}

bool LgsApp::validate() {
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

bool LgsApp::parse() {
    loadBuiltins();
    ThreadPool threadPool;
    for (const auto& entry : recursive_directory_iterator(paths.srcDir)) {
        if (!isLogosFile(entry)) continue;
        threadPool.runTask([entry, this] {
            const auto absFilePath = path(canonical(entry));
            const auto codeText = getFileText(absFilePath);
            parseSrcFile(codeText, absFilePath);
        });
    }
    threadPool.wait();
    return errHandler.successful && resolveExternalFiles();
}

bool LgsApp::analyse() {
    if (!resolveGlobalTypes()) handleExitWithErrors();
    ThreadPool threadPool;
    for (const auto file : files) {
        threadPool.runTask([file, this] {
            SemaAnalyser semaAnalyser(file, globals);
            semaAnalyser.analyse();
            if (!semaAnalyser.errHandler.successful) {
                lock_guard lock(mtx);
                errHandler.addErrors(semaAnalyser.errHandler.errors);
            }
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::generate() {
    initLLVM();
    initBuildDir();
    ThreadPool threadPool;
    for (const auto& file : files) {
        threadPool.runTask([file, this] {
            const auto module = file->generateIR(globals);
            if (!module) return;
            const auto name = file->name;
            lock_guard lock(mtx);
            modules[name] = module;
        });
    }
    threadPool.wait();
    writeIRToFile();
    return errHandler.successful;
}

void LgsApp::parseSrcFile(const string& codeText, path filePath) {
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto ast = parser.logosFile();
    if (parser.getNumberOfSyntaxErrors() != 0) {
        lock_guard lock(mtx);
        errHandler.setUnsuccessful();
        return;
    }
    AntlerConverter antlerConverter(filePath, globals);
    const auto file = antlerConverter.getLogosFile(ast);
    lock_guard lock(mtx);
    files.push_back(file);
    if (!antlerConverter.errHandler.successful) {
        errHandler.addErrors(antlerConverter.errHandler.errors);
        return;
    }
    for (const auto externFile : file->externFiles) {
        externFiles.push_back(externFile);
    }
}

void LgsApp::parseEnvFile(path fileEntry) {
    const auto absFilePath = new path(canonical(fileEntry));
    AntlerConverter antlerConverter(*absFilePath, globals);
    const auto codeText = getFileText(fileEntry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    auto file = antlerConverter.getEnvFile(parser.logosEnvFile());
    lock_guard lock(mtx);
    envFiles.emplace_back(file);
    errHandler.addErrors(antlerConverter.errHandler.errors);
}

void LgsApp::parseAppFile(path fileEntry) {
    const auto absFilePath = new path(canonical(fileEntry));
    AntlerConverter antlerConverter(*absFilePath, globals);
    auto codeText = getFileText(fileEntry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
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
            errHandler.addErrors(semaAnalyser.errHandler.errors);
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
    globals.addSymbol(lgsPrint.name, LgsSymbol(new LgsPrint()), &errHandler);
    globals.addSymbol(lgsSizeof.name, LgsSymbol(new LgsSizeOf()), &errHandler);
}

void LgsApp::loadEnvFiles() {
    vector<LgsEnvFile*> files;
    ThreadPool threadPool;
    for (const auto& entry : directory_iterator(paths.envsDir)) {
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
            checkRequiredEnvVar(requireEnvVar, envFile);
        }
    }
}

void LgsApp::checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile) {
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

void LgsApp::initPaths(const path& rootDirPath) {
    if (rootDirPath == "") return;
    paths.rootDir = rootDirPath;
    paths.rootDirAbs = canonical(paths.rootDir);
    paths.srcDir = paths.rootDir / LOGOS_SRC_DIR;
    paths.envsDir = paths.rootDir / LOGOS_ENVS_DIR;
    paths.buildDir = paths.rootDir / LOGOS_BUILD_DIR;
    paths.buildIR = paths.buildDir / LOGOS_BUILD_IR;
    paths.objFilePath = paths.buildDir / LOGOS_OBJECT_FILE;
    paths.execFilePath = paths.buildDir / LOGOS_EXECUTABLE_FILE;
    paths.appFilePath = paths.rootDir / LOGOS_APP_FILE_NAME LOGOS_FILE_EXTENSION;
    paths.clibRoot = CLIB_ROOT;
    paths.clibInclude = paths.clibRoot / "usr/include";
}

void LgsApp::handleExitWithErrors() const {
    for (auto error : errHandler.errors) {
        lgsLog(LOGOS_ERROR_STR + error.msg);
    }
    return exit(1);
}

void LgsApp::initBuildDir() const {
    if (exists(paths.buildDir)) remove_all(paths.buildDir);
    create_directories(paths.buildDir);
    create_directories(paths.buildIR);
}

void LgsApp::writeIRToFile() {
    for (const auto [_, module] : modules) {
        if constexpr (WRITE_IR_TO_FILE) {
            const auto filePath = (paths.buildIR / module->IRModule->getName().str()).string() + ".ll";
            std::error_code EC;
            raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
            module->IRModule->print(textFile, nullptr);
        }
        if (logLevel == DEBUG) {
            module->IRModule->print(outs(), nullptr);
            lgsLog("\n-----\n\n");
        }
    }
}

LgsApp::~LgsApp() {
    for (const auto file : files) {
        delete file;
    }
}
