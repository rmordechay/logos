#pragma once
#include "LgsSymbol.h"
#include <unordered_map>
#include <vector>

class LgsImport;
class LgsFuncCall;
class LgsExpr;
class LgsStrConst;
class LgsApp;
class LgsErrHandler;

struct LgsSymbolTable {
    std::unordered_map<std::string, LgsSymbol> symbols;
    std::unordered_map<std::string, LgsFunc*> coroutines;
    std::unordered_map<std::string, LgsFunc*> genericsFuncs;
    std::unordered_map<std::string, LgsType*> rttTypes;
    std::unordered_map<std::string, LgsType*> genericsTypes;
    std::vector<LgsImport*> importPaths;

    LgsSymbol* getSymbol(const std::string& name);
    void addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler, const std::string& filePath = "");
};
