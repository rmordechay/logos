#include "logos/LgsRuntime.h"
#include "logos/LgsGlobals.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsFuncImpl.h"

void LgsRuntime::enterScope(LgsFunc* func) {
    LgsFunc* currentFunc = nullptr;
    if (func) {
        currentFunc = func;
    } else {
        currentFunc = getCurrentFunc();
    }
    if (stage == LGS_RUNTIME) {
        std::cout << currentFunc->location.getFullPath(currentFunc->path) << std::endl;
    }
    if (stack.empty()) {
        stack.push(LgsStackFrame{.currentFunc = currentFunc});
    } else {
        stack.push(LgsStackFrame{.symbols = stack.top().symbols, .currentFunc = currentFunc, .currentLoop = getCurrentLoop()});
    }
}

void LgsRuntime::exitScope() {
    stack.pop();
}

void LgsRuntime::exitFunc() {
    stack.pop();
}

void LgsRuntime::reset() {
    while (stack.size() > 0) {
        stack.pop();
    }
}

// %struct.Runtime = type { %struct.Stack }
// %struct.Stack = type { i32, [512 x %struct.StackStr] }
// %struct.StackStr = type { [1024 x i8], i32 }
//
// @.str = private unnamed_addr constant [2 x i8] c"1\00", align 1
// @.str.1 = private unnamed_addr constant [2 x i8] c"2\00", align 1
// @.str.2 = private unnamed_addr constant [2 x i8] c"3\00", align 1
// @.str.3 = private unnamed_addr constant [2 x i8] c"4\00", align 1
//
// ; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
// define i32 @main() #0 {
//   %1 = alloca %struct.Runtime, align 4
//   call void @init(ptr noundef %1)
//   call void @push(ptr noundef %1, ptr noundef @.str)
//   call void @push(ptr noundef %1, ptr noundef @.str.1)
//   call void @push(ptr noundef %1, ptr noundef @.str.2)
//   call void @push(ptr noundef %1, ptr noundef @.str.3)
//   call void @print_stack(ptr noundef %1)
//   ret i32 0
// }

void LgsRuntime::printStack(CodegenMetadata* metadata) const {
    LgsParam lgsParam(&LGS_INT);
    auto printStack = LgsFuncImpl("print_stack", &LGS_VOID, {&lgsParam});
}

LgsFunc* LgsRuntime::getCurrentFunc() {
    assert(stack.size() > 0);
    return stack.top().currentFunc;
}

LgsForLoop* LgsRuntime::getCurrentLoop() {
    assert(stack.size() > 0);
    return stack.top().currentLoop;
}

void LgsRuntime::addLocalSymbol(const string& name, const LgsSymbol& symbol) {
    assert(stack.size() > 0);
    stack.top().symbols[name] = symbol;
}
