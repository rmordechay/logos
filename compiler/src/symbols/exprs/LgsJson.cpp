#include "exprs/LgsJson.h"
#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsIntConst.h"
#include "exprs/constants/LgsStrConst.h"

bool LgsJson::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsJson::asText() {
    assert(0);
}

void LgsJson::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsJson::~LgsJson() {
    switch (jsonType->kind) {
    case JSON_OBJECT:
        delete obj;
        break;
    case JSON_ARRAY:
        delete arr;
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
        break;
    case JSON_UNKNOWN:
        break;
    }
}
