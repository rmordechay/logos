#include "LogosStack.h"

void LogosStack::enterScope(Function* func) {
    currentFunc = func;
    push(LogosStackFrame());
}

void LogosStack::enterScope() {
    if (size() > 0) {
        push(LogosStackFrame{.symbols = top().symbols});
    } else {
        push(LogosStackFrame());
    }
}

void LogosStack::exitScope() {
    pop();
}

LogosSymbol* LogosStack::getSymbol(const string& name) {
    if (globalSymbols.find(name) != globalSymbols.end()) {
        return &globalSymbols[name];
    }
    auto& symbols = top().symbols;
    if (symbols.find(name) != symbols.end()) {
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
