#include "LgsStack.h"

void LgsStack::enterScope() {
    if (size() > 0) {
        push(LgsStackFrame{.symbols = top().symbols});
    } else {
        push(LgsStackFrame());
    }
}

void LgsStack::exitScope() {
    pop();
}

LgsSymbol* LgsStack::getSymbol(const string& name) {
    if (globalSymbols.find(name) != globalSymbols.end()) {
        return &globalSymbols[name];
    }
    auto& symbols = top().symbols;
    if (symbols.find(name) != symbols.end()) {
        return &symbols[name];
    }
    return nullptr;
}

bool LgsStack::hasSymbol(const string& name) {
    if (globalSymbols.find(name) != globalSymbols.end()) return true;
    auto& symbols = this->top().symbols;
    return symbols.find(name) != symbols.end();
}

void LgsStack::addGlobalSymbol(const string& name, const LgsSymbol& symbol) {
    globalSymbols[name] = symbol;
}

void LgsStack::addLocalSymbol(const string& name, const LgsSymbol& symbol) {
    assert(size() > 0 && "stack has no frames");
    top().symbols[name] = symbol;
}

void LgsStack::addLocalSymbol(const string& name, LgsObject* symbol) {
    addLocalSymbol(name, LgsSymbol(OBJECT, symbol));
}

void LgsStack::addLocalSymbol(const string& name, LgsVarDec* symbol) {
    addLocalSymbol(name, LgsSymbol(VAR_DEC, symbol));
}

void LgsStack::addLocalSymbol(const string& name, LgsParam* symbol) {
    addLocalSymbol(name, LgsSymbol(PARAM, symbol));
}

void LgsStack::addLocalSymbol(const string& name, LgsFunc* symbol) {
    addLocalSymbol(name, LgsSymbol(FUNC, symbol));
}

string LgsStack::getStackString() const {
    return "";
}

void LgsStack::reset() {
    while (size() > 0) {
        pop();
    }
}