#ifndef LOGOSITERABLE_H
#define LOGOSITERABLE_H

#include "constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/LgsInt.h"

#include <cstddef>
struct CodeGenMetadata;

class LgsIterable {
public:
    virtual size_t length() = 0;
    virtual Value* sizeIR(CodeGenMetadata* metadata) = 0;
    virtual ~LgsIterable() = default;
    void setFields(LgsType* type);
};

inline void LgsIterable::setFields(LgsType* type) {
    const auto lenField = new LgsField("len", &LGS_INT, new LgsIntConst(length()));
    type->fields[lenField->name] = lenField;
}

#endif //LOGOSITERABLE_H
