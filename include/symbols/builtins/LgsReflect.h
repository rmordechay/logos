#pragma once
#include "exprs/LgsInstance.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/LgsObject.h"
#include "types/iterables/LgsStr.h"

class LgsReflect final : public LgsObject {
public:
    static constexpr auto name = "Reflect";
    LgsFunc* getFieldFunc = new LgsFunc{"getField", &LGS_ANY, {&LGS_ANY, new LgsStr()}, PUBLIC | BUILTIN};
    LgsFunc* getMethodFunc = new LgsFunc{"getMethod", new LgsFuncType(&LGS_ANY, {}, VIRTUAL | METHOD), {&LGS_ANY, new LgsStr()}, PUBLIC | BUILTIN};

    explicit LgsReflect() : LgsObject(name) {
        addMethod(getFieldFunc);
        addMethod(getMethodFunc);
        getMethodFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) -> Value* {
            if (args.size() < 2) return nullptr;
            assert(0);
        };
    }
};
