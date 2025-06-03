#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "LgsStack.h"
#include "LgsSymbol.h"
#include "codegen/CodegenMetadata.h"
#include <map>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

using namespace std;
using namespace llvm;
class LgsErrHandler;
class LgsForLoop;
class LgsFuncType;

class LgsRuntime {
public:
    LgsStack stack;
    Module* module = nullptr;
    IRBuilder<> builder = IRBuilder(context);
    GlobalVariable* runtimeStruct = nullptr;

    void initRuntime(LgsRuntime* runtime);
    void pushStackTrace(LgsRuntime* runtime, const string& path) const;
    void printStack(LgsRuntime* runtime) const;
    void addAllocatedExpr(LgsExpr* expr);
    void freeExprs(LgsRuntime* runtime);
    ~LgsRuntime() = default;
};

struct LgsGlobals {
    map<string, LgsSymbol> symbols;

    void addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler);
    void addEnum(LgsEnum* lgsEnum, LgsErrHandler* errHandler = nullptr);
    ~LgsGlobals();
};

inline LgsGlobals globals;

#endif //LOGOSSTACK_H
