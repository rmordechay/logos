#pragma once
#include "exprs/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/LgsFuncType.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsBool.h"

class LgsTest final : public LgsObject {
public:
    static constexpr auto name = "Test";
    LgsFunc* mockFunc = new LgsFunc{"mock", &LGS_VOID, std::vector<LgsType*>{&LGS_ANY, &LGS_ANY}, PUBLIC | BUILTIN};
    LgsFunc* assertFunc = new LgsFunc{"assert", &LGS_BOOL, std::vector<LgsType*>{&LGS_BOOL, new LgsStr()}, PUBLIC | BUILTIN};

    explicit LgsTest(): LgsObject(name) {
        assertFunc->funcType->params[1].expr = new LgsStrConst("");
        addMethod(mockFunc);
        addMethod(assertFunc);
    }
};
