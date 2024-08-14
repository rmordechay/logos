#include "analyser.h"

char *object_name;

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
    if (object_file->node_type != N_OBJECT_FILE) return;
    for (int i = 0; i < object_file->child_count; i++) {
        ASTNode *child = object_file->children[i];
        int nt = child->node_type;
        if (nt == N_FULL_TITLE) {
            visit_full_title(child);
        } else if (nt == N_FIELDS_BLOCK) {
            visit_fields_block(child);
        } else if (nt == N_METHODS_BLOCK_LIST) {
            visit_methods_block_list(child);
        }
    }
}

/**
 *
 */
void visit_full_title(ASTNode *full_title) {
    if (full_title->node_type != N_FULL_TITLE) return;
    for (int i = 0; i < full_title->child_count; i++) {
        ASTNode *child = full_title->children[i];
        int nt = child->node_type;
        if (nt == N_PRIMARY_TITLE) {
            visit_primary_title(child);
        } else if (nt == N_SECONDARY_TITLE) {
            visit_secondary_title(child);
        }
    }
}

/**
 *
 */
void visit_primary_title(ASTNode *primary_title) {
    object_name = primary_title->children[0]->value;
    printf("%s\n", object_name);
}

/**
 *
 */
void visit_secondary_title(ASTNode *secondary_title) {

}

/**
 *
 */
void visit_methods_block_list(ASTNode *methods_block_list) {

}

/**
 *
 */
void visit_fields_block(ASTNode *fields_block) {

}

