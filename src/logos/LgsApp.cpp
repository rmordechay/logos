#include "logos/LgsApp.h"
#include "LogosLexer.h"
#include "analysis/AntlrConverter.h"
#include "analysis/SemaAnalyser.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "logos/Platform.h"
#include "utils/ThreadPool.h"
#include "builtin/LgsBuiltinFuncs.h"
#include "codegen/CodeGenerator.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "files/LgsAppFile.h"
#include "files/LgsEnvFile.h"
#include "funcs/LgsMainFunc.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsInterface.h"

extern char **environ;

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
    thread tSrcFiles([this] {
        vector<LgsFile*> files;
        ThreadPool threadPool;
        threadPool.start();
        parseSrcFiles(paths.srcDir, threadPool);
        threadPool.wait();
    });
    thread tGlobals([this] { loadGlobals(); });
    tSrcFiles.join();
    tGlobals.join();
    return resolveGlobalTypes();
}

bool LgsApp::analyse() {
    ThreadPool threadPool;
    threadPool.start();
    for (const auto file : files) {
        threadPool.runTask([=, &file] {
            SemaAnalyser semaAnalyser(file);
            semaAnalyser.start();
            if (!semaAnalyser.errHandler.successful) {
                lock_guard lock(mtx);
                addErrors(semaAnalyser.errHandler.errors);
                errHandler.setUnsuccessful();
            }
        });
    }
    threadPool.wait();
    SemaAnalyser::reprocessFuncs(files);
    return errHandler.successful;
}

bool LgsApp::generate() {
    CodeGenerator::init(paths);
    ThreadPool threadPool;
    threadPool.start();
    for (const auto file : files) {
        threadPool.runTask([=, &file] {
            const auto module = file->generateIR();
            if (!module) return;
            lock_guard lock(mtx);
            IRModules[file->name] = module;
        });
    }
    threadPool.wait();
    CodeGenerator::writeIRToFile(IRModules, paths);
    return errHandler.successful;
}

bool LgsApp::link() const {
    Module* mainModule = IRModules.find(LOGOS_MAIN_FILE_NAME)->second;
    assert(mainModule);
    Linker llvmLinker(*mainModule);
    for (const auto& [name, module] : IRModules) {
        if (name == LOGOS_MAIN_FILE_NAME) continue;
        llvmLinker.linkInModule(unique_ptr<Module>(module));
    }
    if (!generateObjFile(mainModule)) return false;
    auto linkerOpts = platform.linkerOpts;
    linkerOpts.push_back(paths.objFilePath.c_str());
    linkerOpts.push_back("-o");
    linkerOpts.push_back(paths.execFilePath.c_str());
    if (!platform.link(linkerOpts, outs(), errs(), false, false)) {
        errs().flush();
        return false;
    }
    return true;
}

void LgsApp::run() const {
    execv(paths.execFilePath.c_str(), args.data());
}

void LgsApp::parseSrcFiles(const string& path, ThreadPool& threadPool) {
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

void LgsApp::parseSrcFile(path entry) {
    const path absFilePath = canonical(entry);
    AntlerConverter antlerConverter;
    antlerConverter.errHandler.filePath = absFilePath;
    const auto codeText = getFileText(entry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto lgsFile = parser.logosFile();
    if (parser.getNumberOfSyntaxErrors() == 0) {
        const auto file = antlerConverter.getLogosFile(lgsFile, absFilePath);
        lock_guard lock(mtx);
        files.push_back(file);
        if (!antlerConverter.errHandler.successful) {
            addErrors(antlerConverter.errHandler.errors);
            errHandler.setUnsuccessful();
        }
    } else {
        errHandler.setUnsuccessful();
    }
}

void LgsApp::parseEnvFile(path fileEntry) {
    const auto absFilePath = canonical(fileEntry);
    AntlerConverter antlerConverter;
    antlerConverter.errHandler.filePath = absFilePath;
    const auto codeText = getFileText(fileEntry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    auto file = antlerConverter.getEnvFile(parser.logosEnvFile());
    lock_guard lock(mtx);
    envFiles.emplace_back(file);
    addErrors(antlerConverter.errHandler.errors);
}

bool LgsApp::resolveGlobalTypes() const {
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
                if (dynamic_cast<LgsMainFunc*>(func)) continue;
                semaAnalyser.resolveFuncTypes(func->funcType);
            }
        } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            semaAnalyser.resolveObjTypes(objFile->obj);
        } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
            auto methods = interfaceFile->interface->methods;
            for (const auto& [_, method] : methods) {
                semaAnalyser.resolveFuncTypes(method->funcType);
            }
        }
        if (!semaAnalyser.errHandler.successful) return false;
    }
    return true;
}

void LgsApp::parseAppFile(path fileEntry) {
    auto absFilePath = canonical(fileEntry);
    AntlerConverter antlerConverter;
    antlerConverter.errHandler.filePath = absFilePath;

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

bool LgsApp::generateObjFile(Module* module) const {
    error_code ec;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(paths.objFilePath.c_str(), ec, sys::fs::OF_None);
    const auto addedPassFailed = getTargetMachine()->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    if (addedPassFailed) {
        cerr << ec.message() << endl;
        return false;
    }

    if (verifyModule(*module, &errs())) {
        errs().flush();
        return false;
    }

    pass.run(*module);
    outputStream.flush();
    outputStream.close();
    return true;
}

void LgsApp::loadGlobals() {
    globals.addSymbol(lgsPrint.name, LgsSymbol(&lgsPrint), &errHandler);
    globals.addSymbol(lgsSizeof.name, LgsSymbol(&lgsSizeof), &errHandler);
}

void LgsApp::loadEnvFiles() {
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

void LgsApp::checkDuplicateFiles(const vector<LgsFile*>& files) {
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
    paths.objFilePath = paths.buildDir / LOGOS_OBJECT_FILE;
    paths.execFilePath = paths.buildDir / LOGOS_EXECUTABLE_FILE;
    paths.appFilePath = paths.rootDir / LOGOS_APP_FILE_NAME LOGOS_FILE_EXTENSION;
    paths.clibRoot = CLIB_ROOT;
}

bool LgsApp::isLogosFile(const directory_entry& entry) const {
    return entry.is_regular_file() && entry.path().extension().string() == LOGOS_FILE_EXTENSION;
}

void LgsApp::addErrors(vector<LgsError> newErrors) {
    errHandler.errors.insert(errHandler.errors.end(), newErrors.begin(), newErrors.end());
}