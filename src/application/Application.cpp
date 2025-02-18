#include "application/Application.h"

#include <ANTLRInputStream.h>
#include <AntlrConverter.h>
#include <CodeGenerator.h>
#include <LogosLexer.h>
#include <LogosParser.h>
#include <ThreadPool.h>

void Application::runLogos() {
    semaAnalyser.files = parse();
    if (!semaAnalyser.analyse()) return;
    const auto codeGenerator = CodeGenerator(semaAnalyser.mainStack, semaAnalyser.files);
    codeGenerator.generateCode();
    linker.runBinary();
}

map<string, LogosFile*> Application::parse() {
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

LogosFile* Application::getFile(const directory_entry& fileEntry) {
    ifstream file(fileEntry);
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