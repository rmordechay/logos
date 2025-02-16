#ifndef LOGOSLINKER_H
#define LOGOSLINKER_H
#include <llvm/IR/Module.h>
#include <iostream>
#include "llvm/Linker/Linker.h"

#include <map>
#include <llvm/IR/Module.h>

class LogosLinker {
public:
    static void link(const std::map<std::string, llvm::Module*>& modules);
    static void writeFile(const std::unique_ptr<llvm::Module>& module, const std::string& filename);
    void runBinary();
    ~LogosLinker() = default;
};

#endif //LOGOSLINKER_H
