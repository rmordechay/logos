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

void LgsSymbolTable::addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler) {
    const auto symbolName = *symbol.name;
    if (symbols.find(symbolName) != symbols.end()) {
        return errHandler->addError(E10011, symbol.location, {symbolName});
    }
    symbols[symbolName] = symbol;
}

LgsSymbol* LgsSymbolTable::getSymbol(const std::string& name) {
    if (symbols.find(name) != symbols.end()) {
        return &symbols[name];
    }
    return nullptr;
}

void LgsSymbolTable::freeSymbols() {
    for (const auto [_, symbol] : symbols) {
        switch (symbol.symbolType) {
        case VAR_DEC:
            delete symbol.varDec;
            break;
        case PARAM:
            delete symbol.param;
            break;
        case FIELD:
            delete symbol.field;
            break;
        case FUNC:
            delete symbol.func;
            break;
        case OBJECT:
            freeType(symbol.object);
            break;
        case INTERFACE:
            freeType(symbol.interface);
            break;
        case GROUP:
            freeType(symbol.group);
            break;
        case ENUM:
            freeType(symbol.lgsEnum);
            break;
        case SUBTYPE:
            freeType(symbol.subtype);
            break;
        case UNKNOWN:
            break;
        }
    }
    symbols.clear();
}
