#include <printf.h>
#include "executor.h"


/**
 *
 */
void execute(ObjectEntity *entity) {
    ObjectField *f = entity->field_list->fields[0];
    printf("%s\n", f->variable_declaration->type->name);
    printf("%s\n", f->variable_declaration->identifier->name);
    ObjectMethod *method = entity->methods_block_list->blocks[0]->methods_list->methods[0];
    StatementList *statement_list = method->statement_list;
    for (int i = 0; i < statement_list->count; i++) {
        Statement *statement = statement_list->statements[i];
    }
}
