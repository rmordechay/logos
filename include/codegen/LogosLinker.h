#ifndef LOGOSLINKER_H
#define LOGOSLINKER_H
#include <map>
#include <llvm/IR/Module.h>
#include <llvm/Support/SourceMgr.h>
#include "LogosDefinitions.h"
#include <llvm/TargetParser/Host.h>

using namespace llvm;

class LogosLinker {
public:
    SMDiagnostic EC;
    const std::string targetTriple = sys::getProcessTriple();

    void link(const std::map<std::string, Module*>& modules);
    void writeFile(const std::unique_ptr<Module>& module, const std::string& filename) const;
    ~LogosLinker() = default;
};

#endif //LOGOSLINKER_H
