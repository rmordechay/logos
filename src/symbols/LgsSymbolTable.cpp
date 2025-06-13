#include "LgsSymbolTable.h"
#include "data/LgsErrors.h"
#include "funcs/LgsParam.h"
#include "logos/LgsErrHandler.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

void LgsSymbolTable::addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler) {
    if (symbols.find(name) != symbols.end()) {
        errHandler->handleError(E10011, symbol.location, {name, symbol.location->lineNumberStr()});
        return;
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
        symbols[name] = LgsSymbol(dynamic_cast<LgsEnumField*>(field));
    }
}

LgsSymbolTable::~LgsSymbolTable() {
    for (const auto& [_, symbol] : symbols) {
        switch (symbol.symbolType) {
        case VAR_DEC: delete symbol.varDec; break;
        case PARAM: delete symbol.param; break;
        case OBJECT: delete symbol.object; break;
        case INTERFACE: delete symbol.interface; break;
        case ENUM: delete symbol.lgsEnum; break;
        case ENUM_FIELD: delete symbol.enumField; break;
        case FUNC: break;
        case GROUP: break;
        case FIELD: break;
        case UNKNOWN: break;
        }
    }
}

