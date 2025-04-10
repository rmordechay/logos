#include "LgsStack.h"

#include "LgsGlobals.h"
#include "exprs/unary/LgsFuncCall.h"
#include "funcs/LgsFunc.h"

#include <llvm/Support/CommandLine.h>

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

void LgsStack::exitScope() {
    pop();
}

LgsSymbol* LgsStack::getSymbol(const string& name) {
    // Globals symbols
    if (globals.symbols.find(name) != globals.symbols.end()) {
        return &globals.symbols[name];
    }
    if (size() == 0) return nullptr;
    // Locals
    auto& symbols = top().symbols;
    if (symbols.find(name) != symbols.end()) {
        return &symbols[name];
    }
    return nullptr;
}

void LgsStack::addLocalSymbol(const string& name, const LgsSymbol& symbol) {
    assert(size() > 0 && "stack has no frames");
    top().symbols[name] = symbol;
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

