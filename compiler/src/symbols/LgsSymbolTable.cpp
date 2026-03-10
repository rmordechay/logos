#include "LgsSymbolTable.h"

#include <assert.h>

#include "errors/LgsErrors.h"
#include "errors/LgsErrHandler.h"


void LgsSymbolTable::addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler, const std::string& filePath) {
    const auto symbolName = *symbol.name;
    assert(symbolName != "");
    if (symbols.contains(symbolName)) {
        return errHandler->addError(E10011, symbol.location, filePath, {symbolName});
    }
    symbols[symbolName] = symbol;
}

LgsSymbol* LgsSymbolTable::getSymbol(const std::string& name) {
    if (symbols.contains(name)) {
        return &symbols[name];
    }
    return nullptr;
}
