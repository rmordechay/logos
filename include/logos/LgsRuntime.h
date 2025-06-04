#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "LgsStack.h"
#include "LgsSymbol.h"
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
    LLVMContext context;
    Module* module = nullptr;
    IRBuilder<> builder = IRBuilder(context);
    GlobalVariable* runtimeStruct = nullptr;

    void initRuntime();
    void pushStackTrace(const string& path);
    void printStack();
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
