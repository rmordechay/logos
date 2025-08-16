#pragma once
#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/primitives/LgsFloat.h"

class LgsVec2 final : public LgsIterable {
public:
    static constexpr auto name = "vec2";
    LgsField* x = new LgsField("x", &LGS_FLOAT, LGS_FLOAT.getZeroValue());
    LgsField* y = new LgsField("y", &LGS_FLOAT, LGS_FLOAT.getZeroValue());

    explicit LgsVec2() : LgsIterable(&LGS_FLOAT) {
        sizeExpr = new LgsIntConst(2);
        addField(x);
        addField(y);
    }
    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string pname() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    Value* IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    bool equals(LgsType* other) override;
    ~LgsVec2() override = default;
};
