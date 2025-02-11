#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "LogosSymbol.h"

#include <stack>

#include <map>

namespace llvm {
    class Function;
}

using namespace std;
using namespace llvm;

struct LogosStackFrame {
    Function* currentFunction = nullptr;
    map<string, LogosSymbol> symbols;

    explicit LogosStackFrame(Function* currentFunction) :
        currentFunction(currentFunction) {
    }
};

class LogosStack : public stack<LogosStackFrame> {
public:
    void enterScope(Function* func);
    void exitScope();
    LogosSymbol* getSymbol(const string& name);
    Function* getFunc(const string& name);
    void addLocalSymbol(const string& name, const LogosSymbol& symbol);
    void addGlobalSymbol(const string& name, const LogosSymbol& symbol);
    void addFunc(const string& name, Function* value);
    void setCurrentFunc(Function* value);
    ~LogosStack() = default;
private:
    map<string, LogosSymbol> globalSymbols;
};

inline void LogosStack::enterScope(Function* func) {
    push(LogosStackFrame(func));
}

inline void LogosStack::exitScope() {
    pop();
}

inline LogosSymbol* LogosStack::getSymbol(const string& name) {
    auto& symbols = top().symbols;

    if (symbols.contains(name)) {
        return &symbols[name];
    }
    if (globalSymbols.contains(name)) {
        return &globalSymbols[name];
    }
    return nullptr;
}

inline void LogosStack::addLocalSymbol(const string& name, const LogosSymbol& symbol) {
    top().symbols[name] = symbol;
}

inline void LogosStack::addGlobalSymbol(const string& name, const LogosSymbol& symbol) {
    globalSymbols[name] = symbol;
}

inline void LogosStack::setCurrentFunc(Function* value) {
    top().currentFunction = value;
}


#endif //LOGOSSTACK_H
