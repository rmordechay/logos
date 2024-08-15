#include <stdlib.h>
#include <string.h>
#include "analyser.h"
#include "types/object.h"

/**
 *
 */
void analyse_ast(Node *root) {
    visit_object_file(root);
}

/**
 *
 */
void visit_object_file(Node *object_file) {
    if (object_file->node_type != N_OBJECT_FILE) return;
    Object *obj = create_object();
    for (int i = 0; i < object_file->child_len; i++) {
        Node *child = object_file->children[i];
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
void visit_full_title(Node *full_title, Object *obj) {
    if (full_title->node_type != N_FULL_TITLE) return;
    for (int i = 0; i < full_title->child_len; i++) {
        Node *child = full_title->children[i];
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
void visit_primary_title(Node *primary_title, Object *obj) {
    if (primary_title->node_type != N_PRIMARY_TITLE) return;
    Node *identifier = primary_title->children[0];
    obj->name = strdup(identifier->value);
}

/**
 *
 */
void visit_secondary_title(Node *secondary_title, Object *obj) {
    if (secondary_title->node_type != N_SECONDARY_TITLE) return;
    Node *type_list = secondary_title->children[0];
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
void visit_fields_block(Node *fields_block, Object *obj) {
    if (fields_block->node_type != N_SECONDARY_TITLE) return;
    Node *node = fields_block->children[0];
}

/**
 *
 */
void visit_methods_block_list(Node *methods_block_list, Object *obj) {

}

/**
 *
 */
void visit_type_list(Node *type_list, Object *obj) {

}

