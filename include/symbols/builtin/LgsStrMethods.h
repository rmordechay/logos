#ifndef LGSSTRMETHODS_H
#define LGSSTRMETHODS_H
#include "LgsBuiltinFunc.h"
#include "logos/LgsRuntime.h"
#include "utils/LgsUtils.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"

#define BUFFER_SIZE 1024

inline FunctionCallee getSnprintf(LgsRuntime* runtime) {
    const auto printfType = FunctionType::get(runtime->builder.getInt32Ty(), {PointerType::getUnqual(context), runtime->builder.getInt64Ty(), PointerType::getUnqual(context)}, true);
    return runtime->module->getOrInsertFunction("snprintf", printfType);
}

class LgsStrFormatFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};
    LgsParam args{&LGS_ANY};

    explicit LgsStrFormatFunc(LgsType* parent) : LgsBuiltinFunc("format", parent, parent->getIRName()) {
        self.type = parent;
        funcType.isVariadic = true;
        funcType.isPublic = true;
        funcType.params = {&self};
    }

    Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args) override {
        const bool isConst = args[0]->type->isConst;
        if (!isConst) assert(false);
        const auto formatString = getFormatString(args);
        const auto baseIRStr = getIRStr(runtime, formatString);
        const auto bufferType = ArrayType::get(runtime->builder.getInt8Ty(), BUFFER_SIZE);
        const auto buffer = runtime->builder.CreateAlloca(bufferType);
        const auto gep = runtime->builder.CreateGEP(bufferType, buffer, {runtime->builder.getInt32(0), runtime->builder.getInt32(0)});
        vector<Value*> IRArgs = {gep, runtime->builder.getInt64(BUFFER_SIZE), baseIRStr};
        for (int i = 1; i < args.size(); ++i) {
            IRArgs.emplace_back(args[i]->getIRValue(runtime));
        }
        const auto printfFunc = getSnprintf(runtime);
        runtime->builder.CreateCall(printfFunc, IRArgs);
        return gep;
    }
};


class LgsStrLenFunc final : public LgsBuiltinFunc {
public:
    LgsParam self{};

    explicit LgsStrLenFunc(LgsType* parent) : LgsBuiltinFunc("len", &LGS_INT, parent->getIRName()) {
        self.type = parent;
        funcType.IRName = "strlen";
        funcType.params = {&self};
        funcType.isPublic = true;
    }
};

#endif //LGSSTRMETHODS_H
