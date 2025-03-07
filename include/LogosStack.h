#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "symbols/LogosSymbol.h"
#include <stack>
#include <map>
#include <llvm/IR/Module.h>

using namespace std;
using namespace llvm;

struct LogosStackFrame {
    map<string, LogosSymbol> symbols;
};

class LogosStack : stack<LogosStackFrame> {
public:
    map<string, LogosSymbol> globalSymbols;
    Function* currentFunc = nullptr;

    void enterScope();
    void exitScope();
    LogosSymbol* getSymbol(const string& name);
    void addLocalSymbol(const string& name, const LogosSymbol& symbol);
    void addGlobalSymbol(const string& name, const LogosSymbol& symbol);
    void deleteGlobalSymbol(const string& name);
    void reset();
    ~LogosStack() = default;
};

inline void LogosStack::enterScope() {
    if (size() > 0) {
        push(LogosStackFrame{.symbols = top().symbols});
    } else {
        push(LogosStackFrame());
    }
}

inline void LogosStack::exitScope() {
    pop();
}

inline LogosSymbol* LogosStack::getSymbol(const string& name) {
    if (globalSymbols.find(name) != globalSymbols.end()) {
        return &globalSymbols[name];
    }
    auto& symbols = top().symbols;
    if (symbols.find(name) != symbols.end()) {
        return &symbols[name];
    }
    return nullptr;
}

inline void LogosStack::addLocalSymbol(const string& name, const LogosSymbol& symbol) {
    top().symbols[name] = symbol;
}

inline void LogosStack::addGlobalSymbol(const string& name, const LogosSymbol& symbol) {
    globalSymbols[name] = symbol;
}

inline void LogosStack::deleteGlobalSymbol(const string& name) {
    globalSymbols.erase(name);
}

inline void LogosStack::reset() {
    while (size() > 0) {
        pop();
    }
}

#endif //LOGOSSTACK_H
