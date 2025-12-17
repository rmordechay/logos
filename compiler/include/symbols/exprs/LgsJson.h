#pragma once
#include "LgsExpr.h"
#include "types/LgsJsonType.h"
#include "types/LgsObject.h"

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
    };
    explicit LgsJson(LgsJsonType* type, LgsJsonObject* obj): LgsExpr(type), jsonType(type), obj(obj) {}
    explicit LgsJson(LgsJsonType* type, LgsJsonArray* arr): LgsExpr(type), jsonType(type), arr(arr) {}
    explicit LgsJson(LgsJsonType* type, LgsIntConst* intConst): LgsExpr(type), jsonType(type), intConst(intConst) {}
    explicit LgsJson(LgsJsonType* type, LgsFloatConst* floatConst): LgsExpr(type), jsonType(type), floatConst(floatConst) {}
    explicit LgsJson(LgsJsonType* type, LgsStrConst* strConst): LgsExpr(type), jsonType(type), strConst(strConst) {}
    bool equals(LgsExpr* other) override;
    std::string asText() override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsJson() override;
};
