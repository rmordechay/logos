#pragma once
#include "LgsSymbol.h"
#include <map>

class LgsApp;
class LgsErrHandler;

struct LgsSymbolTable {
   std::map<std::string, LgsSymbol> symbols;

    LgsSymbol* getSymbol(const std::string& name);
    void addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler, const std::string& filePath = "");
};

struct LgsGlobals {
    LgsSymbolTable symbolTable;
    std::map<std::string, LgsApp*> imports;
};