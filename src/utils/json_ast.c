#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "ast/tree.h"
#include "parser.h"

void print_entity_json(Entity *entity);
cJSON *create_identifier_json(Identifier *obj);
cJSON *create_type_json(Type *obj);
cJSON *create_type_list_json(TypeList *list);
cJSON *create_variable_declaration_json(VariableDec *obj);
cJSON *create_variable_declaration_list_json(VariableDecList *list);
cJSON *create_field_json(ObjectField *obj);
cJSON *create_field_list_json(ObjFieldList *obj);
cJSON *create_implements_block_json(ImplementsBlock *obj);
cJSON *create_expr_json(Expr *obj);
cJSON *create_expr_list_json(ExprList *list);
cJSON *create_binary_expr_json(BinaryExpr *obj);
cJSON *create_unary_expr_json(UnaryExpr *obj);
cJSON *create_local_declaration_json(LocalDeclaration *obj);
cJSON *create_if_statement_json(IfStatement *obj);
cJSON *create_if_block_json(IfBlock *obj);
cJSON *create_if_or_block_json(IfOrBlock *obj);
cJSON *create_if_or_block_list_json(IfOrBlockList *list);
cJSON *create_or_block_json(OrBlock *obj);
cJSON *create_iteration_json(Iteration *obj);
cJSON *create_for_in_loop_json(ForInLoop *obj);
cJSON *create_while_loop_json(WhileLoop *obj);
cJSON *create_pattern_matching_json(PatternMatching *obj);
cJSON *create_pattern_matching_expr_json(PatternMatchingExpr *obj);
cJSON *create_pattern_json(Pattern *obj);
cJSON *create_pattern_list_json(PatternList *list);
cJSON *create_statement_json(Statement *obj);
cJSON *create_statement_list_json(StatementList *list);
cJSON *create_method_signature_json(MethodSignature *obj);
cJSON *create_method_json(ObjMethod *obj);
cJSON *create_methods_list_json(ObjMethodsList *list);
cJSON *create_methods_block_json(ObjMethodsBlock *obj);
cJSON *create_methods_block_list_json(ObjMethodsBlockList *list);
cJSON *create_object_file_json(ObjEntity *obj);


/**
 *
 */
cJSON *create_object_file_json(ObjEntity *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "kind", "ObjEntity");
    cJSON_AddItemToObject(root, "id", create_type_json(obj->id));
    cJSON_AddItemToObject(root, "field_list", create_field_list_json(obj->field_list));
    if (obj->implements_block) {
        cJSON_AddItemToObject(root, "implements_block", create_implements_block_json(obj->implements_block));
    }
    cJSON_AddItemToObject(root, "methods_block_list", create_methods_block_list_json(obj->methods_block_list));
    char *json_str = cJSON_Print(root);
    printf("%s\n", json_str);
    free(json_str);
    return root;
}

/**
 *
 */
cJSON *create_identifier_json(Identifier *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "enums", obj->name);
    return root;
}

/**
 *
 */
cJSON *create_type_json(Type *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "enums", obj->name);
    return root;
}

/**
 *
 */
