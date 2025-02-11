#include "LogosExpr.h"

#include "LogosBinaryExpr.h"
#include "LogosUnaryExpr.h"
#include "LogosConstructor.h"

Value* LogosExpr::getLLVMValue(CodeGenMetadata* metadata) {
    if (const auto unary = dynamic_cast<LogosUnaryExpr*>(this)) {
        return unary->getLLVMValue(metadata);
    }
    if (const auto binary = dynamic_cast<LogosBinaryExpr*>(this)) {
        return binary->getLLVMValue(metadata);
    }
    return nullptr;
}

// LogosUnaryExpr* LogosExpr::asUnaryExpr() {
//     return dynamic_cast<LogosUnaryExpr*>(this);
// }
//
// LogosConstructor* LogosExpr::asConstructor() {
//     return dynamic_cast<LogosConstructor*>(this);
// }
