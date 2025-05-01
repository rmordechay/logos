#ifndef LGSGLOBALS_H
#define LGSGLOBALS_H
#include "funcs/LgsFunc.h"
#include "funcs/LgsParam.h"
#include "types/LgsEnum.h"
#include "exprs/unary/LgsEnumField.h"
#include "stmts/LgsVarDec.h"
#include "symbols/LgsSymbol.h"
#include "types/LgsObject.h"
#include "types/LgsInterface.h"
#include "LgsErrorHandler.h"

struct LgsGlobals {
    std::mutex mtx;
    map<string, LgsSymbol> symbols;

    void addSymbol(const string& name, const LgsSymbol& symbol, LgsErrorHandler* errHandler) {
        if (symbols.find(name) != symbols.end()) {
            const auto location = symbol.getLocation();
            errHandler->handleError(E10011, location, {name, location->lineNumberStr()});
            return;
        }
        lock_guard lock(mtx);
        symbols[name] = symbol;
        return;
    }

    void addFunc(LgsFunc* func) {
        std::lock_guard lock(mtx);
        auto [symbol, inserted] = symbols.try_emplace(func->signature.name);
        if (inserted) {
            symbol->second.type = FUNC;
        }
        symbol->second.func.emplace_back(func);
    }

    void addEnum(LgsEnum* lgsEnum) {
        if (symbols.find(lgsEnum->name) != symbols.end()) {
            // TODO replace with proper error
            assert(false && "enum already exists");
        }
        lock_guard lock(mtx);
        symbols[lgsEnum->name] = LgsSymbol(lgsEnum);
        for (const auto& [name, field] : lgsEnum->fields) {
            symbols[name] = LgsSymbol(dynamic_cast<LgsEnumField*>(field));
        }
    }

    ~LgsGlobals() {
        for (const auto& [_, symbol] : symbols) {
            switch (symbol.type) {
            case VAR_DEC: delete symbol.varDec; break;
            case PARAM: delete symbol.param; break;
            case OBJECT: delete symbol.object; break;
            case INTERFACE: delete symbol.interface; break;
            case FUNC: {
                for (const auto& overload : symbol.func) {
                    delete overload;
                }
                break;
            }
            case ENUM: delete symbol.lgsEnum; break;
            case ENUM_FIELD: delete symbol.enumField; break;
            default: break;
            }
        }
    }
};

inline LgsGlobals globals;

// TODO Put somewhere else
inline LgsType* resolveType(LgsType* type, LgsErrorHandler* errorHandler) {
    if (!dynamic_cast<LgsUnknownType*>(type)) return type;
    auto typeName = type->getName();
    const auto nullable = type->nullable;
    if (globals.symbols.find(typeName) == globals.symbols.end()) {
        errorHandler->handleError(E10006, &type->location, {typeName});
        return nullptr;
    }
    const auto symbol = &globals.symbols[typeName];
    delete type;
    LgsType* newType = nullptr;
    if (symbol->type == OBJECT) {
        symbol->object->nullable = nullable;
        newType = symbol->object;
    }
    if (symbol->type == INTERFACE) {
        symbol->interface->nullable = nullable;
        newType = symbol->interface;
    }
    if (symbol->type == ENUM) {
        symbol->lgsEnum->nullable = nullable;
        newType = symbol->lgsEnum;
    }
    if (symbol->type == ENUM_FIELD) {
        symbol->enumField->parent->nullable = nullable;
        newType = symbol->enumField->parent;
    }
    assert(newType);
    return newType;
}

#endif //LGSGLOBALS_H
