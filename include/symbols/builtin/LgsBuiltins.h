#pragma once
#include "funcs/LgsBuiltinFunc.h"
#include "utils/LgsUtils.h"
#include <types/primitives/LgsVoid.h>
#include <types/primitives/LgsLong.h>
#include <types/LgsAny.h>

class LgsPrint final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "print";

    explicit LgsPrint(): LgsBuiltinFunc(name, &LGS_VOID, "", {&LGS_ANY, &LGS_ANY}, true, true) {
        funcType->IRName = "printf";
    }

    Value* call(LgsModule* module, const vector<LgsExpr*>& args) override {
        vector<Value*> IRArgs;
        stringstream str;
        for (int i = 0; i < args.size(); ++i) {
            const auto arg = args[i];
            const auto argType = arg->type->getIRType(module->context);
            auto argValue = arg->getIRValue(module);
            if (shouldLoadIRArg(argValue, arg)) {
                argValue = module->builder.CreateLoad(argType, argValue);
            }
            IRArgs.push_back(argValue);
            str << arg->type->getStrFormatPart() << std::endl;
        }
        IRArgs.insert(IRArgs.begin(), getIRStr(module, str.str()));
        const auto printfFunc = getPrintf(module);
        const auto callInst = module->builder.CreateCall(printfFunc, IRArgs);
        return callInst;
    }

    ~LgsPrint() override = default;
};

class LgsSizeOf final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "sizeof";

    LgsSizeOf(): LgsBuiltinFunc(name, &LGS_LONG, "", {&LGS_ANY}) {}
    Value* call(LgsModule* module, const vector<LgsExpr*>& args) override {
        return module->builder.getInt64(args.front()->type->getSizeBytes());
    }
};

inline LgsPrint lgsPrint;
inline LgsSizeOf lgsSizeof;
