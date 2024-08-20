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
    VariableDec *param = method->method_signature->param_list->var_declarations[0];
}
