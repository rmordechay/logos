#ifndef LOGOSLINKER_H
#define LOGOSLINKER_H
#include <llvm/IR/Module.h>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/SourceMgr.h>

class LogosLinker {
public:
    llvm::SMDiagnostic EC;

    void link(const std::map<std::string, llvm::Module*>& modules);
    static void writeFile(const std::unique_ptr<llvm::Module>& module, const std::string& filename);
    ~LogosLinker() = default;
};

#endif //LOGOSLINKER_H
