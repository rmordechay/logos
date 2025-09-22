#include "types/iterables/LgsIterable.h"
#include "funcs/LgsFunc.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsSize.h"

LgsFunc* LgsIterable::getMethod(const std::string& name) {
    const auto method = methods.find(name);
    if (method != methods.end()) {
        if (name == ADD_FUNC_NAME) {
            return getAddFunc();
        }
        if (name == LEN_FUNC_NAME) {
            return getLenFunc();
        }
        if (name == IS_EMPTY_FUNC_NAME) {
            return getIsEmptyFunc();
        }
        if (name == IS_NOT_EMPTY_FUNC_NAME) {
            return getIsNotEmptyFunc();
        }
        assert(method->second);
        return method->second;
    }
    return nullptr;
}

Value* LgsIterable::loadWithIndex(LgsLLVMGen* cg) {
    assert(0);
}

LgsFunc* LgsIterable::getAddFunc() {
    assert(0);
}

LgsFunc* LgsIterable::getMapFunc() {
    assert(0);
}

LgsFunc* LgsIterable::getLenFunc() {
    const auto lenFunc = methods.find(LEN_FUNC_NAME);
    if (lenFunc != methods.end() && lenFunc->second) return lenFunc->second;
    lenFunc->second = new LgsFunc(LEN_FUNC_NAME, &LGS_SIZE, {this}, BUILTIN | PUBLIC | METHOD);
    addMethod(lenFunc->second);
    return lenFunc->second;
}

LgsFunc* LgsIterable::getIsEmptyFunc() {
    const auto isEmptyFunc = methods.find(IS_EMPTY_FUNC_NAME);
    if (isEmptyFunc != methods.end() && isEmptyFunc->second) return isEmptyFunc->second;
    isEmptyFunc->second = new LgsFunc(IS_EMPTY_FUNC_NAME, &LGS_BOOL, {this}, BUILTIN | PUBLIC | METHOD);
    addMethod(isEmptyFunc->second);
    return isEmptyFunc->second;
}

LgsFunc* LgsIterable::getIsNotEmptyFunc() {
    const auto isNotEmptyFunc = methods.find(IS_NOT_EMPTY_FUNC_NAME);
    if (isNotEmptyFunc != methods.end() && isNotEmptyFunc->second) return isNotEmptyFunc->second;
    isNotEmptyFunc->second = new LgsFunc(IS_NOT_EMPTY_FUNC_NAME, &LGS_BOOL, {this}, BUILTIN | PUBLIC | METHOD);;;
    addMethod(isNotEmptyFunc->second);
    return isNotEmptyFunc->second;
}

LgsIterable::~LgsIterable() {
    if (sizeExpr) {
        freeExpr(sizeExpr);
        sizeExpr = nullptr;
    }
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
