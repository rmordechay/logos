#ifndef LOGOSLINKER_H
#define LOGOSLINKER_H

#include "logos/LgsProject.h"
#include <llvm/IR/Verifier.h>

struct LgsPaths;
using namespace llvm;
using namespace std;

class LgsLinker {
public:
    bool link(LogosProject& project) const;
    bool generateObjFile(Module* module, const string& path) const;
    ~LgsLinker() = default;
};

#endif //LOGOSLINKER_H
