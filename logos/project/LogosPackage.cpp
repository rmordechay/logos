#include "LogosPackage.h"

LogosPackage::LogosPackage(const std::string& name, const std::string& path) {
    this->name = name;
    this->path = std::filesystem::absolute(path).string();
}

LogosPackage::~LogosPackage() {
    for (const auto file : files) {
        delete file;
    }
    for (const auto package : packages) {
        delete package;
    }
}

