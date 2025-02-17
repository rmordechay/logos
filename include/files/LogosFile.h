#ifndef LOGOSFILE_H
#define LOGOSFILE_H
#include <LogosDefinitions.h>
#include <string>
#include <llvm/IR/Module.h>
#include <llvm/Support/FileSystem.h>
#include "types/LogosType.h"

class LogosStack;
using namespace std;

class LogosFile {
public:
    string name;
    string path;

    explicit LogosFile(const string& name, const string& path) : name(name), path(path) {}
    virtual ~LogosFile() = default;
};

#endif //LOGOSFILE_H
