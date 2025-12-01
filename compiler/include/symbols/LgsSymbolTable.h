#pragma once
#include "LgsSymbol.h"
#include <unordered_map>
#include <unordered_set>

class LgsStrConst;
class LgsApp;
class LgsErrHandler;

struct LgsSymbolTable {
    std::unordered_map<std::string, LgsSymbol> symbols;
    std::unordered_map<std::string, LgsApp*> imports;
    std::unordered_map<std::string, LgsFunc*> coroutines;
    std::unordered_map<std::string, LgsFunc*> genericFuncCalls;
    std::unordered_set<std::string> cImportPaths;
    std::vector<LgsType*> rttTypes;

    LgsSymbol* getSymbol(const std::string& name);
    void addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler, const std::string& filePath = "");
};

struct LgsGlobals {
    LgsSymbolTable table;
    std::map<std::string, LgsSymbolTable> cImports;
};
