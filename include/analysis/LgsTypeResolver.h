#pragma once

class LgsGroup;
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
    LgsErrHandler& errHandler;
    LgsSymbolTable& globals;

    LgsTypeResolver(LgsErrHandler& errHandler, LgsSymbolTable& globals) : errHandler(errHandler), globals(globals) {}
    bool resolveGlobalTypes(const std::vector<LgsFile*>& ast);
    LgsType* resolveType(LgsType* type, LgsFile* file);
    void resolveObjTypes(LgsObject* obj, LgsFile& file);
    void resolveInterfaceTypes(LgsInterface* interface, LgsFile& file);
    void resolveIterable(LgsIterable* iterable, LgsFile& file);
    void resolveFuncTypes(LgsFuncType* funcType, LgsFile& file);
    void resolveGroupTypes(LgsGroup* group, LgsFile& file);
};
