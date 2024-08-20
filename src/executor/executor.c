#include <printf.h>
#include "executor.h"


/**
 *
 */
void execute(ObjectEntity *entity) {
    Field *f = entity->fields_block->field_list->fields[0];
    printf("%s\n", f->variable_declaration->type->name);
    printf("%s\n", f->variable_declaration->identifier->name);
    Method *method = entity->methods_block_list->blocks[0]->methods_list->methods[0];
    StatementList *statement_list = method->statement_list;
    for (int i = 0; i < statement_list->count; i++) {
        Statement *statement = statement_list->statements[i];
        switch (statement->type) {
            case ST_LOCAL_DECLARATION:
                break;
            case ST_IF_STATEMENT:
                break;
            case ST_PATTERN_MATCHING:
                break;
            case ST_PATTERN_MATCHING_EXPR:
                break;
            case ST_ITERATION:
                break;
            case ST_RETURN_STATEMENT:
                break;
            case ST_BREAK_STATEMENT:
                break;
            case ST_CONTINUE_STATEMENT:
                break;
        }
    }
}
