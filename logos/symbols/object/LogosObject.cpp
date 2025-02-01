#include "LogosObject.h"

const string LogosObject::name() const {
    return typeName;
}

Type* LogosObject::getLLVMType(IRBuilder<>* builder) const {
    return nullptr;
}

bool LogosObject::operator==(LogosType* other) const {

}

LogosObject::~LogosObject() {
    for (const auto var : fields) {
        delete var;
    }
    for (const auto func : funcs) {
        delete func;
    }
}
