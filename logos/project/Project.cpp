#include "Project.h"
#include <fstream>
#include <sstream>

#include "LogosLexer.h"
#include "LogosParser.h"
#include "antlr4-runtime/antlr4-runtime.h"

using namespace antlr4;

Project::Project(const std::string& path) {
    if (!fs::exists(path)) {
        throw std::invalid_argument("Path does not exist: " + path);
    }
    if (!fs::is_directory(path)) {
        throw std::invalid_argument("Path is not a directory: " + path);
    }
    dirPath = path;
}

void Project::parseFile(const std::string& code) {
    ANTLRInputStream input(code);
    LogosLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    tree::ParseTree* tree = parser.entry();

    for (auto child : tree->children) {
        std::string text = child->getText();
        size_t start = text.find('"') + 1;
        size_t end = text.rfind('"');
        std::cout << text.substr(start, end - start) << std::endl;
    }
}

void Project::addLogosFile(const fs::directory_entry& entry) {
    std::ifstream file(entry.path());
    if (!file) {
        std::cerr << "Could not open file: " << entry.path() << std::endl;
        return;
    }
    std::stringstream fileContents;
    fileContents << file.rdbuf();
    std::string content = fileContents.str();
    files.push_back(new LogosFile(content));
}

void Project::scanPackage(const std::string& packagePath) {
    for (const auto& entry : fs::directory_iterator(packagePath)) {
        if (is_regular_file(entry.status())) {
            addLogosFile(entry);
        } else if (is_directory(entry.status())) {
            scanPackage(entry.path());
        }
    }
}


void Project::scanProject() {
    scanPackage(dirPath);
    for (auto file : files) {
        parseFile(file->code);
    }
}

Project::~Project() {
    for (const LogosFile* file : files) {
        delete file;
    }
    files.clear();
}
