#ifndef LOGOSLINKER_H
#define LOGOSLINKER_H
#include "CodeGenMetadata.h"
#include <iostream>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/FileSystem.h>

struct LgsPaths;
using namespace llvm;
using namespace std;

class LgsLinker {
public:
    bool link() const;
    bool generateObjFile(Module* module, const string& path) const;
    ~LgsLinker() = default;
};

#endif //LOGOSLINKER_H
