#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "ast/tree.h"
#include "parser.h"

void print_object_file_json(ObjectFile *object_file);
cJSON *create_identifier_json(Identifier *obj);
cJSON *create_type_json(Type *obj);
cJSON *create_type_list_json(TypeList *list);
cJSON *create_variable_declaration_json(VariableDec *obj);
cJSON *create_variable_declaration_list_json(VarDecList *list);
cJSON *create_field_json(Field *obj);
cJSON *create_field_list_json(FieldList *obj);
cJSON *create_fields_block_json(FieldsBlock *obj);
cJSON *create_implements_block_json(ImplementsBlock *obj);
cJSON *create_expr_json(Expr *obj);
cJSON *create_binary_expr_json(BinaryExpr *obj);
cJSON *create_unary_expr_json(UnaryExpr *obj);
cJSON *create_local_declaration_json(LocalDeclaration *obj);
cJSON *create_if_statement_json(IfStatement *obj);
cJSON *create_if_block_json(IfBlock *obj);
cJSON *create_if_or_block_json(IfOrBlock *obj);
cJSON *create_if_or_block_list_json(IfOrBlockList *list);
cJSON *create_or_block_json(OrBlock *obj);
cJSON *create_pattern_matching_json(PatternMatching *obj);
cJSON *create_pattern_matching_expr_json(PatternMatchingExpr *obj);
cJSON *create_pattern_json(Pattern *obj);
cJSON *create_pattern_list_json(PatternList *list);
cJSON *create_statement_json(Statement *obj);
cJSON *create_statement_list_json(StatementList *list);
cJSON *create_method_header_json(MethodHeader *obj);
cJSON *create_method_signature_json(MethodSignature *obj);
cJSON *create_method_json(Method *obj);
cJSON *create_methods_list_json(MethodsList *list);
cJSON *create_methods_block_json(MethodsBlock *obj);
cJSON *create_methods_block_list_json(MethodsBlockList *list);
cJSON *create_object_file_json(ObjectFile *obj);

/**
 *
 */
void print_object_file_json(ObjectFile *object_file) {
    cJSON *json = create_object_file_json(object_file);
    char *json_string = cJSON_Print(json);
    printf("%s\n", json_string);
    free(json_string);
    cJSON_Delete(json);
}

/**
 *
 */
cJSON *create_object_file_json(ObjectFile *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "kind", "ObjectFile");
    cJSON_AddItemToObject(root, "id", create_identifier_json(obj->id));
    cJSON_AddItemToObject(root, "fields_block", create_fields_block_json(obj->fields_block));
    if (obj->implements_block) {
        cJSON_AddItemToObject(root, "implements_block", create_implements_block_json(obj->implements_block));
    }
    cJSON_AddItemToObject(root, "methods_block_list", create_methods_block_list_json(obj->methods_block_list));
    return root;
}

/**
 *
 */
cJSON *create_identifier_json(Identifier *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "name", obj->name);
    return root;
}

/**
 *
 */
cJSON *create_type_json(Type *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "name", obj->name);
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
    cJSON_AddItemToObject(root, "type", create_type_json(obj->type));
    cJSON_AddItemToObject(root, "identifier", create_identifier_json(obj->identifier));
    return root;
}

/**
 *
 */
cJSON *create_variable_declaration_list_json(VarDecList *list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < list->count; i++) {
        cJSON_AddItemToArray(root, create_variable_declaration_json(list->declarations[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_field_json(Field *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "variable_declaration", create_variable_declaration_json(obj->variable_declaration));
    if (obj->implements) {
    }
    return root;
}

/**
 *
 */
cJSON *create_field_list_json(FieldList *obj) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < obj->count; i++) {
        cJSON_AddItemToArray(root, create_field_json(obj->fields[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_fields_block_json(FieldsBlock *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "field_list", create_field_list_json(obj->field_list));
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
    if (obj->type == UNARY) {
        return create_unary_expr_json(obj->unary_expr);
    } else if (obj->type == BINARY) {
        return create_binary_expr_json(obj->binary_expr);
    }
    return NULL;
}

/**
 *
 */
cJSON *create_unary_expr_json(UnaryExpr *obj) {
    cJSON *root = cJSON_CreateObject();
    if (obj->type == INTEGER) {
        cJSON_AddStringToObject(root, "integer_value", obj->integer_value);
    } else if (obj->type == FLOAT) {
        cJSON_AddStringToObject(root, "float_value", obj->float_value);
    } else if (obj->type == IDENTIFIER) {
        cJSON_AddItemToObject(root, "identifier", create_identifier_json(obj->identifier));
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
    cJSON_AddItemToObject(root, "variable_declaration",create_variable_declaration_json(obj->variable_declaration));
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
    cJSON_AddItemToObject(root, "expr", create_expr_json(obj->expr));
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
    cJSON_AddItemToObject(root, "expr", create_expr_json(obj->expr));
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
    cJSON_AddItemToObject(root, "expr",create_expr_json(obj->expr));
    cJSON_AddItemToObject(root, "pattern_list",create_pattern_list_json(obj->pattern_list));
    return root;
}

/**
 *
 */
cJSON *create_pattern_json(Pattern *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "expr",create_expr_json(obj->condition));
    switch (obj->type) {
        case EXPR_BODY:
            cJSON_AddItemToObject(root, "expr",create_expr_json(obj->condition));
            break;
        case STMT_LIST_BODY:
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
        case LOCAL_DECLARATION:
            cJSON_AddItemToObject(root, "local_declaration", create_local_declaration_json(obj->local_declaration));
            break;
        case IF_STMT:
            cJSON_AddItemToObject(root, "if_statement", create_if_statement_json(obj->if_statement));
            break;
        case PATTERN_MATCHING:
            cJSON_AddItemToObject(root, "pattern_matching", create_pattern_matching_json(obj->if_statement));
            break;
        case PATTERN_MATCHING_EXPR:
            cJSON_AddItemToObject(root, "pattern_matching_expr", create_pattern_matching_expr_json(obj->if_statement));
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
cJSON *create_method_header_json(MethodHeader *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON *var_dec = create_variable_declaration_json(obj->variable_declaration);
    cJSON_AddItemToObject(root, "variable_declaration",var_dec);
    return root;
}

/**
 *
 */
cJSON *create_method_signature_json(MethodSignature *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "method_header", create_method_header_json(obj->method_header));
    if (obj->variable_declaration_list) {
        cJSON *var_dec_list = create_variable_declaration_list_json(obj->variable_declaration_list);
        cJSON_AddItemToObject(root, "variable_declaration_list", var_dec_list);
    }
    return root;
}

/**
 *
 */
cJSON *create_method_json(Method *obj) {
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
cJSON *create_methods_list_json(MethodsList *list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < list->count; i++) {
        cJSON_AddItemToArray(root, create_method_json(list->methods[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_methods_block_json(MethodsBlock *obj) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "identifier", create_identifier_json(obj->identifier));
    cJSON_AddItemToObject(root, "methods_list", create_methods_list_json(obj->methods_list));
    return root;
}

/**
 *
 */
cJSON *create_methods_block_list_json(MethodsBlockList *list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < list->count; i++) {
        cJSON_AddItemToArray(root, create_methods_block_json(list->blocks[i]));
    }
    return root;
}
