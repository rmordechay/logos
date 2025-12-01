#pragma once
#include "LgsExpr.h"
#include "LgsNull.h"
#include "types/LgsJsonType.h"
#include "types/LgsObject.h"

class LgsNull;

class LgsJsonArray {
public:
    std::vector<LgsJson*> elements;
};

class LgsJsonObject {
public:
    std::map<std::string, LgsJson*> entries;
};

class LgsJson final : public LgsExpr {
public:
    LgsJsonType* jsonType;
    union {
        LgsJsonObject* obj;
        LgsJsonArray* arr;
        LgsIntConst* intConst;
        LgsFloatConst* floatConst;
        LgsStrConst* strConst;
        LgsNull* null;
    };
    explicit LgsJson(LgsJsonType* type, LgsJsonObject* obj): LgsExpr(type), jsonType(type), obj(obj) {}
    explicit LgsJson(LgsJsonType* type, LgsJsonArray* arr): LgsExpr(type), jsonType(type), arr(arr) {}
    explicit LgsJson(LgsJsonType* type, LgsIntConst* intConst): LgsExpr(type), jsonType(type), intConst(intConst) {}
    explicit LgsJson(LgsJsonType* type, LgsFloatConst* floatConst): LgsExpr(type), jsonType(type), floatConst(floatConst) {}
    explicit LgsJson(LgsJsonType* type, LgsStrConst* strConst): LgsExpr(type), jsonType(type), strConst(strConst) {}
    explicit LgsJson(LgsJsonType* type, LgsNull* null): LgsExpr(type), jsonType(type), null(null) {}
    bool equals(LgsExpr* other) override;
    std::string asText() override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsJson() override;
};
