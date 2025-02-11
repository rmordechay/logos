#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "LogosSymbol.h"

#include <stack>
#include <map>
#include "types/LogosInt.h"

using namespace std;

struct LogosStackFrame {
    Function* currentFunction = nullptr;
    map<string, LogosSymbol> symbols;

    explicit LogosStackFrame(Function* currentFunction) :
        currentFunction(currentFunction) {
    }
};

class LogosStack : public stack<LogosStackFrame> {
public:
    map<string, LogosSymbol> globalSymbols;

    void enterScope(Function* func);
    void exitScope();
    LogosSymbol* getSymbol(const string& name);
    Function* getFunc(const string& name);
    void addSymbol(const string& name, const LogosSymbol& symbol);
    void addGlobalSymbol(const string& name, const LogosSymbol& symbol);
    void addFunc(const string& name, Function* value);
    void setCurrentFunc(Function* value);
    ~LogosStack() = default;
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

inline void LogosStack::addSymbol(const string& name, const LogosSymbol& symbol) {
    top().symbols[name] = symbol;
}

inline void LogosStack::addGlobalSymbol(const string& name, const LogosSymbol& symbol) {
    globalSymbols[name] = symbol;
}

inline void LogosStack::setCurrentFunc(Function* value) {
    top().currentFunction = value;
}


#endif //LOGOSSTACK_H
