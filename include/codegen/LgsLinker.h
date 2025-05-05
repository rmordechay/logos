#ifndef LOGOSLINKER_H
#define LOGOSLINKER_H
#include <llvm/IR/Module.h>
#include <llvm/Linker/Linker.h>

struct LgsPaths;
using namespace llvm;
using namespace std;

#define STD_LIBS {"../stdlib/lgslib.ll", "../stdlib/array.ll", "../stdlib/string.ll", "../stdlib/map.ll"}

class LgsLinker {
public:
    bool link() const;
    bool getLinkFunc() const;
    void linkStdlib(const string& path, Linker* linker) const;
    ~LgsLinker() = default;
};

#endif //LOGOSLINKER_H
