#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H
#include <json/json.hpp>
#include <llvm/IR/Value.h>

using namespace nlohmann;

class LgsField;
struct CodeGenMetadata;
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
    OBJECT,
    INTERFACE,
    FIELD,
    FUNC,
    ENUM,
    ENUM_FIELD,
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

    explicit LgsSymbol(): type(UNKNOWN) {}
    explicit LgsSymbol(LgsParam* param);
    explicit LgsSymbol(LgsVarDec* varDec);
    explicit LgsSymbol(LgsObject* object);
    explicit LgsSymbol(LgsInterface* interface);
    explicit LgsSymbol(LgsField* field);
    explicit LgsSymbol(LgsEnum* lgsEnum);
    explicit LgsSymbol(LgsEnumField* enumField);
    explicit LgsSymbol(LgsFunc* func);
    LgsSymbol* clone() const;
    Location* getLocation() const;
    json asJSON() const;
    ~LgsSymbol() = default;
};

#endif //LOGOSSYMBOL_H
