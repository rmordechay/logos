#pragma once
#include "LgsSymbol.h"
#include <map>
#include <vector>
#include <unordered_map>

class LgsStrConst;
class LgsApp;
class LgsErrHandler;

struct LgsSymbolTable {
    std::unordered_map<std::string, LgsSymbol> symbols;
    std::unordered_map<std::string, LgsApp*> imports;
    std::vector<LgsType*> rtTypes;

    LgsSymbol* getSymbol(const std::string& name);
    void addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler, const std::string& filePath = "");
};

struct LgsGlobals {
    LgsSymbolTable* symbolTable;
    std::vector<LgsStrConst*> cImports;
    std::vector<LgsType*> rtTypesRegistry;

    LgsSymbol* getSymbol(const std::string& name);
    void addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler, const std::string& filePath = "");
};
