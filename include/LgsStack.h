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
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    void addGlobalSymbol(const string& name, const LgsSymbol& symbol);
    void deleteGlobalSymbol(const string& name);
    string getStackString();
    void reset();
    ~LgsStack() = default;
};

inline void LgsStack::enterScope() {
    if (size() > 0) {
        push(LgsStackFrame{.symbols = top().symbols});
    } else {
        push(LgsStackFrame());
    }
}

inline void LgsStack::exitScope() {
    pop();
}

inline LgsSymbol* LgsStack::getSymbol(const string& name) {
    if (globalSymbols.find(name) != globalSymbols.end()) {
        return &globalSymbols[name];
    }
    auto& symbols = top().symbols;
    if (symbols.find(name) != symbols.end()) {
        return &symbols[name];
    }
    return nullptr;
}

inline void LgsStack::addLocalSymbol(const string& name, const LgsSymbol& symbol) {
    top().symbols[name] = symbol;
}

inline void LgsStack::addGlobalSymbol(const string& name, const LgsSymbol& symbol) {
    globalSymbols[name] = symbol;
}

inline void LgsStack::deleteGlobalSymbol(const string& name) {
    globalSymbols.erase(name);
}

inline string LgsStack::getStackString() {
    return "";
}

inline void LgsStack::reset() {
    while (size() > 0) {
        pop();
    }
}

#endif //LOGOSSTACK_H
