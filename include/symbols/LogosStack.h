#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "LogosSymbol.h"

#include <stack>

#include <map>

namespace llvm {
    class Module;
    class Function;
}

using namespace std;
using namespace llvm;

struct LogosStackFrame {
    Function* llvmFunc = nullptr;
    map<string, LogosSymbol> symbols;

    LogosStackFrame() = default;
    explicit LogosStackFrame(Function* llvmFunc) : llvmFunc(llvmFunc) {}
};

class LogosStack : public stack<LogosStackFrame> {
public:
    map<string, Module*> modules;

    void enterScope(Function* func);
    void enterScope();
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

inline void LogosStack::enterScope() {
    push(LogosStackFrame());
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
    top().llvmFunc = value;
}


#endif //LOGOSSTACK_H
