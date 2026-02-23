#include "types/LgsInterface.h"

#include <llvm/IR/Constant.h>
#include <vector>

#include "codegen/LgsCodeGen.h"
#include "types/LgsObject.h"
#include "LgsType.h"

bool LgsInterface::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    if (const auto interface = other->asInterface()) {
        if (interface->name == getName()) return true;
    } else if (const auto obj = other->asObject()) {
        if (obj->name == getName()) return true;
        for (const auto& implement : obj->implements) {
            if (implement->getName() == getName()) return true;
        }
    }
    return false;
}

LgsExpr* LgsInterface::getZeroValue() {
    return nullptr;
}

Value* LgsInterface::getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) {
    return cg.null();
}
