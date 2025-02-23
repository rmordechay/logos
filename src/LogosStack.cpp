#include "LogosStack.h"

void LogosStack::enterScope(Function* func) {
    currentFunc = func;
    push(LogosStackFrame());
}

void LogosStack::enterScope() {
    push(LogosStackFrame());
}

void LogosStack::exitScope() {
    pop();
}

LogosSymbol* LogosStack::getSymbol(const string& name) {
    if (globalSymbols.contains(name)) {
        return &globalSymbols[name];
    }
    auto& symbols = top().symbols;
    if (symbols.contains(name)) {
        return &symbols[name];
    }
    return nullptr;
}

void LogosStack::addLocalSymbol(const string& name, const LogosSymbol& symbol) {
    top().symbols[name] = symbol;
}

void LogosStack::addGlobalSymbol(const string& name, const LogosSymbol& symbol) {
    globalSymbols[name] = symbol;
}

void LogosStack::deleteGlobalSymbol(const string& name) {
    globalSymbols.erase(name);
}

void LogosStack::reset() {
    while (size() > 0) {
        pop();
    }
}
