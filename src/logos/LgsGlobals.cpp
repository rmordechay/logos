#include "logos/LgsGlobals.h"

#include "exprs/unary/LgsEnumField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"

void LgsGlobals::addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler) {
    if (symbols.find(name) != symbols.end()) {
        const auto location = symbol.getLocation();
        errHandler->handleError(E10011, location, {name, location->lineNumberStr()});
        return;
    }
    std::lock_guard lock(mtx);
    symbols[name] = symbol;
}

void LgsGlobals::addEnum(LgsEnum* lgsEnum, LgsErrHandler* errHandler) {
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

LgsGlobals::~LgsGlobals() {
    for (const auto& [_, symbol] : symbols) {
        switch (symbol.type) {
        case VAR_DEC: delete symbol.varDec; break;
        case PARAM: delete symbol.param; break;
        case OBJECT: delete symbol.object; break;
        case INTERFACE: delete symbol.interface; break;
        case FUNC: assert(false);
        case ENUM: delete symbol.lgsEnum; break;
        case ENUM_FIELD: delete symbol.enumField; break;
        default: break;
        }
    }
}
