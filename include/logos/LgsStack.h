#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "symbols/LgsSymbol.h"
#include <stack>
#include <map>
#include <llvm/IR/Module.h>

using namespace std;
using namespace llvm;
struct LgsFuncSignature;

struct LgsStackFrame {
    map<string, LgsSymbol> symbols;
};

class LgsStack : stack<LgsStackFrame> {
public:
    mutex mtx;
    LgsFunc* currentFunc = nullptr;

    void enterScope(LgsFunc* func = nullptr);
    void exitScope(CodeGenMetadata* metadata = nullptr);
    LgsSymbol* getSymbol(const string& name);
    LgsFunc* getFunc(const vector<LgsFunc*>& overloads, const LgsFuncSignature* signature) const;
    vector<LgsFunc*> getFuncOverloads(const string& funcName) const;
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    void addLocalSymbol(const string& name, LgsVarDec* symbol);
    void addLocalSymbol(const string& name, LgsParam* symbol);
    string getStackString() const;
    void freeSymbols(CodeGenMetadata* metadata);
    void reset();
    ~LgsStack() = default;
};

#endif //LOGOSSTACK_H
