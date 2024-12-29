#ifndef CODESTOREINT_H
#define CODESTOREINT_H
#include "LogosCodeNode.h"
#include "LogosType.h"


class CodeStoreInt final : public LogosCodeNode {
public:
    std::string name;
    std::shared_ptr<LogosType> value;

    explicit CodeStoreInt(const std::string& name, const std::shared_ptr<LogosType>& value) : name(name), value(value) {}
    void generateCode(const LLVMContext& context, const IRBuilder<>& builder, Module* module) override;
};



#endif //CODESTOREINT_H
