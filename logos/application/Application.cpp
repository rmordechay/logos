#include "Application.h"

void Application::runLogos() {
    semaAnalyser.unprocessedFiles = parse();
    if (!semaAnalyser.analyse()) return;
    codeGenerator.run(semaAnalyser.validFiles);
}

vector<LogosFile*> Application::parse() {
    ThreadPool threadPool;
    auto files = vector<LogosFile*>();
    flattenTree(rootPath, files, threadPool);
    threadPool.wait();
    return files;
}

void Application::flattenTree(const string& path, vector<LogosFile*>& files, ThreadPool& threadPool) {
    for (const auto& entry : directory_iterator(path)) {
        if (Utils::isLogosFile(entry)) {
            threadPool.runTask([entry, &files, this] {
                const auto logosFile = getFile(entry);
                {
                    lock_guard lock(mtx);
                    files.emplace_back(logosFile);
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