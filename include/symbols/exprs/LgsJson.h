#pragma once
#include "LgsExpr.h"
#include "LgsNull.h"
#include "constants/LgsFloatConst.h"
#include "constants/LgsIntConst.h"
#include "constants/LgsStrConst.h"
#include "utils/LgsUtils.h"

class LgsNull;

enum LgsJsonType {
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_INT,
    JSON_FLOAT,
    JSON_STRING,
    JSON_NULL,
};

class LgsJsonArray {
public:
    std::vector<LgsJson*> entries;
};

class LgsJsonObject {
public:
    std::map<std::string, LgsJson*> entries;
};

class LgsJsonPrimitive {
public:
    LgsJsonType jsonType;
    union {
        LgsIntConst intConst;
        LgsFloatConst* floatConst;
        LgsStrConst* strConst;
        LgsNull* null;
    };
};

class LgsJson final : public LgsExpr {
public:
    LgsJsonType jsonType;
    union {
        LgsJsonObject* jsonObject;
        LgsJsonArray* jsonArray;
        LgsIntConst* intConst;
        LgsFloatConst* floatConst;
        LgsStrConst* strConst;
        LgsNull* null;
    };
    ~LgsJson() override;
};

inline LgsJson::~LgsJson() {
    switch (jsonType) {
    case JSON_OBJECT:
        delete jsonObject;
        break;
    case JSON_ARRAY:
        delete jsonArray;
        break;
    case JSON_INT:
        freeExpr(intConst);
        break;
    case JSON_FLOAT:
        freeExpr(floatConst);
        break;
    case JSON_STRING:
        freeExpr(strConst);
        break;
    case JSON_NULL:
        freeExpr(null);
        break;
    }
}
