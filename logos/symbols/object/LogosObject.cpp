#include "LogosObject.h"

Type* LogosObject::getLLVMType(IRBuilder<>* builder) const {
    return nullptr;
}

LogosObject::~LogosObject() {
    for (const auto var : fields) {
        delete var;
    }
    for (const auto func : funcs) {
        delete func;
    }
}
