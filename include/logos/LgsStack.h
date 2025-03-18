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
    map<string, LgsSymbol> globalSymbols;
    Function* currentFunc = nullptr;

    void enterScope();
    void exitScope();
    LgsSymbol* getSymbol(const string& name);
    bool hasSymbol(const string& name);
    void addGlobalSymbol(const string& name, const LgsSymbol& symbol);
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
