#pragma once
#include "files/LgsMainFile.h"
#include "utils/ThreadPool.h"

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
    LgsSymbolTable& globals;
    LgsErrHandler& errHandler;
    std::vector<LgsType*> rtTypesRegistry;

    LgsTypeResolver(LgsErrHandler& errHandler, LgsSymbolTable& globals) : globals(globals), errHandler(errHandler) {}
    bool resolveGlobals(const std::vector<LgsFile*>& srcFiles, ThreadPool& pool);
    LgsType* resolveType(LgsType* type, LgsFile* file);
    void resolveMainFileTypes(LgsMainFile* mf);
    void resolveObjTypes(LgsObject* obj, LgsFile& file);
    void resolveInterfaceTypes(LgsInterface* interface, LgsFile& file);
    void resolveFuncTypes(LgsFuncType* funcType, LgsFile& file);
    void resolveIOPair(LgsIOPair* ioPair, LgsObject* obj, LgsFile& file) const;
};
