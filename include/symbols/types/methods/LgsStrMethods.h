#pragma once
#include "funcs/LgsBuiltinFunc.h"
#include "types/LgsAny.h"
#include "utils/LgsUtils.h"

class LgsStrFormatFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};
    LgsParam args{&LGS_ANY};

    explicit LgsStrFormatFunc(LgsType* parent) : LgsBuiltinFunc("format", parent, parent->getIRName()) {
        self.type = parent;
        funcType.isVariadic = true;
        funcType.isPublic = true;
    }

    Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args) override {
        const bool isConst = args[0]->type->isConst;
        if (!isConst) assert(false);
        constexpr auto bufferSize = 1024;
        const auto formatString = getFormatString(args);
        const auto baseIRStr = getIRStr(runtime, formatString);
        const auto bufferType = ArrayType::get(runtime->builder.getInt8Ty(), bufferSize);
        const auto buffer = runtime->builder.CreateAlloca(bufferType);
        const auto gep = runtime->builder.CreateGEP(bufferType, buffer, {runtime->builder.getInt32(0), runtime->builder.getInt32(0)});
        vector<Value*> IRArgs = {gep, runtime->builder.getInt64(bufferSize), baseIRStr};
        for (int i = 1; i < args.size(); ++i) {
            IRArgs.emplace_back(args[i]->getIRValue(runtime));
        }
        const auto printfFunc = getSnprintf(runtime);
        runtime->builder.CreateCall(printfFunc, IRArgs);
        return gep;
    }
};
