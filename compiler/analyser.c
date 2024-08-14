#include <stdlib.h>
#include "analyser.h"

/**
 *
 */
void analyse_ast(ASTNode *root) {
    visit_object_file(root);
}

/**
 *
 */
void visit_object_file(ASTNode *object_file) {
    Object *obj = create_object();
    if (object_file->node_type != N_OBJECT_FILE) return;
    for (int i = 0; i < object_file->child_count; i++) {
        ASTNode *child = object_file->children[i];
        int nt = child->node_type;
        if (nt == N_FULL_TITLE) {
            visit_full_title(child, obj);
        } else if (nt == N_FIELDS_BLOCK) {
            visit_fields_block(child, obj);
        } else if (nt == N_METHODS_BLOCK_LIST) {
            visit_methods_block_list(child, obj);
        }
    }
    free(obj);
}

/**
 *
 */
void visit_full_title(ASTNode *full_title, Object *obj) {
    if (full_title->node_type != N_FULL_TITLE) return;
    for (int i = 0; i < full_title->child_count; i++) {
        ASTNode *child = full_title->children[i];
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
void visit_primary_title(ASTNode *primary_title, Object *obj) {
    if (primary_title->node_type != N_PRIMARY_TITLE) return;
    ASTNode *identifier = primary_title->children[0];
    obj->name = identifier->value;
}

/**
 *
 */
void visit_secondary_title(ASTNode *secondary_title, Object *obj) {
    if (secondary_title->node_type != N_SECONDARY_TITLE) return;
    obj->implements_count = secondary_title->child_count;
    ASTNode *type_list = secondary_title->children[0];
    for (int i = 0; i < type_list->child_count; i++) {
        ASTNode *child = type_list->children[i];
        add_to_string(&obj->implements, child->value);
    }
}

/**
 *
 */
void visit_methods_block_list(ASTNode *methods_block_list, Object *obj) {

}

/**
 *
 */
void visit_fields_block(ASTNode *fields_block, Object *obj) {

}

/**
 *
 */
Object *create_object() {
    Object *obj = malloc(sizeof(Object));
    obj->name = NULL;
    obj->implements_count = 0;
    init_string_list(&obj->implements, 2);
    return obj;
}

/**
 *
 */
void visit_type_list(ASTNode *type_list, Object *obj) {

}

