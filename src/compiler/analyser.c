#include <stdlib.h>
#include <string.h>
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
Object *create_object(FileType file_type) {
    Object *obj = malloc(sizeof(Object));
    obj->name = NULL;
    obj->fileType = file_type;
    obj->interfaces = NULL;
    obj->interfaces_len = 0;
    return obj;
}

/**
 *
 */
void visit_object_file(ASTNode *object_file) {
    Object *obj = create_object(OBJECT_FILE);
    if (object_file->node_type != N_OBJECT_FILE) return;
    for (int i = 0; i < object_file->child_len; i++) {
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
//    printf("%s\n", obj->name);
    for (size_t i = 0; i < obj->interfaces_len; i++) {
        printf("%s\n", obj->interfaces[i]->name);
    }
    free_object(obj);
}

/**
 *
 */
void visit_full_title(ASTNode *full_title, Object *obj) {
    if (full_title->node_type != N_FULL_TITLE) return;
    for (int i = 0; i < full_title->child_len; i++) {
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
    obj->name = strdup(identifier->value);
}

/**
 *
 */
void visit_secondary_title(ASTNode *secondary_title, Object *obj) {
    if (secondary_title->node_type != N_SECONDARY_TITLE) return;
    ASTNode *type_list = secondary_title->children[0];
    obj->interfaces_len = type_list->child_len;
    obj->interfaces = malloc(obj->interfaces_len * sizeof(Interface*));
    for (int i = 0; i < type_list->child_len; i++) {
        ASTNode *type = type_list->children[i];
        obj->interfaces[i] = malloc(sizeof(Interface));
        obj->interfaces[i]->name = strdup(type->value);
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
void visit_type_list(ASTNode *type_list, Object *obj) {

}

void free_object(Object *obj) {
    if (obj) {
        free(obj->name);
        for (size_t i = 0; i < obj->interfaces_len; i++) {
            free(obj->interfaces[i]->name);
            free(obj->interfaces[i]);
        }
        free(obj->interfaces);
        free(obj);
    }
}

