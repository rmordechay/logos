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

struct LgsBinOp {
    LgsBinOpType opType;
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

const std::unordered_map<LgsTokenType, LgsBinOp> LGS_BINARY_OPS_DICT = {
    {T_PLUS, ADD_OP},
    {T_EQUAL_PLUS, ADD_OP},
    {T_MINUS, SUB_OP},
    {T_EQUAL_MINUS, SUB_OP},
    {T_STAR, MUL_OP},
    {T_EQUAL_STAR, MUL_OP},
    {T_SLASH, DIV_OP},
    {T_EQUAL_SLASH, DIV_OP},
    {T_PERCENT, MODULO_OP},
    {T_EQUAL_PERCENT, MODULO_OP},
    {T_CARET, POW_OP},
    {T_EQUAL_CARET, POW_OP},
    {T_AMPERSAND, BIT_AND_OP},
    {T_EQUAL_AMPERSAND, BIT_AND_OP},
    {T_PIPE, BIT_OR_OP},
    {T_EQUAL_PIPE, BIT_OR_OP},
    {T_DOUBLE_CARET, BIT_XOR_OP},
    {T_EQUAL_DOUBLE_CARET, BIT_XOR_OP},
    {T_DOUBLE_LANGLE, LSHIFT_OP},
    {T_EQUAL_DOUBLE_RANGLE, LSHIFT_OP},
    {T_DOUBLE_RANGLE, RSHIFT_OP},
    {T_EQUAL_DOUBLE_LANGLE, RSHIFT_OP},
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

