#include "LgsSymbolTable.h"
#include "data/LgsErrors.h"
#include "exprs/unary/LgsEnumField.h"
#include "funcs/LgsParam.h"
#include "logos/LgsErrHandler.h"
#include "stmts/LgsField.h"
#include "types/LgsEnum.h"
#include "utils/LgsUtils.h"

void LgsSymbolTable::addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler) {
    if (symbols.find(name) != symbols.end()) {
        return errHandler->handleError(E10011, symbol.location, {name, symbol.location->lineNumberStr()});
    }
    std::lock_guard lock(mtx);
    symbols[name] = symbol;
}

void LgsSymbolTable::addSymbol(const string& name, const LgsSymbol& symbol) {
    if (symbols.find(name) != symbols.end()) return;
    std::lock_guard lock(mtx);
    symbols[name] = symbol;
}

LgsSymbol* LgsSymbolTable::getSymbol(const string& name) {
    if (symbols.find(name) != symbols.end()) {
        return &symbols[name];
    }
    return nullptr;
}

void LgsSymbolTable::addEnum(LgsEnum* lgsEnum, LgsErrHandler* errHandler) {
    if (symbols.find(lgsEnum->name) != symbols.end()) {
        const auto location = lgsEnum->location;
        errHandler->handleError(E10011, &location, {lgsEnum->name, location.lineNumberStr()});
        return;
    }
    lock_guard lock(mtx);
    symbols[lgsEnum->name] = LgsSymbol(lgsEnum);
    for (const auto& [name, field] : lgsEnum->fields) {
        symbols[name] = LgsSymbol(field->expr->asEnumField());
    }
}
