#include "LgsSymbolTable.h"
#include "data/LgsErrors.h"
#include "logos/LgsApp.h"
#include "utils/LgsErrHandler.h"
#include "types/LgsEnum.h"

void LgsSymbolTable::addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler, const std::string& filePath) {
    const auto symbolName = *symbol.name;
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
