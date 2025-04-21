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

struct LgsGlobals {
    std::mutex mtx;
    // TODO make symbols and enums map for faster retrieval
    map<string, LgsSymbol> symbols;
    map<string, LgsSymbol> enums;
    map<string, vector<LgsFunc*>> funcs;

    void addSymbol(const string& name, const LgsSymbol& symbol) {
        if (symbols.find(name) != symbols.end()) {
            // TODO replace with proper error
            assert(false && "element already exists");
        }
        lock_guard lock(mtx);
        symbols[name] = symbol;
    }

    void addFunc(LgsFunc* func) {
        lock_guard lock(mtx);
        funcs[func->signature.name].emplace_back(func);
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
        for (const auto& [_, func] : funcs) {
            for (const auto& overload : func) {
                delete overload;
            }
        }
        for (const auto& [_, symbol] : symbols) {
            switch (symbol.type) {
            case VAR_DEC: delete symbol.varDec; break;
            case PARAM: delete symbol.param; break;
            case OBJECT: delete symbol.object; break;
            case INTERFACE: delete symbol.interface; break;
            case FUNC: delete symbol.func; break;
            case ENUM: delete symbol.lgsEnum; break;
            case ENUM_FIELD: delete symbol.enumField; break;
            default: break;
            }
        }
    }
};

inline LgsGlobals globals;

#endif //LGSGLOBALS_H
