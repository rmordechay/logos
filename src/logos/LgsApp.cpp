#include "logos/LgsApp.h"
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Module.h>
#include "analysis/LgsSema.h"
#include "builtins/LgsTest.h"
#include "logos/LgsPaths.h"
#include "utils/ThreadPool.h"
#include "builtins/LgsPrint.h"
#include "builtins/LgsReflect.h"
#include "builtins/LgsSystem.h"
#include "files/LgsEnvFile.h"
#include "codegen/LgsCodeGen.h"
#include "codegen/LgsLinker.h"
#include "data/LgsConfigs.h"
#include "files/LgsTestFile.h"
#include "parser/LgsLexer.h"
#include "parser/LgsParser.h"
#include "utils/LgsUtils.h"
#include "llvm/IR/Verifier.h"
#include <llvm/Target/TargetMachine.h>

void LgsApp::run() {
    if (!setup()) exitWithErrors();
    if (!parse()) exitWithErrors();
    if (!analyse()) exitWithErrors();
    if (!generate()) exitWithErrors();
    if (!link()) exitWithErrors();
    execute();
}

void LgsApp::runTests() {
    if (!setup()) exitWithErrors();
    if (!parse()) exitWithErrors();
    if (!analyse()) exitWithErrors();
    if (!generate()) exitWithErrors();
    if (!link()) exitWithErrors();
}

bool LgsApp::setup() {
    if (isLogosFile(paths.rootPath)) {
        appConfigs.isFileMode = true;
        return true;
    }
    paths.initPaths();
    if (!is_directory(paths.rootPath) || !is_directory(paths.srcDir)) {
        errHandler.addError(E10010, nullptr);
        return false;
    }
    if (!appConfigs.isFileMode && !fs::exists(paths.appFilePath)) {
        errHandler.addError(E10086, nullptr, {paths.rootPath});
        return false;
    }
    return true;
}

