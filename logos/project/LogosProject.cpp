#include "LogosProject.h"

void LogosProject::runLogos() {
    const auto rootPackage = getRootPackage();
    codeGenerator->run(rootPackage);
    delete rootPackage;
}

LogosRootPackage* LogosProject::getRootPackage() {
    const auto rootPackage = new LogosRootPackage(rootPath);
    for (const auto& dirEntry : filesystem::directory_iterator(rootPath)) {
        auto dirPath = dirEntry.path();
        if (isLogosFile(dirEntry)) {
            if (isMainFile(dirEntry)) {
                rootPackage->mainFile = static_cast<LogosMainFile*>(getFile(dirEntry.path()));
            } else {
                rootPackage->files.push_back(getFile(dirPath));
            }
        } else if (is_directory(dirEntry.status())) {
            auto package = getPackage(dirPath);
            rootPackage->packages.push_back(package);
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
    if (const auto mainFileCtx = fileCtx->mainFile()) {
        return antlerConverter->getMainFile(mainFileCtx);
    }
    return nullptr;
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
}