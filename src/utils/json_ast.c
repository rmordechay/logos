#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "ast/tree.h"

// Forward declarations
cJSON *create_identifier_json(Identifier *id);
cJSON *create_type_json(Type *type);
cJSON *create_type_list_json(TypeList *type_list);
cJSON *create_variable_declaration_json(VariableDec *var_dec);
cJSON *create_variable_declaration_list_json(VariableDeclarationList *var_dec_list);
cJSON *create_field_json(Field *field);
cJSON *create_field_list_json(FieldList *field_list);
cJSON *create_fields_block_json(FieldsBlock *fields_block);
cJSON *create_implements_block_json(ImplementsBlock *implements_block);
cJSON *create_expr_json(Expr *expr);
cJSON *create_binary_expr_json(BinaryExpr *binary_expr);
cJSON *create_unary_expr_json(UnaryExpr *unary_expr);
cJSON *create_local_declaration_json(LocalDeclaration *local_dec);
cJSON *create_statement_json(Statement *statement);
cJSON *create_statement_list_json(StatementList *statement_list);
cJSON *create_method_header_json(MethodHeader *method_header);
cJSON *create_method_signature_json(MethodSignature *method_signature);
cJSON *create_method_json(Method *method);
cJSON *create_methods_list_json(MethodsList *methods_list);
cJSON *create_methods_block_json(MethodsBlock *methods_block);
cJSON *create_methods_block_list_json(MethodsBlockList *methods_block_list);

/**
 *
 */
cJSON *create_object_file_json(ObjectFile *object_file) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "ObjectFile");
    cJSON_AddItemToObject(root, "id", create_identifier_json(object_file->id));
    cJSON_AddItemToObject(root, "fields_block", create_fields_block_json(object_file->fields_block));
    if (object_file->implements_block) {
        cJSON_AddItemToObject(root, "implements_block", create_implements_block_json(object_file->implements_block));
    }
    cJSON_AddItemToObject(root, "methods_block_list", create_methods_block_list_json(object_file->methods_block_list));
    return root;
}

/**
 *
 */
cJSON *create_identifier_json(Identifier *id) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "Identifier");
    cJSON_AddStringToObject(root, "name", id->name);
    return root;
}

/**
 *
 */
cJSON *create_type_json(Type *type) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "Type");
    cJSON_AddStringToObject(root, "name", type->name);
    return root;
}

/**
 *
 */
cJSON *create_type_list_json(TypeList *type_list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < type_list->count; i++) {
        cJSON_AddItemToArray(root, create_type_json(type_list->types[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_variable_declaration_json(VariableDec *var_dec) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "VariableDeclaration");
    cJSON_AddItemToObject(root, "type", create_type_json(var_dec->type));
    cJSON_AddItemToObject(root, "identifier", create_identifier_json(var_dec->identifier));
    return root;
}

/**
 *
 */
cJSON *create_variable_declaration_list_json(VariableDeclarationList *var_dec_list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < var_dec_list->count; i++) {
        cJSON_AddItemToArray(root, create_variable_declaration_json(var_dec_list->declarations[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_field_json(Field *field) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "Field");
    cJSON_AddItemToObject(root, "variable_declaration", create_variable_declaration_json(field->variable_declaration));
    if (field->type) {
        cJSON_AddItemToObject(root, "type", create_type_json(field->type));
    }
    return root;
}

/**
 *
 */
cJSON *create_field_list_json(FieldList *field_list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < field_list->count; i++) {
        cJSON_AddItemToArray(root, create_field_json(field_list->fields[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_fields_block_json(FieldsBlock *fields_block) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "FieldsBlock");
    cJSON_AddItemToObject(root, "field_list", create_field_list_json(fields_block->field_list));
    return root;
}

/**
 *
 */
cJSON *create_implements_block_json(ImplementsBlock *implements_block) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "ImplementsBlock");
    cJSON_AddItemToObject(root, "type_list", create_type_list_json(implements_block->type_list));
    return root;
}

/**
 *
 */
cJSON *create_expr_json(Expr *expr) {
    if (expr->unary_expr) {
        return create_unary_expr_json(expr->unary_expr);
    } else if (expr->binary_expr) {
        return create_binary_expr_json(expr->binary_expr);
    }
    return NULL;
}

/**
 *
 */
cJSON *create_binary_expr_json(BinaryExpr *binary_expr) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "BinaryExpr");
    cJSON_AddItemToObject(root, "left", create_expr_json(binary_expr->left));
    cJSON_AddItemToObject(root, "right", create_expr_json(binary_expr->right));
    char op_str[2] = {binary_expr->operator, '\0'};
    cJSON_AddStringToObject(root, "operator", op_str);
    return root;
}

/**
 *
 */
cJSON *create_unary_expr_json(UnaryExpr *unary_expr) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "UnaryExpr");
    if (unary_expr->integer_value) {
        cJSON_AddStringToObject(root, "integer_value", unary_expr->integer_value);
    } else if (unary_expr->float_value) {
        cJSON_AddStringToObject(root, "float_value", unary_expr->float_value);
    } else if (unary_expr->identifier) {
        cJSON_AddItemToObject(root, "identifier", create_identifier_json(unary_expr->identifier));
    }
    return root;
}

