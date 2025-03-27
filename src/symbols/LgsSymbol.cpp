#include "LgsSymbol.h"

#include "funcs/LgsParam.h"
#include "stmts/LgsEnum.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

void LgsSymbol::free(CodeGenMetadata* metadata) const {
    switch (type) {
    case VAR_DEC:
        varDec->free(metadata);
        break;
    case ENUM:
        lgsEnum->free(metadata);
        break;
    default:
        break;
    }
}
