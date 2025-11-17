#pragma once
#include "LgsDefinitions.h"
#include "data/LgsErrors.h"
#include <unordered_map>

enum LgsTokenType {
    T_LANGLE,
    T_RANGLE,
    T_LPAREN,
    T_RPAREN,
    T_LBRACE,
    T_RBRACE,
    T_LBRACK,
    T_RBRACK,
    T_DOT,
    T_COMMA,
    T_ARROW,
    T_DARROW,
    T_COLON,
    T_EQUAL,
    T_DOUBLE_EQUAL,
    T_NOT_EQUAL,
    T_GE,
    T_LE,
    T_QUEST_MARK,
    T_EXCLA_MARK,
    T_TRIPLE_DOT,
    T_DOUBLE_DOT,
    T_WALRUS,
    T_EQUAL_PLUS,
    T_EQUAL_MINUS,
    T_EQUAL_STAR,
    T_EQUAL_SLASH,
    T_EQUAL_PERCENT,
    T_EQUAL_DOLLAR,
    T_EQUAL_AMPERSAND,
    T_EQUAL_PIPE,
    T_EQUAL_CARET,
    T_EQUAL_DOUBLE_RANGLE,
    T_EQUAL_DOUBLE_LANGLE,
    T_INC,
    T_DEC,
    T_PLUS,
    T_MINUS,
    T_STAR,
    T_SLASH,
    T_SLIDER,
    T_PERCENT,
    T_AMPERSAND,
    T_PIPE,
    T_CARET,
    T_DOLLAR,
    T_DOUBLE_LANGLE,
    T_DOUBLE_RANGLE,
    T_TYPE,
    T_OBJECT,
    T_SINGLETON,
    T_SELF_INSTANCE,
    T_SELF_CLASS,
    T_INTERFACE,
    T_PUBLIC,
    T_IMPLEMENTS,
    T_CONST,
    T_ENUM,
    T_GO,
    T_DEFER,
    T_IO,
    T_OWNER,
    T_AND,
    T_OR,
    T_NOT,
    T_IN,
    T_IF,
    T_SWITCH,
    T_ELSE,
    T_THEN,
    T_WHILE,
    T_BREAK,
    T_CONTINUE,
    T_RETURN,
    T_IMPORT,
    T_VEC2,
    T_VEC3,
    T_VEC4,
    T_JSON,
    T_SET,
    T_FOR,
    T_FOR_I,
    T_FOR_IS_FIRST,
    T_FOR_IS_LAST,
    T_FOR_EVER,
    T_BOOL,
    T_INT,
    T_LONG,
    T_DOUBLE,
    T_HEX,
    T_FLOAT,
    T_NULL,
    T_IDENTIFIER,
    T_DOLLAR_IDENTIFIER,
    T_STRING,
    T_TAG,
    T_LINE_COMMENT,
    T_BLOCK_COMMENT,
    T_EOF,
    T_UNKNOWN,
};

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

const std::unordered_map<std::string, LgsTokenType> LGS_KEYWORDS = {
    {"type", T_TYPE},
    {"object", T_OBJECT},
    {"single", T_SINGLETON},
    {"self", T_SELF_INSTANCE},
    {"Self", T_SELF_CLASS},
    {"interface", T_INTERFACE},
    {"pub", T_PUBLIC},
    {"implements", T_IMPLEMENTS},
    {"const", T_CONST},
    {"enum", T_ENUM},
    {"go", T_GO},
    {"defer", T_DEFER},
    {"io", T_IO},
    {"owner", T_OWNER},
    {"and", T_AND},
    {"or", T_OR},
    {"not", T_NOT},
    {"in", T_IN},
    {"if", T_IF},
    {"switch", T_SWITCH},
    {"else", T_ELSE},
    {"then", T_THEN},
    {"while", T_WHILE},
    {"break", T_BREAK},
    {"continue", T_CONTINUE},
    {"return", T_RETURN},
    {"import", T_IMPORT},
    {"for", T_FOR},
    {"for.i", T_FOR_I},
    {"for.ever", T_FOR_EVER},
    {"for.isFirst", T_FOR_IS_FIRST},
    {"for.isLast", T_FOR_IS_LAST},
    {"Vec2", T_VEC2},
    {"Vec3", T_VEC3},
    {"Vec4", T_VEC4},
    {"Json", T_JSON},
    {"Set", T_SET},
    {"true", T_BOOL},
    {"false", T_BOOL},
    {LGS_NULL_LITERAL, T_NULL}
};

struct LgsBinOp {
    LgsBinOpType opType;
    std::string text;
};

struct LgsToken {
    LgsTokenType type = T_UNKNOWN;
    std::string lexeme = "";
    LgsLocation location;

    LgsToken() = default;
    LgsToken(const LgsTokenType type, const std::string& lexeme, const LgsLocation& location) : type(type), lexeme(lexeme), location(location) {}
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
