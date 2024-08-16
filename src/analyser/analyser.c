#include <stdlib.h>
#include <string.h>
#include "analyser.h"
#include "types/types.h"

void check_wrong_token(Node *actual, NodeType expected, char *text);

/**
 *
 */
void analyse_ast(Node *root) {
    visit_object_file(root);
}

/**
 *
 */
void visit_object_file(Node *n_object_file) {
    check_wrong_token(n_object_file, N_OBJECT_FILE, "OBJECT_FILE");
    Object *obj = create_object();
    for (int i = 0; i < n_object_file->child_len; i++) {
        Node *child = n_object_file->children[i];
        int nt = child->node_type;
        if (nt == N_FULL_TITLE) {
            visit_full_title(child, obj);
        } else if (nt == N_FIELDS_BLOCK) {
            visit_fields_block(child, obj);
        } else if (nt == N_METHODS_BLOCK_LIST) {
            visit_methods_block_list(child, obj);
        }
    }
    print_obj(obj);
    free_object(obj);
}

/**
 *
 */
void visit_full_title(Node *n_full_title, Object *obj) {
    check_wrong_token(n_full_title, N_FULL_TITLE, "FULL_TITLE");
    for (int i = 0; i < n_full_title->child_len; i++) {
        Node *child = n_full_title->children[i];
        int nt = child->node_type;
        if (nt == N_PRIMARY_TITLE) {
            visit_primary_title(child, obj);
        } else if (nt == N_SECONDARY_TITLE) {
            visit_secondary_title(child, obj);
        }
    }
}

/**
 *
 */
void visit_primary_title(Node *n_primary_title, Object *obj) {
    check_wrong_token(n_primary_title, N_PRIMARY_TITLE, "PRIMARY_TITLE");
    Node *identifier = n_primary_title->children[0];
    obj->name = strdup(identifier->value);
}

/**
 *
 */
void visit_secondary_title(Node *n_secondary_title, Object *obj) {
    check_wrong_token(n_secondary_title, N_SECONDARY_TITLE, "SECONDARY_TITLE");
    Node *type_list = n_secondary_title->children[0];
    obj->interfaces_len = type_list->child_len;
    obj->interfaces = malloc(obj->interfaces_len * sizeof(Interface*));
    for (int i = 0; i < type_list->child_len; i++) {
        obj->interfaces[i] = create_interface();
        obj->interfaces[i]->name = strdup(type_list->children[i]->value);
    }
}

/**
 *
 */
void visit_fields_block(Node *n_fields_block, Object *obj) {
    check_wrong_token(n_fields_block, N_FIELDS_BLOCK, "FIELDS_BLOCK");
    Node *field_list = n_fields_block->children[0];
    obj->fields_len = field_list->child_len;
    obj->fields = malloc(obj->fields_len * sizeof(Field*));
    for (int i = 0; i < obj->fields_len; i++) {
        Node *child = field_list->children[i];
        obj->fields[i] = create_field();
        visit_field(child, obj->fields[i]);
    }
}

/**
 *
 */
void visit_field(Node *n_field, Field *field) {
    check_wrong_token(n_field, N_FIELD, "FIELD");
    Node *full_var_dec = n_field->children[0];
    field->variable_dec->variable_name->name = strdup(full_var_dec->children[1]->value);
    field->variable_dec->type->name = strdup(full_var_dec->children[0]->value);
}

/**
 *
 */
void visit_methods_block_list(Node *n_methods_block_list, Object *obj) {
    check_wrong_token(n_methods_block_list, N_METHODS_BLOCK_LIST, "METHODS_BLOCK_LIST");
    obj->method_blocks_len = n_methods_block_list->child_len;
    obj->method_blocks = malloc(obj->method_blocks_len * sizeof(MethodBlock*));
    for (int i = 0; i < obj->method_blocks_len; i++) {
        Node *n_method_block = n_methods_block_list->children[i];
        Node *n_block_id = n_method_block->children[0];
        obj->method_blocks[i] = create_method_block();
        obj->method_blocks[i]->name = strdup(n_block_id->value);
        visit_methods_block(n_method_block, obj->method_blocks[i]);
    }
}

/**
 *
 */
void visit_methods_block(Node *n_methods_block, MethodBlock *method_block) {
    check_wrong_token(n_methods_block, N_METHODS_BLOCK, "METHODS_BLOCK");
    Node *n_methods_list = n_methods_block->children[1];
    method_block->methods_len = n_methods_list->child_len;
    method_block->methods = malloc(method_block->methods_len * sizeof(Method*));
    for (int i = 0; i < method_block->methods_len; i++) {
        Node *n_method = n_methods_list->children[i];
        method_block->methods[i] = create_method();
        visit_method(n_method, method_block->methods[i]);
    }
}

/**
 *
 */
