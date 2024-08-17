#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "ast/tree.h"
#include "parser.h"

void print_object_file_json(ObjectFile *object_file);
cJSON *create_identifier_json(Identifier *i);
cJSON *create_type_json(Type *t);
cJSON *create_type_list_json(TypeList *tl);
cJSON *create_variable_declaration_json(VariableDec *vc);
cJSON *create_variable_declaration_list_json(VarDecList *vdl);
cJSON *create_field_json(Field *f);
cJSON *create_field_list_json(FieldList *fl);
cJSON *create_fields_block_json(FieldsBlock *fb);
cJSON *create_implements_block_json(ImplementsBlock *ib);
cJSON *create_expr_json(Expr *e);
cJSON *create_binary_expr_json(BinaryExpr *be);
cJSON *create_unary_expr_json(UnaryExpr *ue);
cJSON *create_local_declaration_json(LocalDeclaration *lc);
cJSON *create_if_statement_json(IfStatement *is);
cJSON *create_if_block_json(IfBlock *ib);
cJSON *create_if_or_block_json(IfOrBlock *iob);
cJSON *create_if_or_block_list_json(IfOrBlockList *iobl);
cJSON *create_or_block_json(OrBlock *ob);
cJSON *create_statement_json(Statement *s);
cJSON *create_statement_list_json(StatementList *sl);
cJSON *create_method_header_json(MethodHeader *mh);
cJSON *create_method_signature_json(MethodSignature *ms);
cJSON *create_method_json(Method *m);
cJSON *create_methods_list_json(MethodsList *ml);
cJSON *create_methods_block_json(MethodsBlock *mb);
cJSON *create_methods_block_list_json(MethodsBlockList *mbl);
cJSON *create_object_file_json(ObjectFile *of);

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
cJSON *create_object_file_json(ObjectFile *of) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "kind", "ObjectFile");
    cJSON_AddItemToObject(root, "id", create_identifier_json(of->id));
    cJSON_AddItemToObject(root, "fields_block", create_fields_block_json(of->fields_block));
    if (of->implements_block) {
        cJSON_AddItemToObject(root, "implements_block", create_implements_block_json(of->implements_block));
    }
    cJSON_AddItemToObject(root, "methods_block_list", create_methods_block_list_json(of->methods_block_list));
    return root;
}

/**
 *
 */
cJSON *create_identifier_json(Identifier *i) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "name", i->name);
    return root;
}

/**
 *
 */
cJSON *create_type_json(Type *t) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "name", t->name);
    return root;
}

/**
 *
 */
cJSON *create_type_list_json(TypeList *tl) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < tl->count; i++) {
        cJSON_AddItemToArray(root, create_type_json(tl->types[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_variable_declaration_json(VariableDec *vc) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type", create_type_json(vc->type));
    cJSON_AddItemToObject(root, "identifier", create_identifier_json(vc->identifier));
    return root;
}

/**
 *
 */
cJSON *create_variable_declaration_list_json(VarDecList *vdl) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < vdl->count; i++) {
        cJSON_AddItemToArray(root, create_variable_declaration_json(vdl->declarations[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_field_json(Field *f) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "variable_declaration", create_variable_declaration_json(f->variable_declaration));
    if (f->implements) {
    }
    return root;
}

/**
 *
 */
cJSON *create_field_list_json(FieldList *fl) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < fl->count; i++) {
        cJSON_AddItemToArray(root, create_field_json(fl->fields[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_fields_block_json(FieldsBlock *fb) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "field_list", create_field_list_json(fb->field_list));
    return root;
}

/**
 *
 */
cJSON *create_implements_block_json(ImplementsBlock *ib) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "type_list", create_type_list_json(ib->type_list));
    return root;
}

/**
 *
 */
cJSON *create_expr_json(Expr *e) {
    if (e->type == UNARY) {
        return create_unary_expr_json(e->unary_expr);
    } else if (e->type == BINARY) {
        return create_binary_expr_json(e->binary_expr);
    }
    return NULL;
}

/**
 *
 */
cJSON *create_unary_expr_json(UnaryExpr *ue) {
    cJSON *root = cJSON_CreateObject();
    if (ue->type == INTEGER) {
        cJSON_AddStringToObject(root, "integer_value", ue->integer_value);
    } else if (ue->type == FLOAT) {
        cJSON_AddStringToObject(root, "float_value", ue->float_value);
    } else if (ue->type == IDENTIFIER) {
        cJSON_AddItemToObject(root, "identifier", create_identifier_json(ue->identifier));
    }
    return root;
}

/**
 *
 */
cJSON *create_binary_expr_json(BinaryExpr *be) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "left", create_expr_json(be->left));
    cJSON_AddItemToObject(root, "right", create_expr_json(be->right));
    char op_str[2] = {be->operator, '\0'};
    cJSON_AddStringToObject(root, "operator", op_str);
    return root;
}

/**
 *
 */
cJSON *create_local_declaration_json(LocalDeclaration *lc) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "variable_declaration",create_variable_declaration_json(lc->variable_declaration));
    cJSON_AddItemToObject(root, "expr", create_expr_json(lc->expr));
    return root;
}

/**
 *
 */
cJSON *create_statement_json(Statement *s) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "local_declaration", create_local_declaration_json(s->local_declaration));
    return root;
}

/**
 *
 */
cJSON *create_statement_list_json(StatementList *sl) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < sl->count; i++) {
        cJSON_AddItemToArray(root, create_statement_json(sl->statements[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_method_header_json(MethodHeader *mh) {
    cJSON *root = cJSON_CreateObject();
    cJSON *var_dec = create_variable_declaration_json(mh->variable_declaration);
    cJSON_AddItemToObject(root, "variable_declaration",var_dec);
    return root;
}

/**
 *
 */
cJSON *create_method_signature_json(MethodSignature *ms) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "method_header", create_method_header_json(ms->method_header));
    if (ms->variable_declaration_list) {
        cJSON *var_dec_list = create_variable_declaration_list_json(ms->variable_declaration_list);
        cJSON_AddItemToObject(root, "variable_declaration_list", var_dec_list);
    }
    return root;
}

/**
 *
 */
cJSON *create_method_json(Method *m) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "method_signature", create_method_signature_json(m->method_signature));
    if (m->statement_list) {
        cJSON_AddItemToObject(root, "statement_list", create_statement_list_json(m->statement_list));
    }
    return root;
}

/**
 *
 */
cJSON *create_methods_list_json(MethodsList *ml) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < ml->count; i++) {
        cJSON_AddItemToArray(root, create_method_json(ml->methods[i]));
    }
    return root;
}

/**
 *
 */
cJSON *create_methods_block_json(MethodsBlock *mb) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "identifier", create_identifier_json(mb->identifier));
    cJSON_AddItemToObject(root, "methods_list", create_methods_list_json(mb->methods_list));
    return root;
}

/**
 *
 */
cJSON *create_methods_block_list_json(MethodsBlockList *mbl) {
    cJSON *root = cJSON_CreateArray();
    for (int i = 0; i < mbl->count; i++) {
        cJSON_AddItemToArray(root, create_methods_block_json(mbl->blocks[i]));
    }
    return root;
}
