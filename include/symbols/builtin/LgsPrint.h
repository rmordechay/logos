#pragma once
#include "funcs/LgsBuiltinFunc.h"


#include "utils/LgsUtils.h"


#include <types/primitives/LgsVoid.h>
#include <types/LgsAny.h>

class LgsPrint final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "print";

    explicit LgsPrint(): LgsBuiltinFunc(name, &LGS_VOID, "") {
        funcType.isVariadic = true;
        funcType.IRName = "printf";
        funcType.params = {LgsParam{&LGS_ANY}, LgsParam{&LGS_ANY}};
    }

    Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args) override {
        vector<Value*> IRArgs;
        stringstream str;
        for (int i = 0; i < args.size(); ++i) {
            const auto arg = args[i];
            const auto argType = arg->type->getIRType();
            const auto argValue = arg->getIRValue(runtime);
            const auto IRArg = addIRArg(runtime, argType, argValue);
            IRArgs.push_back(IRArg);
            str << arg->type->getStrFormatPart() << std::endl;
        }
        IRArgs.insert(IRArgs.begin(), getIRStr(runtime, str.str()));
        const auto printfFunc = getPrintf(runtime);
        runtime->builder.CreateCall(printfFunc, IRArgs);
        return nullptr;
    }

    ~LgsPrint() override = default;
};

class LgsSizeOf final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "sizeof";

    LgsSizeOf(): LgsBuiltinFunc(name, &LGS_LONG, "") {
        funcType.params = {LgsParam{&LGS_ANY}};
    }

    Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args) override {
        return runtime->builder.getInt64(args.front()->type->getSizeBytes());
    }
};

inline LgsPrint lgsPrint;
inline LgsSizeOf lgsSizeof;


