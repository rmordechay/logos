#ifndef PRINTCALL_H
#define PRINTCALL_H
#include "codegen/BuiltinFunc.h"

#include <map>

class Print final : public BuiltinFunc {
public:
    std::string name = "print";
    const std::vector<LogosSymbol*> params = {new LogosSymbol(PARAM)};

    explicit Print(): BuiltinFunc() {}
    explicit Print(LogosSymbol* args...): BuiltinFunc(args) {}
    void generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const override;
};

const std::map<std::string, BuiltinFunc*> BUILTIN_FUNCS = {{"print", new Print()}};

#endif //PRINTCALL_H
