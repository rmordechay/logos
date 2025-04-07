#include "LgsStack.h"

#include "LgsGlobals.h"
#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"

void LgsStack::enterScope(LgsFunc* func) {
    if (func) {
        currentFunc = func;
    }
    if (size() > 0) {
        push(LgsStackFrame{.symbols = top().symbols});
    } else {
        push(LgsStackFrame());
    }
}

void LgsStack::exitScope(CodeGenMetadata* metadata) {
    // if (metadata) freeSymbols(metadata);
    pop();
}

LgsSymbol* LgsStack::getSymbol(const string& name) {
    // Globals symbols
    if (globals.symbols.find(name) != globals.symbols.end()) {
        return &globals.symbols[name];
    }
    // Globals enums
    for (auto& [_, enumSymbol] : globals.enums) {
        if (enumSymbol.lgsEnum->name == name) return &enumSymbol;
        for (auto [_, field] : enumSymbol.lgsEnum->fields) {
            if (name != field->name) continue;
            return &enumSymbol;
        }
    }
    if (size() == 0) return nullptr;
    // Locals
    auto& symbols = top().symbols;
    if (symbols.find(name) != symbols.end()) {
        return &symbols[name];
    }
    return nullptr;
}

LgsFunc* LgsStack::getFunc(const vector<LgsFunc*>& overloads, const string& composedName) const {
    for (const auto& overload : overloads) {
        if (overload->signature.composedName == composedName) {
            return overload;
        }
    }
    return nullptr;
}

vector<LgsFunc*> LgsStack::getFuncOverloads(const string& funcName) const {
    const auto func = globals.funcs.find(funcName);
    if (func != globals.funcs.end()) {
        return func->second;
    }
    return {};
}

void LgsStack::addLocalSymbol(const string& name, const LgsSymbol& symbol) {
    assert(size() > 0 && "stack has no frames");
    top().symbols[name] = symbol;
}

void LgsStack::addLocalSymbol(const string& name, LgsVarDec* symbol) {
    addLocalSymbol(name, LgsSymbol(symbol));
}

void LgsStack::addLocalSymbol(const string& name, LgsParam* symbol) {
    addLocalSymbol(name, LgsSymbol(symbol));
}

string LgsStack::getStackString() const {
    return "";
}

void LgsStack::freeSymbols(CodeGenMetadata* metadata) {
    for (const auto& [_, symbol] : top().symbols) {
        symbol.free(metadata);
    }
}

void LgsStack::reset() {
    while (size() > 0) {
        pop();
    }
}

