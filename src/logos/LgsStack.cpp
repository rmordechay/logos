#include "LgsStack.h"

#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"

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
    // Locals
    auto& symbols = top().symbols;
    if (symbols.find(name) != symbols.end()) {
        return &symbols[name];
    }
    // Globals
    if (globals->symbols.find(name) != globals->symbols.end()) {
        return &globals->symbols[name];
    }
    return nullptr;
}

LgsFunc* LgsStack::getFunc(const LgsFuncCall* funcCall) const {
    const auto func = globals->funcs.find(funcCall->name);
    if (func != globals->funcs.end()) {
        for (const auto& overload : func->second) {
            if (overload->composedName == funcCall->composedName) {
                return overload;
            }
        }
    }
    return nullptr;
}

void LgsStack::addGlobalSymbol(const string& name, const LgsSymbol& symbol) {

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