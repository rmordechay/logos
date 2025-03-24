#ifndef LGSGLOBALS_H
#define LGSGLOBALS_H
#include "symbols/LgsSymbol.h"
#include <stack>
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
};

inline LgsGlobals globals;

#endif //LGSGLOBALS_H
