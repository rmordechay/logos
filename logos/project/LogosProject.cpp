#include "LogosProject.h"

void LogosProject::runLogos() {
    const auto rootPackage = getRootPackage();
    if (!semaAnalyser->analyseCode(rootPackage)) {
        return;
    }
    codeGenerator->run(rootPackage);
    delete rootPackage;
}

LogosRootPackage* LogosProject::getRootPackage() {
    const auto rootPackage = new LogosRootPackage(rootPath);
    for (const auto& dirEntry : filesystem::directory_iterator(rootPath)) {
        auto dirPath = dirEntry.path();
        if (isLogosFile(dirEntry)) {
            if (isMainFile(dirEntry)) {
                const auto mainFile = getFile(dirEntry.path());
                rootPackage->mainFile = static_cast<LogosMainFile*>(mainFile);
            } else {
                auto file = getFile(dirPath);
                rootPackage->package->files.push_back(file);
            }
        } else if (is_directory(dirEntry.status())) {
            rootPackage->package = getPackage(dirPath);
        }
    }
    return rootPackage;
}

LogosPackage* LogosProject::getPackage(const filesystem::path& path) {
    const auto package = new LogosPackage(path.filename(), path);
    for (const auto& dirEntry : filesystem::directory_iterator(path)) {
        if (isLogosFile(dirEntry)) {
            auto logosFile = getFile(dirEntry.path());
            package->files.push_back(logosFile);
        } else if (is_directory(dirEntry.status())) {
            auto innerPackage = getPackage(dirEntry.path());
            package->packages.push_back(innerPackage);
        }
    }
    return package;
}

LogosFile* LogosProject::getFile(const filesystem::path& dirPath) {
    const auto codeText = getCodeText(dirPath);
    const auto fileCtx = parseFile(codeText);
    return antlerConverter->getLogosFile(fileCtx);
}

LogosParser::LogosFileContext* LogosProject::parseFile(string codeText) {
    input = make_unique<antlr4::ANTLRInputStream>(codeText);
    lexer = make_unique<LogosLexer>(input.get());
    tokens = make_unique<antlr4::CommonTokenStream>(lexer.get());
    parser = make_unique<LogosParser>(tokens.get());
    return parser->logosFile();
}

string LogosProject::getCodeText(const filesystem::path& path) {
    ifstream file(path);
    stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

LogosProject::~LogosProject() {
    delete antlerConverter;
    delete codeGenerator;
    delete semaAnalyser;
}