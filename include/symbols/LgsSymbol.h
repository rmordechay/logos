#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H
#include <json/json.hpp>
#include <llvm/IR/Value.h>

class LgsGroup;
using namespace nlohmann;

class LgsField;
struct CodegenMetadata;
class LgsEnum;
class LgsEnumField;
class LgsFunc;
class LgsInterface;
class LgsObject;
class LgsParam;
class LgsVarDec;
class Location;

enum LgsSymbolType {
    VAR_DEC,
    PARAM,
    ENUM_FIELD,
    FIELD,
    FUNC,
    OBJECT,
    INTERFACE,
    GROUP,
    ENUM,
    UNKNOWN,
};

struct LgsSymbol {
    LgsSymbolType type;
    LgsVarDec* varDec = nullptr;
    LgsParam* param = nullptr;
    LgsObject* object = nullptr;
    LgsInterface* interface = nullptr;
    LgsField* field = nullptr;
    LgsEnum* lgsEnum = nullptr;
    LgsEnumField* enumField = nullptr;
    LgsFunc* func = nullptr;
    LgsGroup* group = nullptr;

    explicit LgsSymbol(): type(UNKNOWN) {}
    explicit LgsSymbol(LgsParam* param);
    explicit LgsSymbol(LgsVarDec* varDec);
    explicit LgsSymbol(LgsObject* object);
    explicit LgsSymbol(LgsInterface* interface);
    explicit LgsSymbol(LgsField* field);
    explicit LgsSymbol(LgsEnum* lgsEnum);
    explicit LgsSymbol(LgsEnumField* enumField);
    explicit LgsSymbol(LgsFunc* func);
    explicit LgsSymbol(LgsGroup* group);
    LgsSymbol* clone() const;
    Location* getLocation() const;
    void* getPtr() const;
    json asJSON() const;
    ~LgsSymbol() = default;
};

#endif //LOGOSSYMBOL_H
