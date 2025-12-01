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

const auto ADD_OP = LgsBinOp{ADD, "+"};
const auto SUB_OP = LgsBinOp{SUB, "-"};
const auto MUL_OP = LgsBinOp{MUL, "*"};
const auto DIV_OP = LgsBinOp{DIV, "/"};
const auto MODULO_OP = LgsBinOp{MODULO, "%"};
const auto POW_OP = LgsBinOp{POW, "^"};
const auto BIT_AND_OP = LgsBinOp{BIT_AND, "&"};
const auto BIT_OR_OP = LgsBinOp{BIT_OR, "|"};
const auto BIT_XOR_OP = LgsBinOp{BIT_XOR, "$"};
const auto LSHIFT_OP = LgsBinOp{LSHIFT, "<<"};
const auto RSHIFT_OP = LgsBinOp{RSHIFT, ">>"};
const auto EQ_OP = LgsBinOp{EQ, "=="};
const auto NE_OP = LgsBinOp{NE, "!="};
const auto GT_OP = LgsBinOp{GT, ">"};
const auto LT_OP = LgsBinOp{LT, "<"};
const auto GE_OP = LgsBinOp{GE, "<="};
const auto LE_OP = LgsBinOp{LE, ">="};
const auto AND_OP = LgsBinOp{AND, "and"};
const auto OR_OP = LgsBinOp{OR, "or"};
const auto IN_OP = LgsBinOp{IN, "in"};
const auto CROSS_OP = LgsBinOp{CROSS, "x"};
const auto NOOP_OP = LgsBinOp{NOOP, ""};

const std::unordered_map<LgsTokenType, LgsBinOp> LGS_BINARY_OPS_DICT = {
    {T_PLUS, ADD_OP},
    {T_MINUS, SUB_OP},
    {T_STAR, MUL_OP},
    {T_SLASH, DIV_OP},
    {T_PERCENT, MODULO_OP},
    {T_CARET, POW_OP},
    {T_AMPERSAND, BIT_AND_OP},
    {T_PIPE, BIT_OR_OP},
    {T_DOLLAR, BIT_XOR_OP},
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
    {T_UNKNOWN, NOOP_OP},
};
