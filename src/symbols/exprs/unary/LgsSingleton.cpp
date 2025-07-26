#include "exprs/unary/LgsSingleton.h"

#include "types/LgsObject.h"

Value* LgsSingleton::createIRValue(LgsModule* module) {
    const auto objIRType = obj->getIRType(module);
    const auto initializer = ConstantAggregateZero::get(objIRType);
    return new GlobalVariable(*module->IRModule, objIRType, false, GlobalValue::ExternalLinkage, initializer);
}

string LgsSingleton::prettyName() {
    assert(0);
}
