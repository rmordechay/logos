#include "Application.h"

#include "LogosPackage.h"
#include "ThreadPool.h"



void Application::runLogos() {
    const auto rootPackage = getPackage(rootPath);
    if (!semaAnalyser->analyseCode(rootPackage)) return;
    codeGenerator->run(semaAnalyser->files);
    delete rootPackage;
}

LogosPackage* Application::getPackage(const filesystem::path& path) {
    const auto package = new LogosPackage(path.filename(), path);
    for (const auto& dirEntry : filesystem::directory_iterator(path)) {
        if (Utils::isLogosFile(dirEntry)) {
            auto logosFile = getFile(dirEntry.path());
            package->files.push_back(logosFile);
        } else if (is_directory(dirEntry.status())) {
            auto innerPackage = getPackage(dirEntry.path());
            package->packages.push_back(innerPackage);
        }
    }
    return package;
}

LogosFile* Application::getFile(const filesystem::path& dirPath) const {
    const auto codeText = getCodeText(dirPath);
    const auto parser = parseFile(codeText);
    const auto logosFile = antlerConverter->getLogosFile(parser->logosFile());
    delete parser;
    return logosFile;
}

LogosParser* Application::parseFile(const string& codeText) {
    const auto input = new antlr4::ANTLRInputStream(codeText);
    const auto lexer = new LogosLexer(input);
    const auto tokens = new antlr4::CommonTokenStream(lexer);
    const auto parser = new LogosParser(tokens);
    return parser;
}

string Application::getCodeText(const filesystem::path& path) {
    ifstream file(path);
    stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

Application::~Application() {
    delete antlerConverter;
    delete codeGenerator;
    delete semaAnalyser;
}