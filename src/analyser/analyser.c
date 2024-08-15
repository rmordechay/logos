#include <stdlib.h>
#include <string.h>
#include "analyser.h"
#include "types/object.h"
#include "types/method.h"

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
        obj->interfaces[i] = create_interface();
        obj->interfaces[i]->name = strdup(type_list->children[i]->value);
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
        obj->fields[i] = create_field();
        visit_field(child, obj->fields[i]);
    }
}

/**
 *
 */
void visit_field(Node *n_field, Field *field) {
    if (n_field->node_type != N_FIELD) return;
    Node *full_var_dec = n_field->children[0];
    field->variable->name = strdup(full_var_dec->children[1]->value);
    field->variable->type->name = strdup(full_var_dec->children[0]->value);
}

/**
 *
 */
void visit_methods_block_list(Node *n_methods_block_list, Object *obj) {
    if (n_methods_block_list->node_type != N_METHODS_BLOCK_LIST) return;
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
    if (n_methods_block->node_type != N_METHODS_BLOCK) return;
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
    if (n_method->node_type != N_METHOD) return;
    Node *n_method_signature = n_method->children[0];
    Node *n_method_header = n_method_signature->children[0];
    Node *var_declaration = n_method_header->children[0];
    Node *n_var = var_declaration->children[0];
    Node *n_type = var_declaration->children[1];
    method->identifier = create_variable();
    method->identifier->name = strdup(n_var->value);
    method->identifier->type = create_type();
    method->identifier->type->name = strdup(n_type->value);
}


