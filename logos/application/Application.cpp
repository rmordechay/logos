#include "Application.h"

#include "ThreadPool.h"

#include <future>


void Application::runLogos() {
    vector<future<LogosFile*>> fileFutures;
    flattenTree(rootPath, fileFutures);
    vector<LogosFile*> files;
    for (auto& fileFuture : fileFutures) {
        files.push_back(fileFuture.get());
    }
    if (!semaAnalyser->analyse(files)) {
        return;
    }
    codeGenerator->run(semaAnalyser->files);
}

void Application::flattenTree(const filesystem::path& path, vector<future<LogosFile*>>& files) {
    for (const auto& dirEntry : filesystem::directory_iterator(path)) {
        if (Utils::isLogosFile(dirEntry)) {
            files.push_back(getFile(dirEntry.path()));
        } else if (is_directory(dirEntry.status())) {
            flattenTree(dirEntry.path(), files);
        }
    }
}

future<LogosFile*> Application::getFile(const filesystem::path& path) const {
    return async(launch::async, [this, path] {
        std::ifstream file(path);
        std::stringstream fileContents;
        fileContents << file.rdbuf();
        auto codeText = fileContents.str();
        auto input = antlr4::ANTLRInputStream(codeText);
        auto lexer = LogosLexer(&input);
        auto tokens = antlr4::CommonTokenStream(&lexer);
        auto parser = LogosParser(&tokens);
        auto logosFile = antlerConverter->getLogosFile(parser.logosFile());
        logosFile->name = path.stem().string();
        logosFile->path = absolute(path);
        return logosFile;
    });
}

Application::~Application() {
    delete antlerConverter;
    delete codeGenerator;
    delete semaAnalyser;
}