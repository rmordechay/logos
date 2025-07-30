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
#include "../../include/configs/LgsConfig.h"
#include "logos/LgsLinker.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsInterface.h"
#include "utils/LgsIRUtils.h"

extern char **environ;

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
    if (!resolveGlobalTypes()) exitWithErrors();
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
    initBuild();
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
    return errHandler.successful;
}

bool LgsApp::link() const {
    const LgsLinker linker(paths, modules);
    return linker.link();
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

void LgsApp::exitWithErrors() const {
    for (const auto error : errHandler.errors) {
        logInfo(LOGOS_ERROR_STR + string(error.msg));
    }
    return exit(1);
}

void LgsApp::initBuild() const {
    if (exists(paths.buildDir)) remove_all(paths.buildDir);
    create_directories(paths.buildDir);
    create_directories(paths.buildIR);
    writeDebugFile();
    initLLVM();
}

void LgsApp::writeDebugFile() const {
    ofstream ofs(paths.debugFile, ios::binary);
    for (const auto file : files) {
        const auto s = file->absPath.string();
        file->pathIndex = ofs.tellp();
        uint32_t len = static_cast<uint32_t>(s.size());
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(uint32_t));
        ofs.write(s.data(), s.size());
    }
}

LgsApp::~LgsApp() {
    for (const auto file : files) {
        delete file;
    }
}
