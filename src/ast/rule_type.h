#ifndef LOGOS_RULE_TYPE_H
#define LOGOS_RULE_TYPE_H

/**
 *
 */
typedef enum NumberType {
    N_BOOL_VALUE,
    N_SHORT_VALUE,
    N_USHORT_VALUE,
    N_INT_VALUE,
    N_UINT_VALUE,
    N_LONG_VALUE,
    N_ULONG_VALUE,
    N_FLOAT_VALUE,
    N_DOUBLE_VALUE,
} NumberType;

/**
 *
 */
typedef enum EntityType {
    E_OBJECT,
    E_INTERFACE,
    E_ENUM,
} EntityType;

/**
 *
 */
typedef enum ExprType {
    E_UNARY,
    E_BINARY,
} ExprType;
/**
 *
 */
typedef enum UnaryExprType {
    UE_INT,
    UE_FLOAT,
    UE_BOOL,
    UE_STRING,
    UE_IDENTIFIER,
    UE_METHOD_CALL,
    UE_COLLECTION,
} UnaryExprType;
/**
 *
 */
typedef enum StatementType {
    ST_LOCAL_DECLARATION,
    ST_IF_STATEMENT,
    ST_PATTERN_MATCHING,
    ST_PATTERN_MATCHING_EXPR,
    ST_ITERATION,
    ST_RETURN_STATEMENT,
    ST_BREAK_STATEMENT,
    ST_CONTINUE_STATEMENT,
    ST_ENUM_STATEMENT,
} StatementType;
/**
 *
 */
typedef enum PatternBodyType {
    PB_EXPR,
    PB_STMT_LIST,
} PatternBodyType;
/**
 *
 */
typedef enum IterationType {
    FL_WHILE,
    FL_INFINITE,
    FL_IN,
} IterationType;

#endif //LOGOS_RULE_TYPE_H
