#include "application/Application.h"

#include <ANTLRInputStream.h>
#include <AntlrConverter.h>
#include <CodeGenerator.h>
#include <LogosLexer.h>
#include <LogosParser.h>
#include <ThreadPool.h>
#include <funcs/LogosPrint.h>
#include <ranges>


void Application::runLogos() {
    const map<string, LogosFile*> files = parseFiles();
    const map<string, LogosSymbol> globalSymbols = collectGlobals(files);
    SemaAnalyser::analyse(files, globalSymbols);
    const CodeGenerator codeGenerator = CodeGenerator(mainFile);
    codeGenerator.generateCode(globalSymbols);
    linker.runBinary();
}

map<string, LogosFile*> Application::parseFiles() {
    ThreadPool threadPool;
    map<string, LogosFile*> files;
    parseTree(rootPath, files, threadPool);
    threadPool.wait();
    return files;
}

void Application::parseTree(const string& path, map<string, LogosFile*>& files, ThreadPool& threadPool) {
    for (const auto& entry : directory_iterator(path)) {
        if (Utils::isLogosFile(entry)) {
            threadPool.runTask([entry, &files, this] {
                const auto logosFile = getFile(entry);
                if (const auto mainFile = dynamic_cast<LogosMainFile*>(logosFile)) {
                    this->mainFile = mainFile;
                }
                {
                    lock_guard lock(mtx);
                    files[logosFile->name] = logosFile;
                }
            });
        } else if (is_directory(entry.status())) {
            parseTree(entry.path(), files, threadPool);
        }
    }
}

map<string, LogosSymbol> Application::collectGlobals(const map<string, LogosFile*>& files) {
    map<string, LogosSymbol> globalSymbols;
    globalSymbols["print"] = LogosSymbol(INTERNAL_FUNC, new LogosPrint());
    for (const auto& file : files | views::values) {
        if (const auto objFile = dynamic_cast<LogosObjectFile*>(file)) {
            const auto object = objFile->obj;
            globalSymbols[object->name()] = LogosSymbol(OBJECT, object);
        }
    }
    return globalSymbols;
}

LogosFile* Application::getFile(const directory_entry& fileEntry) {
    ifstream file(fileEntry.path());
    stringstream fileContents;
    fileContents << file.rdbuf();
    auto codeText = fileContents.str();
    auto input = ANTLRInputStream(codeText);
    auto lexer = LogosLexer(&input);
    auto tokens = CommonTokenStream(&lexer);
    auto parser = LogosParser(&tokens);
    auto antlerConverter = AntlerConverter(fileEntry.path());
    auto parsedFile = parser.logosFile();
    return antlerConverter.getLogosFile(parsedFile, absolute(fileEntry).string());
}