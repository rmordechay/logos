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

inline mutex mtx;

struct LgsGlobals {
    map<string, LgsSymbol> symbols;
    map<string, vector<LgsFunc*>> funcs;

    void addSymbol(const string& name, const LgsSymbol symbol) {
        lock_guard lock(mtx);
        if (symbols.find(name) != symbols.end()) {
            assert(false && "element already exists");
        }
        symbols[name] = symbol;
    }
};

inline LgsGlobals globals;

class LgsStack : stack<LgsStackFrame> {
public:
    Function* currentFunc = nullptr;

    void enterScope();
    void exitScope();
    LgsSymbol* getSymbol(const string& name);
    LgsFunc* getFunc(const LgsFuncCall* funcCall) const;
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    void addLocalSymbol(const string& name, LgsObject* symbol);
    void addLocalSymbol(const string& name, LgsVarDec* symbol);
    void addLocalSymbol(const string& name, LgsParam* symbol);
    void addLocalSymbol(const string& name, LgsFunc* symbol);
    string getStackString() const;
    void reset();
    ~LgsStack() = default;
};

#endif //LOGOSSTACK_H
