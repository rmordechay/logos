#include <stdlib.h>
#include <string.h>
#include "analyser.h"
#include "types/object.h"
#include <stdio.h>

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
    if (n_object_file->node_type != N_OBJECT_FILE) return;
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
    if (n_full_title->node_type != N_FULL_TITLE) return;
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
    if (n_primary_title->node_type != N_PRIMARY_TITLE) return;
    Node *identifier = n_primary_title->children[0];
    obj->name = strdup(identifier->value);
}

/**
 *
 */
void visit_secondary_title(Node *n_secondary_title, Object *obj) {
    if (n_secondary_title->node_type != N_SECONDARY_TITLE) return;
    Node *type_list = n_secondary_title->children[0];
    obj->interfaces_len = type_list->child_len;
    obj->interfaces = malloc(obj->interfaces_len * sizeof(Interface*));
    for (int i = 0; i < type_list->child_len; i++) {
        Node *type = type_list->children[i];
        obj->interfaces[i] = malloc(sizeof(Interface));
        obj->interfaces[i]->name = strdup(type->value);
    }
}

/**
 *
 */
void visit_fields_block(Node *n_fields_block, Object *obj) {
    if (n_fields_block->node_type != N_FIELDS_BLOCK) return;
    Node *field_list = n_fields_block->children[0];
    obj->fields_len = field_list->child_len;
    obj->fields = malloc(obj->fields_len * sizeof(Field*));
    for (int i = 0; i < obj->fields_len; i++) {
        Node *child = field_list->children[i];
        obj->fields[i] = malloc(sizeof(Field));
        visit_field(child, obj, obj->fields[i]);
    }
}

/**
 *
 */
void visit_field(Node *n_field, Object *obj, Field *field) {
    if (n_field->node_type != N_FIELD) return;
    Node *full_var_dec = n_field->children[0];
    visit_var_declaration(full_var_dec, obj, field);
    if (n_field->child_len == 2) {
        field->Interface = NULL;
    }
}

/**
 *
 */
void visit_var_declaration(Node *n_var_declaration, Object *obj, Field *field) {
    if (n_var_declaration->node_type != N_VARIABLE_DECLARATION) return;
    field->variable = malloc(sizeof(Variable));
    field->type = malloc(sizeof(Type));
    visit_type(n_var_declaration->children[0], field->type);
    visit_variable(n_var_declaration->children[1], field->variable);
}

/**
 *
 */
void visit_variable(Node *n_variable, Variable *variable) {
    if (n_variable->node_type != N_IDENTIFIER) return;
    variable->name = n_variable->value;
}

/**
 *
 */
void visit_type(Node *n_type, Type *type) {
    if (n_type->node_type != N_TYPE) return;
    type->name = n_type->value;
}

/**
 *
 */
void visit_methods_block_list(Node *n_methods_block_list, Object *obj) {

}


