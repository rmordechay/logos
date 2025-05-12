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
#include "LgsErrHandler.h"
#include "funcs/LgsFuncImpl.h"
#include <mutex>

struct LgsGlobals {
    std::mutex mtx;
    map<string, LgsSymbol> symbols;

    void addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler) {
        if (symbols.find(name) != symbols.end()) {
            const auto location = symbol.getLocation();
            errHandler->handleError(E10011, location, {name, location->lineNumberStr()});
            return;
        }
        lock_guard lock(mtx);
        symbols[name] = symbol;
    }

    void addFunc(LgsFuncImpl* newFunc) {
        const auto name = newFunc->funcType.name;
        const auto symbol = symbols.find(name);
        std::lock_guard lock(mtx);
        if (symbol == symbols.end()) {
            const auto funcFamily = new LgsFuncSymbol();
            funcFamily->overloads.push_back(newFunc);
            symbols[name] = LgsSymbol(funcFamily);
        } else {
            symbol->second.func->overloads.emplace_back(newFunc);
        }
    }

    void addEnum(LgsEnum* lgsEnum, LgsErrHandler* errHandler = nullptr) {
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

    ~LgsGlobals() {
        for (const auto& [_, symbol] : symbols) {
            switch (symbol.type) {
            case VAR_DEC: delete symbol.varDec; break;
            case PARAM: delete symbol.param; break;
            case OBJECT: delete symbol.object; break;
            case INTERFACE: delete symbol.interface; break;
            case FUNC: {
                // TODO free global funcs that are not builtin
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

#endif //LGSGLOBALS_H
