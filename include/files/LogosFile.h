#ifndef LOGOSFILE_H
#define LOGOSFILE_H

#include "LogosParser.h"
#include "types/LogosType.h"

#include <llvm/IR/Module.h>

#include <string>
#include <llvm/Support/FileSystem.h>

class LogosStack;
using namespace std;

class LogosFile {
public:
    string name;
    string path;

    explicit LogosFile(const string& name, const string& path) : name(name), path(path) {}
    virtual ~LogosFile() = default;
};

inline void writeIRToFile(const Module* module, const string& name) {
    std::error_code EC;
    raw_fd_ostream textFile("../docs/src/build/" + name + ".ll", EC, sys::fs::OF_None);
    module->print(outs(), nullptr);
    module->print(textFile, nullptr);
}

#endif //LOGOSFILE_H
