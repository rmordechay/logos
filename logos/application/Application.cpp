#include "Application.h"

void Application::runLogos() {
    semaAnalyser.files = parse();
    if (!semaAnalyser.analyse()) return;
    codeGenerator.run(semaAnalyser.files, semaAnalyser.theStack);
}

map<string, LogosFile*> Application::parse() {
    ThreadPool threadPool;
    map<string, LogosFile*> files;
    flattenTree(rootPath, files, threadPool);
    threadPool.wait();
    return files;
}

void Application::flattenTree(const string& path, map<string, LogosFile*>& files, ThreadPool& threadPool) {
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
            flattenTree(entry.path(), files, threadPool);
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
    return antlerConverter.getLogosFile(parser.logosFile(), absolute(fileEntry).string());
}