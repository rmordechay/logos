#include "LgsSymbolTable.h"
#include "data/LgsErrors.h"
#include "funcs/LgsParam.h"
#include "utils/LgsErrHandler.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsEnum.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

void LgsSymbolTable::addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler) {
    if (symbols.find(name) != symbols.end()) {
        return errHandler->handleError(E10011, symbol.location, {name, symbol.location->lineNumberStr()});
    }
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
    // for (const auto& [name, field] : lgsEnum->fields) {
    //     symbols[name] = LgsSymbol(field);
    // }
}

void LgsSymbolTable::freeSymbols() {
    for (const auto symbol : symbols) {
        switch (symbol.second.symbolType) {
        case VAR_DEC:
            delete symbol.second.varDec;
            break;
        case PARAM:
            delete symbol.second.param;
            break;
        case FIELD:
            delete symbol.second.field;
            break;
        case FUNC:
            delete symbol.second.func;
            break;
        case OBJECT:
            delete symbol.second.object;
            break;
        case INTERFACE:
            delete symbol.second.interface;
            break;
        case GROUP:
            delete symbol.second.group;
            break;
        case ENUM:
            delete symbol.second.lgsEnum;
            break;
        case UNKNOWN:
            break;
        }
    }
    symbols.clear();
}
