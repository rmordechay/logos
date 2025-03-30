#ifndef LGSGLOBALS_H
#define LGSGLOBALS_H
#include "funcs/LgsFunc.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsEnum.h"
#include "stmts/LgsVarDec.h"
#include "symbols/LgsSymbol.h"
#include "types/LgsObject.h"

#include <assert.h>

struct LgsGlobals {
    mutex mtx;
    map<string, LgsSymbol> symbols;
    map<string, vector<LgsFunc*>> funcs;

    void addSymbol(const string& name, const LgsSymbol symbol) {
        lock_guard lock(mtx);
        if (symbols.find(name) != symbols.end()) {
            assert(false && "element already exists");
        }
        symbols[name] = symbol;
    }

    void addFunc(LgsFunc* func) {
        lock_guard lock(mtx);
        funcs[func->signature.name].emplace_back(func);
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
                case FUNC: delete symbol.func; break;
                case ENUM: delete symbol.lgsEnum; break;
            }
        }
    }
};

inline LgsGlobals globals;

#endif //LGSGLOBALS_H
