#pragma once
#include "Lgs_Types.h"
#include "exprs/LgsExpr.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>
#include <cmath>
#include <map>
#include <filesystem>
#include <llvm/Passes/OptimizationLevel.h>

class LgsFile;
namespace llvm {
    class PassBuilder;
    class TargetMachine;
}

using llvm::DIBuilder;
using llvm::IRBuilderBase;
using llvm::IRBuilder;

struct LgsLLDBGen {
    DIFile* diFile = nullptr;
    DIBuilder* diBuilder = nullptr;
    DICompileUnit* compileUnit = nullptr;
    DISubprogram* subprogram = nullptr;
    std::vector<llvm::DIScope*> blocks = {};
};

class LgsLLVMGen {
public:
    LLVMContext context;
    LgsLLDBGen debugger;
    Module* IRModule = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    IRBuilder<> builder = IRBuilder(context);
    std::map<std::string, Type*> typesRegistry;
    std::unordered_map<std::string, Value*> stringsRegistry;

    void setupModule(const LgsFile& file, bool debugMode = false);
    void loop(Value* loopLength, const std::function<void(Value*, BasicBlock*)>& body);
    Constant* getIRStr(const std::string& value);
    Value* getPtrTo(Value* v);
    GlobalVariable* createGlobal(const std::string& name, Type* type, Constant* args, bool isConst = false, GlobalValue::LinkageTypes linkage = GlobalValue::ExternalLinkage) const;
    StructType* getStructType(const std::vector<Type*>& fields, const std::string& name = "");
    llvm::AllocaInst* getEmptyBuffer();

    // Blocks
    BasicBlock* createBlock(const std::string& name = "", Function* parent = nullptr);
    void branchIfNeeded(BasicBlock* block);
    void startBlock(BasicBlock* block);
    void branchAndStartBlock(BasicBlock* block);
    bool lastInstTerminator() const;
    void createBoundsGuard(Value* len, Value* index);

    // Funcs
    static FunctionType* getFT(Type* rt, const std::vector<Type*>& params = {}, bool isVariadic = false);
    Function* getFunc(const std::string& funcName, FunctionType* ft, GlobalValue::LinkageTypes linkage = GlobalValue::ExternalLinkage) const;
    Value* callFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes = {}, const std::vector<Value*>& args = {}, bool isVariadic = false);
    Value* callIntrinsics(llvm::Intrinsic::ID intrinsicID, const std::vector<Type*>& types = {}, const std::vector<Value*>& args = {});
    Value* callLgsFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes = {}, const std::vector<Value*>& args = {});
    Value* callRuntimeFunc(const std::string& funcName, Type* rt, const std::vector<Type*>& paramTypes = {}, const std::vector<Value*>& args = {});
    Value* callHash(Value* arg);
    Value* hashConst(const std::string& str);

    // System
    Value* callPrintf(const std::vector<Value*>& args);
    Value* callSnprintf(Value* buffer, Value* fmt, const std::vector<Value*>& args);
    Value* callStrLen(Value* str);
    void callMemSet(Value* dest, Value* src, Value* size);
    void callMemCpy(Value* dest, Value* src, Value* size);
    Value* callAllocate(size_t size, bool isOwner, Lgs_TypeKind type);
    Value* callAllocate(Value* size, bool isOwner, Lgs_TypeKind type);

    // Stack
    void callStackPush(bool hasDefers, bool needsCleanup);
    void callPopStack(bool hasDefers, bool needsCleanup = false);
    void addToVTable(Value* instance, Value* key, Value* ptr);
    Value* getFromVTable(Value* instance, Value* key);
    void addNullTerminate(Value* strPtr, Value* pos);
    void addHeap(bool isOwner, Lgs_TypeKind type, Value* ptr);

    // Types
    Type* i1Ty();
    Type* i8Ty();
    Type* i16Ty();
    Type* i32Ty();
    Type* i64Ty();
    Type* floatTy();
    Type* doubleTy();
    Type* voidTy();
    IntegerType* sizeTy();
    PointerType* ptrTy();

    // Values
    Constant* null();
    ConstantInt* true_();
    ConstantInt* false_();
    ConstantInt* i1(bool v);
    ConstantInt* i8(int8_t v);
    ConstantInt* i16(int16_t v);
    ConstantInt* i32(int32_t v);
    ConstantInt* i64(int64_t v);
    ConstantInt* usize(size_t v);
    ConstantInt* i8Zero();
    ConstantInt* i32Zero();
    ConstantInt* i64Zero();
    ConstantInt* sizeZero();
    Value* extendToSize(Value* v);
    Constant* floatv(float_t v);
    Constant* doublev(double_t v);
    TypeSize typeSize(Type* v) const;
    Value* emptyStr();

    // Debugging
    void printStr(const std::string& str);
    void printPtr(Value* ptr, const std::string& text = "");
    void printInt(Value* number, const std::string& text = "");

    void finalizeDebugger(const std::filesystem::path& buildPath) const;
    llvm::DILocation* getDebugLoc(const LgsLocation& location);
    static void initLLVM();
    static llvm::OptimizationLevel getOptLevel(uint8_t optLevel);
    ~LgsLLVMGen();
};

inline TargetMachine* targetMachine;
