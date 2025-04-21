#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H
#include <string>
#include <json/json.hpp>

class LgsField;
struct CodeGenMetadata;
class LgsEnum;
class LgsEnumField;
class LgsFunc;
class LgsInterface;
class LgsObject;
class LgsParam;
class LgsVarDec;

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
    union {
        LgsVarDec* varDec;
        LgsParam* param;
        LgsObject* object;
        LgsInterface* interface;
        LgsField* field;
        LgsFunc* func;
        LgsEnum* lgsEnum;
        LgsEnumField* enumField;
    };

    LgsSymbol();
    explicit LgsSymbol(LgsParam* param);
    explicit LgsSymbol(LgsVarDec* varDec);
    explicit LgsSymbol(LgsFunc* func);
    explicit LgsSymbol(LgsObject* object);
    explicit LgsSymbol(LgsInterface* interface);
    explicit LgsSymbol(LgsField* field);
    explicit LgsSymbol(LgsEnum* lgsEnum);
    explicit LgsSymbol(LgsEnumField* enumField);
    void free(CodeGenMetadata* metadata) const;
    nlohmann::json asJSON() const;
    ~LgsSymbol() = default;
};

#endif //LOGOSSYMBOL_H
