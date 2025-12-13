#pragma once


class LgsMainFile;
struct LgsGlobals;
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
    LgsGlobals& globals;
    LgsErrHandler& errHandler;

    LgsTypeResolver(LgsFile* file, LgsErrHandler& errHandler, LgsGlobals& globals) : file(file), globals(globals),errHandler(errHandler) {}
    void resolveType(LgsType*& type);
    void resolveMainFile(LgsMainFile* mf);
    void resolveObj(LgsObject* obj);
    void resolveInterface(LgsInterface* interface);
    void resolveFuncType(LgsFuncType* funcType);
    void resolveIOPair(LgsIOPair* ioPair, LgsObject* obj) const;
};
