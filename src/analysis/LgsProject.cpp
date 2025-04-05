#include "analysis/LgsProject.h"
#include "AntlrConverter.h"
#include "LgsGlobals.h"
#include "Logos.h"
#include "LogosLexer.h"
#include "LogosParser.h"
#include "ThreadPool.h"
#include "builtin/LgsSys.h"
#include "funcs/LgsPrint.h"

#include <iostream>

using namespace std;

bool LgsProject::loadProject() {
    if (!validateProject()) return false;
    loadFiles();
    return true;
}

void LgsProject::loadFiles() {
    thread t1([this] { loadEnvFiles(); });
    thread t2([this] { loadSrcFiles(); });
    thread t3([this] { loadGlobals(); });
    t1.join();
    t2.join();
    t3.join();
}

void LgsProject::loadSrcFiles() {
    ThreadPool threadPool;
    threadPool.start();
    vector<LgsFile*> files;
    parseSrcFiles(paths->srcDir, threadPool);
    threadPool.wait();
    checkDuplicateFiles();
}

void LgsProject::parseSrcFiles(const string& path, ThreadPool& threadPool) {
    for (const auto& entry : directory_iterator(path)) {
        if (isLogosFile(entry)) {
            threadPool.runTask([entry, this] {
                parseSrcFile(entry);
            });
        } else if (is_directory(entry.status())) {
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
    const auto file = AntlerConverter::getLogosFile(parser.logosFile(), absFilePath);
    file->relPath = relative(absFilePath, paths->rootDir).lexically_relative(LOGOS_SRC_DIR);
    lock_guard lock(mtx);
    files.emplace_back(file);
    if (file->name == LOGOS_MAIN_FILE_NAME) {
        mainFile = dynamic_cast<LgsMainFile*>(file);
    }
}

void LgsProject::loadEnvFiles() {
    ThreadPool threadPool;
    threadPool.start();
    vector<LgsEnvFile*> files;
    for (const auto& entry : directory_iterator(paths->envsDir)) {
        if (!isLogosFile(entry)) continue;
        threadPool.runTask([entry, this] {
            parseEnvFile(entry);
        });
    }
    threadPool.wait();
}

void LgsProject::parseEnvFile(path fileEntry) {
    auto absFilePath = canonical(fileEntry);
    auto codeText = getFileText(fileEntry);
    ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    auto file = AntlerConverter::getLogosEnvFile(parser.logosEnvFile(), absFilePath);
    lock_guard lock(mtx);
    envFiles.emplace_back(file);
}

string LgsProject::getFileText(path filePath) const {
    ifstream file(canonical(filePath));
    stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}


void LgsProject::loadGlobals() const {
    globals.funcs[LgsPrint::name] = {
        new LgsPrint({new LgsParam(new LgsInt())}),
        new LgsPrint({new LgsParam(new LgsFloat())}),
        new LgsPrint({new LgsParam(new LgsStr())}),
        new LgsPrint({new LgsParam(new LgsChar())}),
        new LgsPrint({new LgsParam(new LgsBool())}),
    };
    globals.symbols[LgsSys::name] = LgsSymbol(new LgsSys());
}

bool LgsProject::validateProject() const {
    if (!is_directory(paths->rootDir) || !is_directory(paths->srcDir)) {
        printError(E10010.msg);
        return false;
    }

    if (!exists(paths->srcDir / LOGOS_MAIN_FILE_NAME LOGOS_FILE_EXTENSION)) {
        printError(E10008.msg);
        return false;
    }
    return true;
}

void LgsProject::checkDuplicateFiles() const {
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
        printError(E10007.msg, {name, errMsg.str()});
    }
}

bool LgsProject::isLogosFile(const directory_entry& entry) const {
    return entry.is_regular_file() && entry.path().extension().string() == LOGOS_FILE_EXTENSION;
}