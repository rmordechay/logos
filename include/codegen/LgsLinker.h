#ifndef LOGOSLINKER_H
#define LOGOSLINKER_H
#include <llvm/IR/Module.h>
#include <llvm/Linker/Linker.h>

struct LgsPaths;
using namespace llvm;
using namespace std;

const string STD_LIBS[] = {
    "../stdlib/start.ll",
    "../stdlib/lgslib.ll",
    "../stdlib/array.ll",
    "../stdlib/string.ll",
    "../stdlib/map.ll",
};

class LgsLinker {
public:
    bool link() const;
    void linkStdlib(const string& path, Linker* linker) const;
    ~LgsLinker() = default;
};

#endif //LOGOSLINKER_H
