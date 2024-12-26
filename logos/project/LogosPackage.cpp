#include "LogosPackage.h"

#include "LogosConfigs.h"

#include <fstream>
#include <iostream>
#include <sstream>

LogosPackage::LogosPackage(const std::string& name, const std::string& path) {
    this->name = name;
    this->path = std::filesystem::absolute(path).string();
    this->mainFile = nullptr;
}

void LogosPackage::scanPackage() {
    for (const auto& directoryEntry : std::filesystem::directory_iterator(path)) {
        if (isLogosFile(directoryEntry)) {
            auto logosFile = readLogosFile(directoryEntry.path());
            logosFile->parseFile();
            files.push_back(logosFile);
            if (logosFile->fileCtx->mainFile() != nullptr) {
                mainFile = logosFile;
            }
        } else if (is_directory(directoryEntry.status())) {
            auto packagePath = directoryEntry.path();
            const auto newPackage = new LogosPackage(packagePath.filename(), packagePath);
            packages.push_back(newPackage);
            newPackage->scanPackage();
        }
    }
}

LogosFile* LogosPackage::readLogosFile(const std::filesystem::path& path) {
    std::ifstream file(path);
    std::stringstream fileContents;
    fileContents << file.rdbuf();
    std::string contentString = fileContents.str();
    return new LogosFile(contentString, path.stem().string());
}

bool LogosPackage::isLogosFile(const std::filesystem::directory_entry& filePath) {
    return filePath.is_regular_file() && filePath.path().extension().string() == LOGOS_EXTENSION;
}

bool LogosPackage::isMainFile(const std::filesystem::directory_entry& filePath) {
    return filePath.path().stem().string() == LOGOS_MAIN_FILE;
}

LogosPackage::~LogosPackage() {
    for (const auto file : files) {
        delete file;
    }
    for (const auto package : packages) {
        delete package;
    }
}