/**
 *
 */
cJSON *create_local_declaration_json(LocalDeclaration *local_dec) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "LocalDeclaration");
    cJSON_AddItemToObject(root, "variable_declaration",
                          create_variable_declaration_json(local_dec->variable_declaration));
    cJSON_AddItemToObject(root, "expr", create_expr_json(local_dec->expr));
    return root;
}

/**
 *
 */
cJSON *create_statement_json(Statement *statement) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "Statement");
    cJSON_AddItemToObject(root, "local_declaration", create_local_declaration_json(statement->local_declaration));
    return root;
}

/**
 *
 */
cJSON *create_statement_list_json(StatementList *statement_list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < statement_list->count; i++) {
        cJSON_AddItemToArray(root, create_statement_json(statement_list->statements[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_method_header_json(MethodHeader *method_header) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "MethodHeader");
    cJSON_AddItemToObject(root, "variable_declaration",
                          create_variable_declaration_json(method_header->variable_declaration));
    return root;
}

/**
 *
 */
cJSON *create_method_signature_json(MethodSignature *method_signature) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "MethodSignature");
    cJSON_AddItemToObject(root, "method_header", create_method_header_json(method_signature->method_header));
    if (method_signature->variable_declaration_list) {
        cJSON_AddItemToObject(root, "variable_declaration_list",
                              create_variable_declaration_list_json(method_signature->variable_declaration_list));
    }
    return root;
}

/**
 *
 */
cJSON *create_method_json(Method *method) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "Method");
    cJSON_AddItemToObject(root, "method_signature", create_method_signature_json(method->method_signature));
    if (method->statement_list) {
        cJSON_AddItemToObject(root, "statement_list", create_statement_list_json(method->statement_list));
    }
    return root;
}

/**
 *
 */
cJSON *create_methods_list_json(MethodsList *methods_list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < methods_list->count; i++) {
        cJSON_AddItemToArray(root, create_method_json(methods_list->methods[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_methods_block_json(MethodsBlock *methods_block) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type", "MethodsBlock");
    cJSON_AddItemToObject(root, "identifier", create_identifier_json(methods_block->identifier));
    cJSON_AddItemToObject(root, "methods_list", create_methods_list_json(methods_block->methods_list));
    return root;
}

/**
 *
 */
cJSON *create_methods_block_list_json(MethodsBlockList *methods_block_list) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < methods_block_list->count; i++) {
        cJSON_AddItemToArray(root, create_methods_block_json(methods_block_list->blocks[i]));
    }
    return root;
}

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