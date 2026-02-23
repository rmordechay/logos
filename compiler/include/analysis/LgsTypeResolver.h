#pragma once
#include <string>

#include "LgsSymbol.h"

class LgsMainFile;
class LgsIOPair;
class LgsFuncType;
class LgsIterable;
class LgsInterface;
class LgsObject;
class LgsFile;
class LgsType;
struct LgsSymbolTable;
class LgsErrHandler;

class LgsTypeResolver {
public:
    LgsFile* file;
    LgsSymbolTable& globals;
    LgsErrHandler& errHandler;
    LgsObject* currentObj = nullptr;
    LgsFuncType* currentFuncType = nullptr;

    LgsTypeResolver(LgsFile* file, LgsErrHandler& errHandler, LgsSymbolTable& globals) : file(file), globals(globals),errHandler(errHandler) {}
    void resolveType(LgsType*& type);
    void resolveMainFile(LgsMainFile* mf);
    void resolveObjTypes(LgsObject* obj);
    void resolveInterface(LgsInterface* interface);
    void resolveFuncType(LgsFuncType* funcType);
    LgsType* findSymbol(const std::string& typeName) const;
};
