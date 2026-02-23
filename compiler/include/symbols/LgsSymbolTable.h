#pragma once
#include <unordered_map>
#include <vector>
#include <string>

#include "LgsSymbol.h"
#include "stmts/LgsImport.h"

class LgsFuncCall;
class LgsExpr;
class LgsStrConst;
class LgsApp;
class LgsErrHandler;
class LgsFunc;
class LgsType;

struct LgsSymbolTable {
    std::unordered_map<std::string, LgsSymbol> symbols;
    std::unordered_map<std::string, LgsFunc*> coroutines;
    std::unordered_map<std::string, LgsFunc*> genericsFuncs;
    std::unordered_map<std::string, LgsType*> genericsTypes;
    std::unordered_map<std::string, LgsType*> rttTypes;
    std::vector<LgsImport> importPaths;

    LgsSymbol* getSymbol(const std::string& name);
    void addSymbol(const LgsSymbol& symbol, LgsErrHandler* errHandler, const std::string& filePath = "");
};
