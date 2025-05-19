#ifndef LOGOSLINKER_H
#define LOGOSLINKER_H
#include <llvm/IR/Module.h>
#include <llvm/Linker/Linker.h>

struct LgsPaths;
using namespace llvm;
using namespace std;

class LgsLinker {
public:
    bool link() const;
    ~LgsLinker() = default;
};

#endif //LOGOSLINKER_H
