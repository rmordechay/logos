#ifndef CODEADD_H
#define CODEADD_H
#include "LogosCodeNode.h"
#include "LogosOperator.h"
#include "LogosType.h"

class CodeAddInt final : public LogosCodeNode {
public:
    std::shared_ptr<LogosType> left;
    std::shared_ptr<LogosType> right;
    LogosOperator op;

    explicit CodeAddInt(const std::shared_ptr<LogosType>& left, const std::shared_ptr<LogosType>& right, const LogosOperator op) : left(left), right(right), op(op) {}
    void generateCode(const LLVMContext& context, const IRBuilder<>& builder, Module* module) override;
};

#endif //CODEADD_H
