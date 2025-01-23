#ifndef LOGOSFILE_H
#define LOGOSFILE_H

#include "LogosParser.h"
#include "types/LogosType.h"

#include <llvm/IR/Module.h>
#include "LogosImportStmt.h"

#include <string>

using namespace std;

class LogosFile {
public:
    string name;
    string path;
    vector<LogosImportStmt*> imports;

    explicit LogosFile(const string& name) : name(name) {}
    virtual Module* generateModule(IRBuilder<>& builder, LogosStack& theStack) = 0;
    virtual void initModule(IRBuilder<>& builder, LogosStack& theStack) = 0;
    virtual ~LogosFile() = default;
};

#endif //LOGOSFILE_H
