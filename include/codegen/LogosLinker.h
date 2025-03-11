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
    const char* objectFile;
    const char* execFile;

    void link(const std::map<std::string, Module*>& modules);
    vector<const char*> getLinkerOpts();
    static void writeFile(const std::unique_ptr<Module>& module, const std::string& filename);
    static std::unique_ptr<Module> getStdlibModule();
    ~LogosLinker() = default;
};

#endif //LOGOSLINKER_H
