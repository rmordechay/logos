#include "compiler.h"

/**
 *
 */
void compile(ASTNode *root) {
    visitObjectFile(root);
}

/**
 *
 */
void visitObjectFile(ASTNode *object_file) {
    if (object_file->nodeType != N_OBJECT_FILE) return;
    cJSON *json = node_to_json(object_file);
    char *jsonString = cJSON_Print(json);
    cJSON_Delete(json);
    printf("%s\n", jsonString);
}

//void visitNode(ASTNode *node) {
//    switch (node->nodeType) {
//        case N_OBJECT_FILE:
//            visitObjectFile(node);
//            break;
//        case N_FULL_TITLE:break;
//        case N_PRIMARY_TITLE:break;
//        case N_SECONDARY_TITLE:break;
//        case N_METHODS_BLOCK_LIST:break;
//        case N_METHODS_BLOCK:break;
//        case N_METHODS_LIST:break;
//        case N_METHOD_SIGNATURE:break;
//        case N_METHOD_HEADER:break;
//        case N_METHOD:break;
//        case N_PARAM_LIST:break;
//        case N_PARAM:break;
//        case N_FULL_VARIABLE_DECLARATION:break;
//        case N_FIELDS_BLOCK:break;
//        case N_FIELD_LIST:break;
//        case N_FIELD:break;
//        case N_VARIABLE_DECLARATION:break;
//        case N_IDENTIFIER:break;
//        case N_TYPE:break;
//    }
//}

