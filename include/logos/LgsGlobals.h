#ifndef LGSGLOBALS_H
#define LGSGLOBALS_H
#include "symbols/LgsSymbol.h"
#include "LgsErrHandler.h"
#include "LgsRuntime.h"
#include <mutex>

struct LgsGlobals {
    std::mutex mtx;
    map<string, LgsSymbol> symbols;

    void addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler);
    void addEnum(LgsEnum* lgsEnum, LgsErrHandler* errHandler = nullptr);
    ~LgsGlobals();
};

inline LgsGlobals globals;
inline LgsRuntime runtime;

#endif //LGSGLOBALS_H
