#ifndef LOGOSLINKER_H
#define LOGOSLINKER_H
#include <map>
#include <llvm/IR/Module.h>

using namespace llvm;
using namespace std;

class LgsLinker {
public:
    static void link(const map<string, Module*>& modules);
    static vector<const char*> getLinkerOpts();
    static void writeExecFile(const unique_ptr<Module>& module);
    ~LgsLinker() = default;
};

#endif //LOGOSLINKER_H
