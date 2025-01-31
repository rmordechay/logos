#ifndef LOGOSFILE_H
#define LOGOSFILE_H

#include "LogosParser.h"
#include "types/LogosType.h"

#include <llvm/IR/Module.h>
#include "LogosImport.h"

#include <string>
#include <llvm/Support/FileSystem.h>

using namespace std;

class LogosFile {
public:
    string name;
    string path;
    vector<LogosImport*> imports;

    explicit LogosFile(const string& name, const string& path) : name(name), path(path) {}
    virtual void initModule(IRBuilder<>& builder, LogosStack& theStack) = 0;
    virtual Module* generateModule(IRBuilder<>& builder, LogosStack& theStack) = 0;
    virtual ~LogosFile();
};

inline LogosFile::~LogosFile() {
    for (const auto import : imports) {
        delete import;
    }
}

inline void writeIRToFile(const Module* module, const string& name) {
    std::error_code EC;
    raw_fd_ostream textFile("../codegen/" + name + ".ll", EC, sys::fs::OF_None);
    module->print(outs(), nullptr);
    module->print(textFile, nullptr);
}

#endif //LOGOSFILE_H
