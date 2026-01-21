#include "types/LgsInterface.h"
#include "codegen/LgsCgModule.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"

bool LgsInterface::canCastTo(LgsType* other) {
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
