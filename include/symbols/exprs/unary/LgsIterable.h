#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H
#include "constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/LgsInt.h"

struct CodeGenMetadata;

class LgsIterable final {
public:
    size_t length;
    LgsType* type = nullptr;
    LgsType* underlyingType = nullptr;

    void setFields() const;
    Type* getIRType(int size) const;
    ~LgsIterable() = default;
};

inline void LgsIterable::setFields() const {
    const auto lenField = new LgsField("len", &LGS_INT, new LgsIntConst(length));
    type->fields[lenField->name] = lenField;
}

inline Type* LgsIterable::getIRType(const int size) const {
    return ArrayType::get(underlyingType->getIRType(), size);
}

#endif //LOGOSITERABLE_H
