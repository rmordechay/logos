#pragma once
#include "LgsExpr.h"
#include "LgsNull.h"
#include "constants/LgsFloatConst.h"
#include "constants/LgsIntConst.h"
#include "constants/LgsStrConst.h"

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
    bool equals(LgsExpr* other) override;
    std::string asText() override;
    ~LgsJson() override;
};

inline bool LgsJson::equals(LgsExpr* other) {
    assert(0);
}

inline std::string LgsJson::asText() {
    assert(0);
}

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
