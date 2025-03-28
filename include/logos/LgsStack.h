#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "symbols/LgsSymbol.h"
#include <stack>
#include <map>
#include <llvm/IR/Module.h>

using namespace std;
using namespace llvm;

struct LgsStackFrame {
    map<string, LgsSymbol> symbols;
};

class LgsStack : stack<LgsStackFrame> {
public:
    mutex mtx;
    Function* currentFunc = nullptr;

    void enterScope();
    void exitScope(CodeGenMetadata* metadata = nullptr);
    LgsSymbol* getSymbol(const string& name);
    LgsFunc* getFunc(const vector<LgsFunc*>& overloads, const LgsFuncCall* funcCall) const;
    vector<LgsFunc*> getFuncOverloads(const LgsFuncCall* funcCall) const;
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    void addLocalSymbol(const string& name, LgsVarDec* symbol);
    void addLocalSymbol(const string& name, LgsParam* symbol);
    string getStackString() const;
    void reset();
    ~LgsStack() = default;
};

#endif //LOGOSSTACK_H
