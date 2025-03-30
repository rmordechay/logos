#ifndef LOGOSLINKER_H
#define LOGOSLINKER_H
#include <map>
#include <llvm/IR/Module.h>
#include <filesystem>
#include <llvm/Linker/Linker.h>

using namespace llvm;
using namespace std;

namespace lld::macho {
    bool link(ArrayRef<const char *> argsArr, raw_ostream &stdoutOS, raw_ostream &stderrOS, bool exitEarly, bool disableOutput);
}

class LgsLinker {
public:
    filesystem::path objFilePath;
    filesystem::path execFilePath;
    const vector<const char *> paths = {"../stdlib/lgslib.ll", "../stdlib/array.ll", "../stdlib/string.ll"};

    LgsLinker(const filesystem::path& objFilePath, const filesystem::path& execFilePath) : objFilePath(objFilePath), execFilePath(execFilePath) {}
    void link(const map<string, Module*>& modules) const;
    vector<const char*> getLinkerOpts() const;
    void linkStdlib(const string& path, Linker* linker) const;
    ~LgsLinker() = default;
};

#endif //LOGOSLINKER_H