bool LgsApp::parse() {
    loadBuiltins();
    // if (!loadAppFile()) return false;
    // loadEnvFiles();
    for (const auto& entry : fs::recursive_directory_iterator(paths.srcDir)) {
        if (!isLogosFile(entry)) continue;
        threadPool.runTask([entry, this] {
            loadSrcFile(getFileText(entry), entry);
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::analyse() {
    LgsTypeResolver typeResolver(errHandler, globals);
    if (!typeResolver.resolveGlobalTypes(srcFiles, threadPool)) {
        return false;
    }
    for (const auto file : srcFiles) {
        threadPool.runTask([this, file] {
            LgsSema semaAnalyser(file, globals);
            semaAnalyser.analyse();
            if (semaAnalyser.errHandler.successful) return;
            {
                std::lock_guard lock(mtx);
                errHandler.mergeErrors(semaAnalyser.errHandler);
            }
        });
    }
    threadPool.wait();
    return errHandler.successful;
}

bool LgsApp::generate() {
    initBuild();
    const auto targetMachine = LgsLLVMGen::getTargetMachine();
    for (const auto& file : srcFiles) {
        threadPool.runTask([this, file, targetMachine] {
            LgsCodeGen code(*file);
            code.generate(appConfigs, *targetMachine);
        });
    }
    threadPool.wait();
    writeIRFiles();
    return errHandler.successful;
}

bool LgsApp::link() {
    LgsLinker linker(appConfigs, paths, srcFiles);
    return linker.link();
}

void LgsApp::execute() {
    const auto execPath = paths.execFilePath.c_str();
    appArgs.insert(appArgs.begin(), const_cast<char*>(execPath));
    if (appArgs.empty() || appArgs.back() != nullptr) {
        appArgs.push_back(nullptr);
    }
    execv(execPath, appArgs.data());
    perror("Logos execution failed.");
    exit(EXIT_FAILURE);
}

void LgsApp::loadBuiltins() {
    globals.addSymbol(LgsSymbol(new LgsPrint(), false, true), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsSystem(), false, true), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsTest(), false, true), &errHandler);
    globals.addSymbol(LgsSymbol(new LgsReflect(), false, true), &errHandler);
}

void LgsApp::loadSrcFile(const std::string& code, const fs::path& filePath) {
    const auto fileID = getNextFileID(filePath);
    LgsLexer lexer(fileID, code);
    const auto tokens = lexer.tokenize();
    if (!lexer.errHandler.successful) {
        errHandler.mergeErrors(lexer.errHandler);
        return;
    }
    LgsParser parser(fileID, filePath, paths, globals, tokens);
    const auto file = parser.parseSrcFile(appConfigs.isTestRun);
    {
        std::lock_guard lock(mtx);
        if (file) srcFiles.push_back(file);
        if (parser.errHandler.successful) return;
        errHandler.mergeErrors(parser.errHandler);
    }
}

bool LgsApp::loadConfigFile() {
    const auto appFileID = getNextFileID(paths.appFilePath);
    LgsLexer lexer(appFileID, getFileText(paths.appFilePath));
    const auto tokens = lexer.tokenize();
    if (!lexer.errHandler.successful) {
        errHandler.mergeErrors(lexer.errHandler);
        return false;
    }
    LgsParser parser(appFileID, paths.appFilePath, paths, globals, tokens);
    configFile = parser.parseConfigFile();
    errHandler.mergeErrors(parser.errHandler);
    if (errHandler.successful) loadConfigs();
    return errHandler.successful;
}

void LgsApp::loadEnvFiles() {
    for (const auto& filePath : fs::directory_iterator(paths.envsDir)) {
        if (!isLogosFile(filePath)) continue;
        threadPool.runTask([filePath, this] {
            auto code = getFileText(filePath);
            const auto fileID = getNextFileID(filePath);
            LgsLexer lexer(fileID, code);
            const auto tokens = lexer.tokenize();
            if (!lexer.errHandler.successful) {
                errHandler.mergeErrors(lexer.errHandler);
                return;
            }
            LgsParser parser(fileID, filePath, paths, globals, tokens);
            const auto file = parser.parseEnvFile();
            if (!file) return;
            {
                std::lock_guard lock(mtx);
                envFiles.push_back(file);
            }
        });
    }
}

void LgsApp::initBuild() {
    assert(paths.buildDir != "");
    if (!fs::exists(paths.buildDir)) {
        fs::create_directories(paths.buildDir);
    }
    if (!fs::exists(paths.buildIR)) {
        fs::create_directories(paths.buildIR);
    }
    LgsLLVMGen::initLLVM();
    paths.objFilePath = paths.buildDir / (appConfigs.name + ".o");
    paths.execFilePath = paths.buildDir / appConfigs.name;
}

void LgsApp::writeIRFiles() {
    for (const auto file : srcFiles) {
        const auto module = file->generator.IRModule;
        if (!module) continue;
        if constexpr (PRINT_IR) {
            module->print(outs(), nullptr);
            logInfo(LGS_MSG_LINE_SEPERATOR);
        }
        if (verifyModule(*module, &errs())) {
            errHandler.setUnsuccessful();
            continue;
        }
        if constexpr (WRITE_IR_TO_FILE && IS_DEVELOPMENT) {
            const auto filePath = (paths.buildIR / module->getName().str()).string() + ".ll";
            std::error_code EC;
            raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
            module->print(textFile, nullptr);
        }
    }
}

void LgsApp::exitWithErrors() const {
    for (int i = 0; i < errHandler.errors.size(); ++i) {
        const auto err = errHandler.errors[i];
        const auto column = err.location.columnStart;
        const auto line = err.location.lineStart;
        const auto filePath = filePaths.find(err.location.fileID);
        assert(filePath != filePaths.end());
        const auto fullPath = getFullPath(err.location, filePath->second);
        auto lineStr = getLine(filePath->second.string(), line);
        const auto firstNonSpace = std::find_if(lineStr.begin(), lineStr.end(), [](const unsigned char c) { return !std::isspace(c); });
        const auto trimmedCount = std::distance(lineStr.begin(), firstNonSpace);
        auto errMsg = lineStr.substr(trimmedCount);
        auto firstPart = column - LGS_PADDING_SIZE + 1;
        if (firstPart <= 0) {
            firstPart = LGS_PADDING_SIZE;
        }
        errMsg += LGS_ERROR_PADDING + std::string(firstPart, '~');
        errMsg += '^';
        auto secondPart = lineStr.size() - column + 1;
        if (secondPart <= 0) {
            secondPart = LGS_PADDING_SIZE;
        }
        errMsg += std::string(secondPart, '~');
        errMsg += err.msg;
        const auto atPath = "\n   at: " + fullPath;
        logInfo(LGS_ERROR_STR + errMsg);
        logInfo(atPath);
        if (i != errHandler.errors.size() - 1) logInfo(LGS_MSG_LINE_SEPERATOR);
    }
    if (!errHandler.errors.empty()) logInfo("\n");
    exit(1);
}

void LgsApp::loadConfigs() {
    for (const auto config : configFile->configs) {
        const auto configNama = config->name;
        if (configNama == "name") {
            appConfigs.name = config->expr->asStrConst()->value;
        }
        if (configNama == "activeEnv") {
            appConfigs.activeEnv = config->expr->asStrConst()->value;
        }
        if (configNama == "version") {
            auto value = config->expr->asStrConst()->value;
            int consumed = 0;
            auto [major, minor, micro] = appConfigs.version;
            const auto s = std::sscanf(value.c_str(), "%hu.%hu.%hu%n", &major, &minor, &micro, &consumed) == 3;
            if (!s || value[consumed] != '\0') {
                errHandler.addError(E10068, &config->location, {value});
            }
        }
    }
}

size_t LgsApp::getNextFileID(const fs::path& filePath) {
    const auto fileID = nextFileID.fetch_add(1, std::memory_order_relaxed);
    {
        std::lock_guard lock(mtx);
        filePaths[fileID] = filePath;
    }
    return fileID;
}

LgsApp::~LgsApp() {
    if (configFile) {
        delete configFile;
        configFile = nullptr;
    }
    for (const auto file : srcFiles) {
        delete file;
    }
    srcFiles.clear();
    for (const auto envFile : envFiles) {
        delete envFile;
    }
    envFiles.clear();
    for (const auto testFile : testsFiles) {
        delete testFile;
    }
    testsFiles.clear();
}
