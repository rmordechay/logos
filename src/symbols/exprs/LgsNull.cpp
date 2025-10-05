#include "exprs/LgsNull.h"
#include "utils/LgsUtils.h"

json::value LgsNull::asJsonStr() {
    return json::value(nullptr);
}

std::string LgsNull::getName() {
    return "null";
}

LgsNull::~LgsNull() {
    freeType(type);
    type = nullptr;
}