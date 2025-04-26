#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H
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
    LgsVarDec* varDec = nullptr;
    LgsParam* param = nullptr;
    LgsObject* object = nullptr;
    LgsInterface* interface = nullptr;
    LgsField* field = nullptr;
    LgsEnum* lgsEnum = nullptr;
    LgsEnumField* enumField = nullptr;
    std::vector<LgsFunc*> func;

    LgsSymbol();
    explicit LgsSymbol(LgsParam* param);
    explicit LgsSymbol(LgsVarDec* varDec);
    explicit LgsSymbol(const std::vector<LgsFunc*>& func);
    explicit LgsSymbol(LgsObject* object);
    explicit LgsSymbol(LgsInterface* interface);
    explicit LgsSymbol(LgsField* field);
    explicit LgsSymbol(LgsEnum* lgsEnum);
    explicit LgsSymbol(LgsEnumField* enumField);
    void free(CodeGenMetadata* metadata) const;
    LgsSymbol* clone() const;
    nlohmann::json asJSON() const;
    ~LgsSymbol() = default;
};

#endif //LOGOSSYMBOL_H
