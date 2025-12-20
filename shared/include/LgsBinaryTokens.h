#pragma once
#include "LgsTokens.h"
#include <unordered_map>

enum LgsBinOpType {
    ADD,
    SUB,
    MUL,
    DIV,
    MODULO,
    POW,
    BIT_AND,
    BIT_OR,
    BIT_XOR,
    LSHIFT,
    RSHIFT,
    EQ,
    NE,
    LT,
    GT,
    GE,
    LE,
    AND,
    OR,
    IN,
    CROSS,
    NOOP,
};

enum LgsAssignType {
    ASSIGN,
    ASSIGN_ADD,
    ASSIGN_SUB,
    ASSIGN_MUL,
    ASSIGN_DIV,
    ASSIGN_MOD,
    ASSIGN_POW,
    ASSIGN_AND,
    ASSIGN_OR,
    ASSIGN_XOR,
    ASSIGN_LSHIFT,
    ASSIGN_RSHIFT,
    ASSIGN_UNKNOWN,
};

struct LgsBinOp {
    LgsBinOpType opType;
    std::string text;
};

struct LgsAssignOp {
    LgsAssignType opType;
    std::string text;
};

const auto ADD_OP = LgsBinOp{ADD, "Addition"};
const auto SUB_OP = LgsBinOp{SUB, "Subtraction"};
const auto MUL_OP = LgsBinOp{MUL, "Multiplication"};
const auto DIV_OP = LgsBinOp{DIV, "Division"};
const auto MODULO_OP = LgsBinOp{MODULO, "Module"};
const auto POW_OP = LgsBinOp{POW, "Power"};
const auto BIT_AND_OP = LgsBinOp{BIT_AND, "Bit-and"};
const auto BIT_OR_OP = LgsBinOp{BIT_OR, "Bit-or"};
const auto BIT_XOR_OP = LgsBinOp{BIT_XOR, "Xor"};
const auto LSHIFT_OP = LgsBinOp{LSHIFT, "Left-shift"};
const auto RSHIFT_OP = LgsBinOp{RSHIFT, "Right-shift"};
const auto EQ_OP = LgsBinOp{EQ, "=="};
const auto NE_OP = LgsBinOp{NE, "!="};
const auto GT_OP = LgsBinOp{GT, ">"};
const auto LT_OP = LgsBinOp{LT, "<"};
const auto GE_OP = LgsBinOp{GE, "<="};
const auto LE_OP = LgsBinOp{LE, ">="};
const auto AND_OP = LgsBinOp{AND, "And"};
const auto OR_OP = LgsBinOp{OR, "Or"};
const auto IN_OP = LgsBinOp{IN, "In"};
const auto CROSS_OP = LgsBinOp{CROSS, "Cross-product"};
const auto NOOP_BIN_OP = LgsBinOp{NOOP, ""};

// Names will be attached to 'assign'. for example, re-assign, add-assign, etc.
const auto ASSIGN_OP = LgsAssignOp{ASSIGN, "re"};
const auto ADD_ASSIGN_OP = LgsAssignOp{ASSIGN_ADD, "add"};
const auto SUB_ASSIGN_OP = LgsAssignOp{ASSIGN_SUB, "subtract"};
const auto MUL_ASSIGN_OP = LgsAssignOp{ASSIGN_MUL, "multiply"};
const auto DIV_ASSIGN_OP = LgsAssignOp{ASSIGN_DIV, "divide"};
const auto MODULO_ASSIGN_OP = LgsAssignOp{ASSIGN_MOD, "modulo"};
const auto POW_ASSIGN_OP = LgsAssignOp{ASSIGN_POW, "power"};
const auto BIT_AND_ASSIGN_OP = LgsAssignOp{ASSIGN_AND, "and"};
const auto BIT_OR_ASSIGN_OP = LgsAssignOp{ASSIGN_OR, "or"};
const auto BIT_XOR_ASSIGN_OP = LgsAssignOp{ASSIGN_XOR, "xor"};
const auto LSHIFT_ASSIGN_OP = LgsAssignOp{ASSIGN_LSHIFT, "lshift"};
const auto RSHIFT_ASSIGN_OP = LgsAssignOp{ASSIGN_RSHIFT, "rshift"};
const auto NOOP_ASSIGN_OP = LgsAssignOp{ASSIGN_UNKNOWN, "rshift"};

const std::unordered_map<LgsTokenType, LgsBinOp> LGS_BINARY_OPS_DICT = {
    {T_PLUS, ADD_OP},
    {T_MINUS, SUB_OP},
    {T_STAR, MUL_OP},
    {T_SLASH, DIV_OP},
    {T_PERCENT, MODULO_OP},
    {T_CARET, POW_OP},
    {T_AMPERSAND, BIT_AND_OP},
    {T_PIPE, BIT_OR_OP},
    {T_DOUBLE_CARET, BIT_XOR_OP},
    {T_DOUBLE_LANGLE, LSHIFT_OP},
    {T_DOUBLE_RANGLE, RSHIFT_OP},
    {T_DOUBLE_EQUAL, EQ_OP},
    {T_NOT_EQUAL, NE_OP},
    {T_LANGLE, LT_OP},
    {T_RANGLE, GT_OP},
    {T_GE, GE_OP},
    {T_LE, LE_OP},
    {T_AND, AND_OP},
    {T_OR, OR_OP},
    {T_IN, IN_OP},
    {T_UNKNOWN, NOOP_BIN_OP},
};

const std::unordered_map<LgsTokenType, LgsAssignOp> LGS_ASSIGN_OPS_DICT = {
    {T_WALRUS, ASSIGN_OP},
    {T_EQUAL_PLUS, ADD_ASSIGN_OP},
    {T_EQUAL_MINUS, SUB_ASSIGN_OP},
    {T_EQUAL_STAR, MUL_ASSIGN_OP},
    {T_EQUAL_SLASH, DIV_ASSIGN_OP},
    {T_EQUAL_PERCENT, MODULO_ASSIGN_OP},
    {T_EQUAL_DOLLAR, POW_ASSIGN_OP},
    {T_EQUAL_AMPERSAND, BIT_AND_ASSIGN_OP},
    {T_EQUAL_PIPE, BIT_OR_ASSIGN_OP},
    {T_EQUAL_CARET, BIT_XOR_ASSIGN_OP},
    {T_EQUAL_DOUBLE_RANGLE, LSHIFT_ASSIGN_OP},
    {T_EQUAL_DOUBLE_LANGLE, RSHIFT_ASSIGN_OP},
    {T_UNKNOWN, NOOP_ASSIGN_OP},
};
