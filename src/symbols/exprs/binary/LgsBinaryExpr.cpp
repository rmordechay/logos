#include "binary/LgsBinaryExpr.h"
#include "constants/LgsConst.h"

Value* LgsBinaryExpr::createIRValue(CodeGenMetadata* metadata) {
    switch (op) {
    case PLUS:         return left->add(metadata, right);
    case MINUS:        return left->sub(metadata, right);
    case STAR:         return left->mul(metadata, right);
    case SLASH:        return left->div(metadata, right);
    case RANGLE:       return left->gt(metadata, right);
    case LANGLE:       return left->lt(metadata, right);
    case DOUBLE_EQUAL: return left->eq(metadata, right);
    case NOT_EQUAL:    return left->ne(metadata, right);
    case LE:           return left->le(metadata, right);
    case GE:           return left->ge(metadata, right);
    default:           return nullptr;
    }
}
