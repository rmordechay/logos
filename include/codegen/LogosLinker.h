#ifndef LOGOSLINKER_H
#define LOGOSLINKER_H
#include <map>
#include <llvm/IR/Module.h>

using namespace llvm;
using namespace std;

class LogosLinker {
public:
    const char* objectFilePath;
    const char* execFilePath;

    LogosLinker(const char* objectFilePath, const char* execFilePath) : objectFilePath(objectFilePath), execFilePath(execFilePath) {}
    void link(const std::map<std::string, Module*>& modules);
    vector<const char*> getLinkerOpts();
    void writeExecFile(const std::unique_ptr<Module>& module) const;
    static std::unique_ptr<Module> getStdlibModule();
    ~LogosLinker() = default;
};

#endif //LOGOSLINKER_H