void visit_method(Node *n_method, Method *method) {
    check_wrong_token(n_method, N_METHOD, "METHOD");
    visit_methods_signature(n_method->children[0], method);
    int has_stmts = n_method->child_len == 2;
    if (!has_stmts) return;
    Node *n_stmt_list = n_method->children[1];
    method->statements_len = n_stmt_list->child_len;
    method->statements = malloc(method->statements_len * sizeof(Statement*));
    visit_stmt_list(n_stmt_list, method);
}

/**
 *
 */
void visit_stmt_list(Node *n_stmt_list, Method *method) {
    check_wrong_token(n_stmt_list, N_STATEMENT_LIST, "STATEMENT_LIST");

    for (int i = 0; i < n_stmt_list->child_len; i++) {
        Node *n_stmt = n_stmt_list->children[i];
        method->statements[i] = create_statement();
        visit_statement(n_stmt);
    }
}

/**
 *
 */
void visit_statement(Node *n_stmt) {
    check_wrong_token(n_stmt, N_STATEMENT, "STATEMENT");
    Node *n = n_stmt->children[0];
    if (n->node_type == N_LOCAL_DECLARATION) {
        LocalDec *local_dec = create_local_declaration();
        visit_local_declaration(n, local_dec);
    }
}

/**
 *
 */
void visit_local_declaration(Node *n_local_declaration, LocalDec *local_dec) {
    check_wrong_token(n_local_declaration, N_LOCAL_DECLARATION, "LOCAL_DECLARATION");
    // Variable declaration
    Node *n_var_dec = n_local_declaration->children[0];
    local_dec->variable_dec = create_variable_declaration();
    visit_variable_declaration(n_var_dec, local_dec->variable_dec);
    // Expr
    Node *n_expr = n_local_declaration->children[1];
    local_dec->expr = create_expr();
    visit_expr(n_expr, local_dec->expr);
}

/**
 *
 */
void visit_expr(Node *n_expr, Expr *expr) {
    check_wrong_token(n_expr, N_EXPR, "EXPR");
    Node *n_left_expr = n_expr->children[0];
    NodeType node_type = n_left_expr->node_type;
    if (node_type == N_UNARY_EXPR) {
        UnaryExpr *unary_expr = create_unary_expr();
        expr->expr_type = UNARY;
        expr->e.unary_expr = unary_expr;
        return;
    }
    Node *n_right_expr = n_expr->children[1];
    BinaryExpr *binary_expr = create_binary_expr();
    expr->expr_type = BINARY;
    expr->e.binary_expr = binary_expr;
    if (node_type == N_ADD_EXPR) {
        binary_expr->op = ADD;
    } else if (node_type == N_SUB_EXPR) {
        binary_expr->op = SUB;
    } else if (node_type == N_MUL_EXPR) {
        binary_expr->op = MUL;
    } else if (node_type == N_DIV_EXPR) {
        binary_expr->op = DIV;
    }
}

/**
 *
 */
void visit_methods_signature(Node *n_method_signature, Method *method) {
    check_wrong_token(n_method_signature, N_METHOD_SIGNATURE, "METHOD_SIGNATURE");
    Node *var_declaration = n_method_signature->children[0]->children[0];
    Node *n_type = var_declaration->children[0];
    Node *n_var = var_declaration->children[1];
    method->var_dec = create_variable_declaration();
    method->var_dec->variable_name->name = strdup(n_var->value);
    method->var_dec->type = create_type();
    method->var_dec->type->name = strdup(n_type->value);
    int has_params = n_method_signature->child_len == 2;
    if (!has_params) return;
    visit_param_list(n_method_signature->children[1], method);
}

/**
 *
 */
void visit_param_list(Node *n_param_list, Method *method) {
    check_wrong_token(n_param_list, N_VAR_DEC_LIST, "N_VAR_DEC_LIST");
    method->params_len = n_param_list->child_len;
    method->params = malloc(method->params_len * sizeof(VariableDec*));
    for (int i = 0; i < n_param_list->child_len; i++) {
        Node *n_param = n_param_list->children[i];
        method->params[i] = create_variable_declaration();
        visit_variable_declaration(n_param, method->params[i]);
    }
}

/**
 *
 */
void visit_variable_declaration(Node *n_var_dec, VariableDec *param) {
    check_wrong_token(n_var_dec, N_VARIABLE_DECLARATION, "VARIABLE_DECLARATION");
    Node *type = n_var_dec->children[0];
    Node *name_variable = n_var_dec->children[1];
    param->variable_name->name = strdup(name_variable->value);
    param->type->name = strdup(type->value);
}

/**
 *
 */
void check_wrong_token(Node *actual, NodeType expected, char *text) {
    if (actual->node_type != expected) {
        fprintf(stderr, "%s : %s\n", get_node_string(actual->node_type), text);
        exit(1);
    }
}