cJSON *create_type_list_json(TypeList *list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < list->count; i++) {
        cJSON_AddItemToArray(root, create_type_json(list->types[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_variable_declaration_json(VariableDec *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "const_var_list", create_type_json(obj->type));
    cJSON_AddItemToObject(root, "identifier", create_identifier_json(obj->identifier));
    return root;
}

/**
 *
 */
cJSON *create_variable_declaration_list_json(VariableDecList *list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < list->count; i++) {
        cJSON_AddItemToArray(root, create_variable_declaration_json(list->var_declarations[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_field_json(ObjectField *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "method_variable", create_variable_declaration_json(obj->variable_declaration));
    if (obj->implements) {
    }
    return root;
}

/**
 *
 */
cJSON *create_field_list_json(ObjFieldList *obj) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < obj->count; i++) {
        cJSON_AddItemToArray(root, create_field_json(obj->fields[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_implements_block_json(ImplementsBlock *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type_list", create_type_list_json(obj->type_list));
    return root;
}

/**
 *
 */
cJSON *create_expr_json(Expr *obj) {
    if (obj->type == E_UNARY) {
        return create_unary_expr_json(obj->unary_expr);
    } else if (obj->type == E_BINARY) {
        return create_binary_expr_json(obj->binary_expr);
    }
    return NULL;
}

/**
 *
 */
cJSON *create_expr_list_json(ExprList *list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < list->count; ++i) {
        cJSON_AddItemToObject(root, "expr_list", create_expr_json(list->exprs[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_unary_expr_json(UnaryExpr *obj) {
    cJSON *root = cJSON_CreateObject();
    switch (obj->type) {
        case UE_INT:
            cJSON_AddStringToObject(root, "integer_value", obj->integer_value);
            break;
        case UE_FLOAT:
            cJSON_AddStringToObject(root, "float_value", obj->float_value);
            break;
        case UE_BOOL:
            cJSON_AddBoolToObject(root, "bool", obj->boolean);
            break;
        case UE_STRING:
            cJSON_AddStringToObject(root, "string", obj->string);
            break;
        case UE_IDENTIFIER:
            cJSON_AddItemToObject(root, "identifier", create_identifier_json(obj->identifier));
            break;
        case UE_METHOD_CALL:
        case UE_COLLECTION:
            break;
    }
    return root;
}

/**
 *
 */
cJSON *create_binary_expr_json(BinaryExpr *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "left", create_expr_json(obj->left));
    cJSON_AddItemToObject(root, "right", create_expr_json(obj->right));
    char op_str[2] = {obj->operator, '\0'};
    cJSON_AddStringToObject(root, "operator", op_str);
    return root;
}

/**
 *
 */
cJSON *create_local_declaration_json(LocalDeclaration *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "const_var_list",create_type_json(obj->type));
    cJSON_AddItemToObject(root, "identifier",create_identifier_json(obj->identifier));
    cJSON_AddItemToObject(root, "expr", create_expr_json(obj->expr));
    return root;
}

/**
 *
 */
cJSON *create_if_statement_json(IfStatement *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "if_block", create_if_block_json(obj->if_block));
    if (obj->if_or_block_list) {
        cJSON_AddItemToObject(root, "if_or_block_list", create_if_or_block_list_json(obj->if_or_block_list));
    }
    if (obj->or_block) {
        cJSON_AddItemToObject(root, "or_block", create_or_block_json(obj->or_block));
    }
    return root;
}

/**
 *
 */
cJSON *create_if_block_json(IfBlock *obj) {
    cJSON *root = cJSON_CreateObject();
    if (obj->statement_list) {
        cJSON_AddItemToObject(root, "statement_list", create_statement_list_json(obj->statement_list));
    }
    cJSON_AddItemToObject(root, "expr_list", create_expr_json(obj->expr));
    return root;
}

/**
 *
 */
cJSON *create_if_or_block_json(IfOrBlock *obj) {
    cJSON *root = cJSON_CreateObject();
    if (obj->statement_list) {
        cJSON_AddItemToObject(root, "statement_list", create_statement_list_json(obj->statement_list));
    }
    cJSON_AddItemToObject(root, "expr_list", create_expr_json(obj->expr));
    return root;
}

/**
 *
 */
cJSON *create_if_or_block_list_json(IfOrBlockList *list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < list->count; i++) {
        cJSON_AddItemToArray(root, create_if_or_block_json(list->if_or_blocks[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_or_block_json(OrBlock *obj) {
    cJSON *root = cJSON_CreateObject();
    if (obj->statement_list) {
        cJSON_AddItemToObject(root, "statement_list", create_statement_list_json(obj->statement_list));
    }
    return root;
}

/**
 *
 */
cJSON *create_iteration_json(Iteration *obj) {
    cJSON *root = cJSON_CreateObject();
    switch (obj->type) {
        case FL_WHILE:
            cJSON_AddItemToObject(root, "while_loop",create_while_loop_json(obj->while_loop));
            break;
        case FL_INFINITE:
            cJSON_AddItemToObject(root, "infinite_loop",cJSON_CreateObject());
            break;
        case FL_IN:
            cJSON_AddItemToObject(root, "for_in_loop",create_for_in_loop_json(obj->for_in_loop));
            break;
    }
    return root;
}

/**
 *
 */
cJSON *create_for_in_loop_json(ForInLoop *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "expr_list",create_expr_json(obj->in_expr));
    cJSON_AddItemToObject(root, "expr_list",create_expr_list_json(obj->expr_list));
    return root;
}

/**
 *
 */
cJSON *create_while_loop_json(WhileLoop *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "expr_list",create_expr_list_json(obj->expr_list));
    return root;
}


/**
 *
 */
cJSON *create_pattern_matching_json(PatternMatching *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "pattern_list",create_pattern_list_json(obj->pattern_list));
    return root;
}

/**
 *
 */
cJSON *create_pattern_matching_expr_json(PatternMatchingExpr *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "expr_list",create_expr_json(obj->expr));
    cJSON_AddItemToObject(root, "pattern_list",create_pattern_list_json(obj->pattern_list));
    return root;
}

/**
 *
 */
cJSON *create_pattern_json(Pattern *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "expr_list",create_expr_json(obj->condition));
    switch (obj->type) {
        case PB_EXPR:
            cJSON_AddItemToObject(root, "expr_list",create_expr_json(obj->condition));
            break;
        case PB_STMT_LIST:
            cJSON_AddItemToObject(root, "statement_list",create_statement_list_json(obj->statement_list));
            break;
    }
    return root;
}

/**
 *
 */
cJSON *create_pattern_list_json(PatternList *list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < list->count; i++) {
        cJSON_AddItemToArray(root, create_pattern_json(list->patterns[i]));
    }
    return root;
}


/**
 *
 */
cJSON *create_statement_json(Statement *obj) {
    cJSON *root = cJSON_CreateObject();
    switch (obj->type) {
        case ST_LOCAL_DECLARATION:
            cJSON_AddItemToObject(root, "local_declaration", create_local_declaration_json(obj->local_declaration));
            break;
        case ST_IF_STATEMENT:
            cJSON_AddItemToObject(root, "if_statement", create_if_statement_json(obj->if_statement));
            break;
        case ST_PATTERN_MATCHING:
            cJSON_AddItemToObject(root, "pattern_matching", create_pattern_matching_json(obj->pattern_matching));
            break;
        case ST_PATTERN_MATCHING_EXPR:
            cJSON_AddItemToObject(root, "pattern_matching_expr", create_pattern_matching_expr_json(obj->pattern_matching_expr));
            break;
        case ST_ITERATION:
            cJSON_AddItemToObject(root, "for_loop", create_iteration_json(obj->iteration));
            break;
        case ST_RETURN_STATEMENT:
            cJSON_AddItemToObject(root, "return_statement_expr_list", create_expr_list_json(obj->return_statement->expr_list));
            break;
        case ST_BREAK_STATEMENT:
        case ST_CONTINUE_STATEMENT:
            break;
        case ST_ENUM_STATEMENT:
            break;
    }
    return root;
}

/**
 *
 */
cJSON *create_statement_list_json(StatementList *list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < list->count; i++) {
        cJSON_AddItemToArray(root, create_statement_json(list->statements[i]));
    }
    return root;
}


/**
 *
 */
cJSON *create_method_signature_json(MethodSignature *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "method_variable", create_variable_declaration_json(obj->method_variable));
    if (obj->param_list) {
        cJSON *var_dec_list = create_variable_declaration_list_json(obj->param_list);
        cJSON_AddItemToObject(root, "param_list", var_dec_list);
    }
    return root;
}

/**
 *
 */
cJSON *create_method_json(ObjMethod *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "method_signature", create_method_signature_json(obj->method_signature));
    if (obj->statement_list) {
        cJSON_AddItemToObject(root, "statement_list", create_statement_list_json(obj->statement_list));
    }
    return root;
}

/**
 *
 */
cJSON *create_methods_list_json(ObjMethodsList *list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < list->count; i++) {
        cJSON_AddItemToArray(root, create_method_json(list->methods[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_methods_block_json(ObjMethodsBlock *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "identifier", create_type_json(obj->identifier));
    cJSON_AddItemToObject(root, "methods_list", create_methods_list_json(obj->methods_list));
    return root;
}

/**
 *
 */
cJSON *create_methods_block_list_json(ObjMethodsBlockList *list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < list->count; i++) {
        cJSON_AddItemToArray(root, create_methods_block_json(list->blocks[i]));
    }
    return root;
}
