#include <stdlib.h>
#include <string.h>
#include <printf.h>
#include "tree.h"
#include "parser.h"
#include "analyser/analysis.h"
#include "token_types.h"

void yyerror(const char *s);
unsigned int iteration_level;
extern int yylineno;

/**
 *
 */
void analyse_ast(Entity *entity) {
    switch (entity->type) {
        case E_OBJECT:
            analyse_object(entity->object_entity);
            break;
        case E_INTERFACE:
            analyse_interface(entity->interface_entity);
        case E_ENUM:
            break;
    }
    free_entity(entity);
}

/**
 *
 */
Entity *create_entity(EntityType entity_type, void *entity_tree) {
    Entity *entity = malloc(sizeof(Entity));
    entity->line_number = yylineno;
    entity->type = entity_type;
    switch (entity_type) {
        case E_OBJECT:
            entity->object_entity = entity_tree;
            break;
        case E_INTERFACE:
            entity->interface_entity = entity_tree;
            break;
        case E_ENUM:
            break;
    }
    return entity;
}

/**
 *
 */
ObjEntity *create_object_entity(Type *t, ImplementsBlock *ib, ObjFieldList *fl, ObjMethodsBlockList *mbl) {
    ObjEntity *obj = malloc(sizeof(ObjEntity));
    obj->id = t;
    obj->field_list = fl;
    obj->implements_block = ib;
    obj->methods_block_list = mbl;
    return obj;
}

/**
 *
 */
InterfaceEntity *create_interface_entity(Type *type, InterfaceFieldList *fields_list) {
    InterfaceEntity *obj = malloc(sizeof(InterfaceEntity));
    obj->id = type;
    obj->field_list = fields_list;
    return obj;
}

/**
 *
 */
ImplementsBlock *create_implements_block(TypeList *type_list) {
    ImplementsBlock *ib = malloc(sizeof(ImplementsBlock));
    ib->line_number = yylineno;
    ib->type_list = type_list;
    return ib;
}

/**
 *
 */
ObjFieldList *create_object_field_list(ObjectField *field) {
    ObjFieldList *fl = malloc(sizeof(ObjFieldList));
    fl->line_number = yylineno;
    fl->fields = malloc(sizeof(ObjectField *));
    fl->count = 1;
    fl->fields[0] = field;
    return fl;
}

/**
 *
 */
ObjFieldList *add_object_field(ObjFieldList *list, ObjectField *element) {
    int new_size = list->count + 1;
    ObjectField **new_list = realloc(list->fields, new_size * sizeof(ObjectField *));
    list->fields = new_list;
    list->fields[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
ObjectField *create_object_field(VariableDec *variable_declaration, Type *type) {
    ObjectField *f = malloc(sizeof(ObjectField));
    f->line_number = yylineno;
    f->variable_declaration = variable_declaration;
    f->implements = type;
    return f;
}

/**
 *
 */
InterfaceFieldList *create_interface_field_list(InterfaceField *field) {
    InterfaceFieldList *fl = malloc(sizeof(InterfaceFieldList));
    fl->line_number = yylineno;
    fl->fields = malloc(sizeof(InterfaceField *));
    fl->count = 1;
    fl->fields[0] = field;
    return fl;
}

/**
 *
 */
InterfaceFieldList *add_interface_field(InterfaceFieldList *list, InterfaceField *element) {
    int new_size = list->count + 1;
    InterfaceField **new_list = realloc(list->fields, new_size * sizeof(InterfaceField *));
    list->fields = new_list;
    list->fields[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
InterfaceField *create_interface_field(VariableDec *variable_declaration) {
    InterfaceField *f = malloc(sizeof(InterfaceField *));
    f->line_number = yylineno;
    f->variable_declaration = variable_declaration;
    return f;
}

/**
 *
 */
ObjMethodsBlockList *create_object_methods_block_list(ObjMethodsBlock *methodBlock) {
    ObjMethodsBlockList *mbl = malloc(sizeof(ObjMethodsBlockList));
    mbl->line_number = yylineno;
    mbl->blocks = malloc(sizeof(ObjMethodsBlock *));
    mbl->count = 1;
    mbl->blocks[0] = methodBlock;
    return mbl;
}

/**
 *
 */
ObjMethodsBlockList *add_object_methods_block(ObjMethodsBlockList *list, ObjMethodsBlock *element) {
    int new_size = list->count + 1;
    ObjMethodsBlock **new_list = realloc(list->blocks, new_size * sizeof(ObjMethodsBlock *));
    list->blocks = new_list;
    list->blocks[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
ObjMethodsBlock *create_object_methods_block(Type *type, ObjMethodsList *methods_list) {
    ObjMethodsBlock *mb = malloc(sizeof(ObjMethodsBlock));
    mb->line_number = yylineno;
    mb->identifier = type;
    mb->methods_list = methods_list;
    return mb;
}


/**
 *
 */
ObjMethodsList *create_object_methods_list(ObjMethod *method) {
    ObjMethodsList *ml = malloc(sizeof(ObjMethodsList));
    ml->line_number = yylineno;
    ml->methods = malloc(sizeof(ObjMethod *));
    ml->count = 1;
    ml->methods[0] = method;
    return ml;
}

/**
 *
 */
ObjMethodsList *add_object_method(ObjMethodsList *list, ObjMethod *element) {
    int new_size = list->count + 1;
    ObjMethod **new_list = realloc(list->methods, new_size * sizeof(ObjMethod *));
    list->methods = new_list;
    list->methods[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
InterfaceMethodsBlock *create_interface_methods_block(Type *type, InterfaceMethodsList *methods_list) {
    InterfaceMethodsBlock *mb = malloc(sizeof(InterfaceMethodsBlock));
    mb->line_number = yylineno;
    mb->identifier = type;
    mb->methods_list = methods_list;
    return mb;
}

/**
 *
 */
ObjMethod *create_object_method(MethodSignature *method_signature, StatementList *statement_list, Carrier *carrier) {
    ObjMethod *m = malloc(sizeof(ObjMethod));
    m->line_number = yylineno;
    m->method_signature = method_signature;
    m->statement_list = statement_list;
    m->name = strdup(m->method_signature->method_variable->identifier->name);
    return m;
}

/**
 *
 */
InterfaceMethodsBlockList *create_interface_methods_block_list(InterfaceMethodsBlock *methodBlock) {
    InterfaceMethodsBlockList *mbl = malloc(sizeof(InterfaceMethodsBlockList));
    mbl->line_number = yylineno;
    mbl->blocks = malloc(sizeof(InterfaceMethodsBlock *));
    mbl->count = 1;
    mbl->blocks[0] = methodBlock;
    return mbl;
}

/**
 *
 */
InterfaceMethodsBlockList *
add_interface_methods_block(InterfaceMethodsBlockList *list, InterfaceMethodsBlock *element) {
    int new_size = list->count + 1;
    InterfaceMethodsBlock **new_list = realloc(list->blocks, new_size * sizeof(InterfaceMethodsBlock *));
    list->blocks = new_list;
    list->blocks[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
InterfaceMethod *create_interface_method(MethodSignature *method_signature, StatementList *statement_list) {
    InterfaceMethod *m = malloc(sizeof(InterfaceMethod));
    m->line_number = yylineno;
    m->method_signature = method_signature;
    m->statement_list = statement_list;
    m->name = &m->method_signature->method_variable->identifier->name;
    return m;
}

/**
 *
 */
InterfaceMethodsList *create_interface_methods_list(InterfaceMethod *method) {
    InterfaceMethodsList *ml = malloc(sizeof(InterfaceMethodsList));
    ml->line_number = yylineno;
    ml->methods = malloc(sizeof(InterfaceMethod *));
    ml->count = 1;
    ml->methods[0] = method;
    return ml;
}

/**
 *
 */
InterfaceMethodsList *add_interface_method(InterfaceMethodsList *list, InterfaceMethod *element) {
    int new_size = list->count + 1;
    InterfaceMethod **new_list = realloc(list->methods, new_size * sizeof(InterfaceMethod *));
    list->methods = new_list;
    list->methods[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
MethodSignature *create_method_signature(VariableDec *variable_dec, VariableDecList *variable_declaration_list) {
    MethodSignature *ms = malloc(sizeof(MethodSignature));
    ms->line_number = yylineno;
    ms->method_variable = variable_dec;
    ms->param_list = variable_declaration_list;
    return ms;
}

/**
 *
 */
StatementList *create_statement_list(Statement *statement) {
    StatementList *sl = malloc(sizeof(StatementList));
    sl->line_number = yylineno;
    if (statement != NULL) {
        sl->statements = malloc(sizeof(Statement *));
        sl->statements[0] = statement;
        sl->count = 1;
        if (statement->type == ST_ITERATION) iteration_level--;
    } else {
        sl->statements = NULL;
        sl->count = 0;
    }
    return sl;
}

/**
 *
 */
StatementList *add_statement(StatementList *list, Statement *element) {
    int new_size = list->count + 1;
    Statement **new_list = realloc(list->statements, new_size * sizeof(Statement *));
    list->statements = new_list;
    list->statements[list->count] = element;
    list->count++;
    if (iteration_level == 0) {
        if (element->type == ST_CONTINUE_STATEMENT) {
            yyerror("'continue' outside iteration loop");
        } else if (element->type == ST_BREAK_STATEMENT) {
            yyerror("'break' outside iteration loop");
        }
    } else if (element->type == ST_ITERATION) {
        iteration_level--;
    }
    return list;
}

/**
 *
 */
Statement *create_stmt_from_local_dec(LocalDeclaration *local_declaration) {
    Statement *s = malloc(sizeof(Statement));
    s->line_number = yylineno;
    s->local_declaration = local_declaration;
    s->type = ST_LOCAL_DECLARATION;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_if_stmt(IfStatement *if_statement) {
    Statement *s = malloc(sizeof(Statement));
    s->line_number = yylineno;
    s->if_statement = if_statement;
    s->type = ST_IF_STATEMENT;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_pm(PatternMatching *pattern_matching) {
    Statement *s = malloc(sizeof(Statement));
    s->line_number = yylineno;
    s->pattern_matching = pattern_matching;
    s->type = ST_PATTERN_MATCHING;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_pme(PatternMatchingExpr *pattern_matching_expr) {
    Statement *s = malloc(sizeof(Statement));
    s->line_number = yylineno;
    s->pattern_matching_expr = pattern_matching_expr;
    s->type = ST_PATTERN_MATCHING_EXPR;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_iteration(Iteration *iteration) {
    iteration_level++;
    Statement *s = malloc(sizeof(Statement));
    s->line_number = yylineno;
    s->iteration = iteration;
    s->type = ST_ITERATION;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_return(ReturnStatement *return_statement) {
    Statement *s = malloc(sizeof(Statement));
    s->line_number = yylineno;
    s->return_statement = return_statement;
    s->type = ST_RETURN_STATEMENT;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_break(Expr *break_expr) {
    Statement *s = malloc(sizeof(Statement));
    s->line_number = yylineno;
    s->break_expr = break_expr;
    s->type = ST_BREAK_STATEMENT;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_continue() {
    Statement *s = malloc(sizeof(Statement));
    s->line_number = yylineno;
    s->type = ST_CONTINUE_STATEMENT;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_enum(EnumDeclaration *enum_declaration) {
    Statement *s = malloc(sizeof(Statement));
    s->line_number = yylineno;
    s->type = ST_ENUM_STATEMENT;
    s->enum_declaration = enum_declaration;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_expr(Expr *expr) {
    Statement *s = malloc(sizeof(Statement));
    s->line_number = yylineno;
    s->type = ST_EXPR;
    s->expr = expr;
    return s;
}

/**
 *
 */
LocalDeclaration *create_local_declaration(Type *type, Identifier *identifier, Expr *expr) {
    LocalDeclaration *ld = malloc(sizeof(LocalDeclaration));
    ld->line_number = yylineno;
    ld->identifier = identifier;
    ld->type = type;
    ld->expr = expr;
    return ld;
}

/**
 *
 */
IfStatement *create_if_statement(IfBlock *if_block, IfOrBlockList *if_or_block_list, OrBlock *or_block) {
    IfStatement *if_statement = malloc(sizeof(IfStatement));
    if_statement->line_number = yylineno;
    if_statement->or_block = or_block;
    if_statement->if_block = if_block;
    if_statement->if_or_block_list = if_or_block_list;
    return if_statement;
}


/**
 *
 */
IfBlock *create_if_block(Expr *expr, StatementList *statement_list) {
    IfBlock *if_block = malloc(sizeof(IfBlock));
    if_block->line_number = yylineno;
    if_block->statement_list = statement_list;
    if_block->expr = expr;
    return if_block;
}

/**
 *
 */
IfOrBlockList *create_if_or_block_list(IfOrBlock *if_or_block) {
    IfOrBlockList *if_or_block_list = malloc(sizeof(IfOrBlockList));
    if_or_block_list->line_number = yylineno;
    if_or_block_list->if_or_blocks = malloc(sizeof(IfOrBlock *));
    if_or_block_list->count = 1;
    if_or_block_list->if_or_blocks[0] = if_or_block;
    return if_or_block_list;
}


/**
 *
 */
IfOrBlockList *add_if_or_block(IfOrBlockList *list, IfOrBlock *element) {
    int new_size = list->count + 1;
    IfOrBlock **new_list = realloc(list->if_or_blocks, new_size * sizeof(IfOrBlock *));
    list->if_or_blocks = new_list;
    list->if_or_blocks[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
IfOrBlock *create_if_or_block(Expr *expr, StatementList *statement_list) {
    IfOrBlock *if_or_block = malloc(sizeof(IfOrBlock));
    if_or_block->line_number = yylineno;
    if_or_block->statement_list = statement_list;
    if_or_block->expr = expr;
    return if_or_block;
}

/**
 *
 */
OrBlock *create_or_block(StatementList *statement_list) {
    OrBlock *or_block = malloc(sizeof(OrBlock));
    or_block->line_number = yylineno;
    or_block->statement_list = statement_list;
    return or_block;
}

/**
 *
 */
PatternMatching *create_pattern_matching(PatternList *pattern_list) {
    PatternMatching *pattern_matching = malloc(sizeof(PatternMatching));
    pattern_matching->line_number = yylineno;
    pattern_matching->pattern_list = pattern_list;
    return pattern_matching;
}

/**
 *
 */
PatternMatchingExpr *create_pattern_matching_expr(Expr *condition, PatternList *pattern_list) {
    PatternMatchingExpr *pattern_matching = malloc(sizeof(PatternMatchingExpr *));
    pattern_matching->line_number = yylineno;
    pattern_matching->expr = condition;
    pattern_matching->pattern_list = pattern_list;
    return pattern_matching;
}

/**
 *
 */
Pattern *create_pattern_from_stmt_list(Expr *condition, StatementList *statement_list) {
    Pattern *pattern = malloc(sizeof(Pattern *));
    pattern->line_number = yylineno;
    pattern->condition = condition;
    pattern->type = PB_STMT_LIST;
    pattern->statement_list = statement_list;
    return pattern;
}

/**
 *
 */
Pattern *create_pattern_from_expr(Expr *condition, Expr *expr) {
    Pattern *pattern = malloc(sizeof(Pattern *));
    pattern->line_number = yylineno;
    pattern->condition = condition;
    pattern->type = PB_EXPR;
    pattern->expr = expr;
    return pattern;
}

/**
 *
 */
PatternList *create_pattern_list(Pattern *pattern) {
    PatternList *pl = malloc(sizeof(PatternList *));
    pl->line_number = yylineno;
    pl->patterns = malloc(sizeof(Pattern *));
    pl->count = 1;
    pl->patterns[0] = pattern;
    return pl;
}

/**
 *
 */
PatternList *add_pattern(PatternList *list, Pattern *element) {
    int new_size = list->count + 1;
    Pattern **new_list = realloc(list->patterns, new_size * sizeof(Pattern *));
    list->patterns = new_list;
    list->patterns[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
Iteration *create_iteration_from_for_in(ForInLoop *for_in_loop, StatementList *statement_list) {
    Iteration *iteration = malloc(sizeof(Iteration));
    iteration->line_number = yylineno;
    iteration->type = FL_IN;
    iteration->statement_list = statement_list;
    iteration->for_in_loop = for_in_loop;
    return iteration;
}

/**
 *
 */
Iteration *create_iteration_from_while(WhileLoop *while_loop, StatementList *statement_list) {
    Iteration *iteration = malloc(sizeof(Iteration));
    iteration->line_number = yylineno;
    iteration->type = FL_WHILE;
    iteration->statement_list = statement_list;
    iteration->while_loop = while_loop;
    return iteration;
}

/**
 *
 */
Iteration *create_iteration_from_inf_loop(StatementList *statement_list) {
    Iteration *iteration = malloc(sizeof(Iteration));
    iteration->line_number = yylineno;
    iteration->type = FL_INFINITE;
    iteration->statement_list = statement_list;
    return iteration;
}

/**
 *
 */
ForInLoop *create_for_in_loop(ExprList *expr_list, Expr *in_expr) {
    ForInLoop *iteration_in = malloc(sizeof(ForInLoop));
    iteration_in->line_number = yylineno;
    iteration_in->expr_list = expr_list;
    iteration_in->in_expr = in_expr;
    return iteration_in;
}

/**
 *
 */
WhileLoop *create_while_loop(ExprList *expr_list) {
    WhileLoop *while_loop = malloc(sizeof(WhileLoop));
    while_loop->line_number = yylineno;
    while_loop->expr_list = expr_list;
    return while_loop;
}

/**
 *
 */
ReturnStatement *create_return_statement(ExprList *expr_list) {
    ReturnStatement *return_statement = malloc(sizeof(ReturnStatement));
    return_statement->line_number = yylineno;
    return_statement->expr_list = expr_list;
    return return_statement;
}

/**
 *
 */
Expr *create_expr_from_unary(UnaryExpr *unary_expr) {
    Expr *e = malloc(sizeof(Expr));
    e->line_number = yylineno;
    e->unary_expr = unary_expr;
    e->type = E_UNARY;
    return e;
}

/**
 *
 */
Expr *create_expr_from_binary(BinaryExpr *binary_expr) {
    Expr *e = malloc(sizeof(Expr));
    e->line_number = yylineno;
    e->binary_expr = binary_expr;
    e->type = E_BINARY;
    return e;
}

/**
 *
 */
ExprList *create_expr_list(Expr *expr) {
    ExprList *expr_list = malloc(sizeof(ExprList *));
    expr_list->line_number = yylineno;
    expr_list->exprs = malloc(sizeof(Expr *));
    expr_list->count = 1;
    expr_list->exprs[0] = expr;
    return expr_list;
}

/**
 *
 */
ExprList *add_expr(ExprList *list, Expr *element) {
    int new_size = list->count + 1;
    Expr **new_list = realloc(list->exprs, new_size * sizeof(Expr *));
    list->exprs = new_list;
    list->exprs[list->count] = element;
    list->count++;
    return list;
}


/**
 *
 */
BinaryExpr *create_binary_expr(Expr *left, Expr *right, char operator) {
    BinaryExpr *be = malloc(sizeof(BinaryExpr));
    be->line_number = yylineno;
    be->left = left;
    be->right = right;
    be->operator = operator;
    return be;
}

/**
 *
 */
UnaryExpr *create_unary_expr_from_number(int type, char *integer_value) {
    UnaryExpr *ue = malloc(sizeof(UnaryExpr));
    ue->line_number = yylineno;
    ue->integer_value = strdup(integer_value);
    ue->type = type;
    return ue;
}


/**
 *
 */
UnaryExpr *create_unary_expr_from_id(Identifier *identifier) {
    UnaryExpr *ue = malloc(sizeof(UnaryExpr));
    ue->line_number = yylineno;
    ue->identifier = identifier;
    ue->type = UE_IDENTIFIER;
    return ue;
}

/**
 *
 */
UnaryExpr *create_unary_expr_from_string(char *string) {
    UnaryExpr *ue = malloc(sizeof(UnaryExpr));
    ue->line_number = yylineno;
    ue->string = strdup(string);
    ue->type = UE_STRING;
    return ue;
}

/**
 *
 */
UnaryExpr *create_unary_expr_from_method_call(MethodCall *method_call) {
    UnaryExpr *ue = malloc(sizeof(UnaryExpr));
    ue->line_number = yylineno;
    ue->method_call = method_call;
    ue->type = UE_METHOD_CALL;
    return ue;
}

/**
 *
 */
UnaryExpr *create_unary_expr_from_collection(Collection *collection) {
    UnaryExpr *ue = malloc(sizeof(UnaryExpr));
    ue->line_number = yylineno;
    ue->collection = collection;
    ue->type = UE_COLLECTION;
    return ue;
}

/**
 *
 */
MethodCall *create_method_call(MethodSignature *method_signature, ExprList *param_exprs) {
    MethodCall *method_call = malloc(sizeof(MethodCall));
    method_call->line_number = yylineno;
    method_call->method_signature = method_signature;
    method_call->param_exprs = param_exprs;
    return method_call;
}

/**
 *
 */
VariableDecList *create_var_dec_list(VariableDec *variable_dec) {
    VariableDecList *vdl = malloc(sizeof(VariableDecList));
    vdl->line_number = yylineno;
    vdl->var_declarations = malloc(sizeof(VariableDec *));
    vdl->count = 1;
    vdl->var_declarations[0] = variable_dec;
    return vdl;
}

/**
 *
 */
VariableDecList *add_var_dec(VariableDecList *list, VariableDec *element) {
    int new_size = list->count + 1;
    VariableDec **new_list = realloc(list->var_declarations, new_size * sizeof(VariableDec *));
    list->var_declarations = new_list;
    list->var_declarations[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
VariableDec *create_variable_declaration(Type *type, Identifier *identifier) {
    VariableDec *vd = malloc(sizeof(VariableDec));
    vd->line_number = yylineno;
    vd->type = type;
    vd->identifier = identifier;
    return vd;
}

/**
 *
 */
Collection *create_collection(Type *type, ExprList *expr_list) {
    Collection *collection = malloc(sizeof(Collection));
    collection->line_number = yylineno;
    collection->type = type;
    collection->size = expr_list->count;
    collection->expr_list = expr_list;
    return collection;
}

/**
 *
 */
EnumDeclaration *create_enum_declaration(Type *type, ConstantVariableList *const_var_list) {
    EnumDeclaration *ed = malloc(sizeof(EnumDeclaration));
    ed->line_number = yylineno;
    ed->type = type;
    ed->const_var_list = const_var_list;
    return ed;
}

/**
 *
 */
Identifier *create_identifier(char *name) {
    Identifier *id = malloc(sizeof(Identifier));
    id->line_number = yylineno;
    id->name = strdup(name);
    return id;
}

/**
 *
 */
IdentifierList *create_identifier_list(Identifier *identifier) {
    IdentifierList *tl = malloc(sizeof(IdentifierList));
    tl->line_number = yylineno;
    tl->identifiers = malloc(sizeof(Identifier *));
    tl->count = 1;
    tl->identifiers[0] = identifier;
    return tl;
}

/**
 *
 */
IdentifierList *add_identifier(IdentifierList *list, Identifier *element) {
    int new_size = list->count + 1;
    Identifier **new_list = realloc(list->identifiers, new_size * sizeof(Identifier *));
    list->identifiers = new_list;
    list->identifiers[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
ConstantVariable *create_constant_variable(char *name) {
    ConstantVariable *cv = malloc(sizeof(ConstantVariable));
    cv->line_number = yylineno;
    cv->name = name;
    return cv;
}

/**
 *
 */
ConstantVariableList *create_const_var_list(ConstantVariable *constant_variable) {
    ConstantVariableList *vdl = malloc(sizeof(ConstantVariableList));
    vdl->line_number = yylineno;
    vdl->constant_variables = malloc(sizeof(ConstantVariable *));
    vdl->count = 1;
    vdl->constant_variables[0] = constant_variable;
    return vdl;
}

/**
 *
 */
ConstantVariableList *add_const_var(ConstantVariableList *list, ConstantVariable *element) {
    int new_size = list->count + 1;
    ConstantVariable **new_list = realloc(list->constant_variables, new_size * sizeof(ConstantVariable *));
    list->constant_variables = new_list;
    list->constant_variables[list->count] = element;
    list->count++;
    return list;
}


/**
 *
 */
Type *create_type(char *name) {
    Type *t = malloc(sizeof(Type));
    t->line_number = yylineno;
    t->name = strdup(name);
    return t;
}

/**
 *
 */
TypeList *create_type_list(Type *type) {
    TypeList *tl = malloc(sizeof(TypeList));
    tl->types = malloc(sizeof(Type *));
    tl->count = 1;
    tl->types[0] = type;
    return tl;
}

/**
 *
 */
TypeList *add_type(TypeList *list, Type *element) {
    int new_size = list->count + 1;
    Type **new_list = realloc(list->types, new_size * sizeof(Type *));
    list->types = new_list;
    list->types[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
void free_entity(Entity *obj) {
    if (obj == NULL) return;
    switch (obj->type) {
        case E_OBJECT:
            free_object_file(obj->object_entity);
            break;
        case E_INTERFACE:
        case E_ENUM:
            break;
    }
}

/**
 *
 */
void free_object_file(ObjEntity *obj) {
    if (obj == NULL) return;
    free_object_field_list(obj->field_list);
    free_methods_block_list(obj->methods_block_list);
    free_implements_block(obj->implements_block);
    free(obj->id);
    free(obj);
}

/**
 *
 */
void free_implements_block(ImplementsBlock *ib) {
    if (ib == NULL) return;
    free_type_list(ib->type_list);
    free(ib);
}

/**
 *
 */
void free_object_field_list(ObjFieldList *fl) {
    if (fl == NULL) return;
    for (int i = 0; i < fl->count; i++) {
        free_object_field(fl->fields[i]);
    }
    free(fl->fields);
    free(fl);
}

/**
 *
 */
void free_object_field(ObjectField *f) {
    if (f == NULL) return;
    free_variable_declaration(f->variable_declaration);
    free_type(f->implements);
    free(f);
}

/**
 *
 */
void free_methods_block_list(ObjMethodsBlockList *mbl) {
    if (mbl == NULL) return;
    for (int i = 0; i < mbl->count; i++) {
        free_methods_block(mbl->blocks[i]);
    }
    free(mbl->blocks);
    free(mbl);
}

/**
 *
 */
void free_methods_block(ObjMethodsBlock *mb) {
    if (mb == NULL) return;
    free_type(mb->identifier);
    free_methods_list(mb->methods_list);
    free(mb);
}

/**
 *
 */
void free_methods_list(ObjMethodsList *ml) {
    if (ml == NULL) return;
    for (int i = 0; i < ml->count; i++) {
        free_method(ml->methods[i]);
    }
    free(ml->methods);
    free(ml);
}

/**
 *
 */
void free_method(ObjMethod *m) {
    if (m == NULL) return;
    free_method_signature(m->method_signature);
    free_statement_list(m->statement_list);
    free(m->name);
    free(m);
}

/**
 *
 */
void free_method_signature(MethodSignature *ms) {
    if (ms == NULL) return;
    free_variable_declaration(ms->method_variable);
    if (ms->param_list) {
        free_variable_declaration_list(ms->param_list);
    }
    free(ms);
}


/**
 *
 */
void free_statement_list(StatementList *sl) {
    if (sl == NULL) return;
    for (int i = 0; i < sl->count; i++) {
        free_statement(sl->statements[i]);
    }
    free(sl->statements);
    free(sl);
}

/**
 *
 */
void free_statement(Statement *s) {
    if (s == NULL) return;
    switch (s->type) {
        case ST_LOCAL_DECLARATION:
            free_local_declaration(s->local_declaration);
            break;
        case ST_IF_STATEMENT:
            free_if_statement(s->if_statement);
            break;
        case ST_PATTERN_MATCHING:
            free_pattern_matching(s->pattern_matching);
            break;
        case ST_PATTERN_MATCHING_EXPR:
            free_pattern_matching_expr(s->pattern_matching_expr);
            break;
        case ST_ITERATION:
            free_iteration(s->iteration);
            break;
        case ST_RETURN_STATEMENT:
            free_return_statement(s->return_statement);
            break;
        case ST_BREAK_STATEMENT:
            free_expr(s->break_expr);
        case ST_CONTINUE_STATEMENT:
            break;
        case ST_ENUM_STATEMENT:
            free_enum_declaration(s->enum_declaration);
            break;
        case ST_EXPR:
            free_expr(s->expr);
            break;
    }
    free(s);
}

/**
 *
 */
void free_local_declaration(LocalDeclaration *ld) {
    if (ld == NULL) return;
    free_type(ld->type);
    free_identifier(ld->identifier);
    free_expr(ld->expr);
    free(ld);
}

/**
 *
 */
void free_if_statement(IfStatement *is) {
    if (is == NULL) return;
    free_if_block(is->if_block);
    free_or_block(is->or_block);
    free_if_or_block_list(is->if_or_block_list);
    free(is);
}

/**
 *
 */
void free_if_block(IfBlock *ib) {
    if (ib == NULL) return;
    free_expr(ib->expr);
    free_statement_list(ib->statement_list);
    free(ib);
}

/**
 *
 */
void free_if_or_block_list(IfOrBlockList *iobl) {
    if (iobl == NULL) return;
    for (int i = 0; i < iobl->count; i++) {
        free_if_or_block(iobl->if_or_blocks[i]);
    }
    free(iobl);
}

/**
 *
 */
void free_if_or_block(IfOrBlock *iob) {
    if (iob == NULL) return;
    free_expr(iob->expr);
    free_statement_list(iob->statement_list);
    free(iob);
}

/**
 *
 */
void free_or_block(OrBlock *ob) {
    if (ob == NULL) return;
    free_statement_list(ob->statement_list);
    free(ob);
}

/**
 *
 */
void free_pattern(Pattern *p) {
    if (p == NULL) return;
    switch (p->type) {
        case PB_EXPR:
            free_expr(p->expr);
            break;
        case PB_STMT_LIST:
            free_statement_list(p->statement_list);
            break;
    }
    free(p);
}

/**
 *
 */
void free_pattern_list(PatternList *pl) {
    if (pl == NULL) return;
    for (int i = 0; i < pl->count; i++) {
        free_pattern(pl->patterns[i]);
    }
    free(pl);
}

/**
 *
 */
void free_pattern_matching(PatternMatching *pm) {
    if (pm == NULL) return;
    free_pattern_list(pm->pattern_list);
    free(pm);
}

/**
 *
 */
void free_pattern_matching_expr(PatternMatchingExpr *pme) {
    if (pme == NULL) return;
    free_expr(pme->expr);
    free_pattern_list(pme->pattern_list);
    free(pme);
}

/**
 *
 */
void free_iteration(Iteration *fl) {
    if (fl == NULL) return;
    switch (fl->type) {
        case FL_WHILE:
            free_while_loop(fl->while_loop);
            break;
        case FL_IN:
            free_for_in_loop(fl->for_in_loop);
            break;
        case FL_INFINITE:
            break;
    }
    free_statement_list(fl->statement_list);
    free(fl);
}

/**
 *
 */
void free_for_in_loop(ForInLoop *fli) {
    if (fli == NULL) return;
    free_expr_list(fli->expr_list);
    free_expr(fli->in_expr);
    free(fli);
}

/**
 *
 */
void free_while_loop(WhileLoop *wl) {
    if (wl == NULL) return;
    free_expr_list(wl->expr_list);
    free(wl);
}

/**
 *
 */
void free_return_statement(ReturnStatement *rs) {
    if (rs == NULL) return;
    free_expr_list(rs->expr_list);
    free(rs);
}

/**
 *
 */
void free_expr(Expr *e) {
    if (e == NULL) return;
    if (e->unary_expr != NULL) {
        free_unary_expr(e->unary_expr);
    } else if (e->binary_expr != NULL) {
        free_binary_expr(e->binary_expr);
    }
    free(e);
}

/**
 *
 */
void free_expr_list(ExprList *el) {
    if (el == NULL) return;
    for (int i = 0; i < el->count; ++i) {
        free_expr(el->exprs[i]);
    }
    free(el);
}

/**
 *
 */
void free_binary_expr(BinaryExpr *be) {
    if (be == NULL) return;
    free_expr(be->left);
    free_expr(be->right);
    free(be);
}

/**
 *
 */
void free_unary_expr(UnaryExpr *ue) {
    if (ue == NULL) return;
    switch (ue->type) {
        case UE_IDENTIFIER:
            free_identifier(ue->identifier);
            break;
        case UE_INT:
        case UE_FLOAT:
            break;
        case UE_STRING:
            free(ue->string);
            break;
        case UE_BOOL:
            break;
        case UE_METHOD_CALL:
            free(ue->method_call);
            break;
        case UE_COLLECTION:
            free_collection(ue->collection);
            break;
    }
    free(ue);
}

/**
 *
 */
void free_enum_declaration(EnumDeclaration *ed) {
    if (ed == NULL) return;
    free_const_variable_list(ed->const_var_list);
    free_type(ed->type);
    free(ed);
}

/**
 *
 */
void free_variable_declaration_list(VariableDecList *vdl) {
    if (vdl == NULL) return;
    for (int i = 0; i < vdl->count; i++) {
        free_variable_declaration(vdl->var_declarations[i]);
    }
    free(vdl->var_declarations);
    free(vdl);
}

/**
 *
 */
void free_variable_declaration(VariableDec *vd) {
    if (vd == NULL) return;
    free_type(vd->type);
    free_identifier(vd->identifier);
    free(vd);
}

/**
 *
 */
void free_collection(Collection *c) {
    free_type(c->type);
    free(c);
}

/**
 *
 */
void free_type(Type *t) {
    if (t == NULL) return;
    free(t->name);
    free(t);
}

/**
 *
 */
void free_type_list(TypeList *tl) {
    if (tl == NULL) return;
    for (int i = 0; i < tl->count; i++) {
        free_type(tl->types[i]);
    }
    free(tl->types);
    free(tl);
}

/**
 *
 */
void free_const_variable(ConstantVariable *cv) {
    if (cv == NULL) return;
    free(cv->name);
    free(cv);
}

/**
 *
 */
void free_const_variable_list(ConstantVariableList *cvl) {
    if (cvl == NULL) return;
    for (int i = 0; i < cvl->count; i++) {
        free_const_variable(cvl->constant_variables[i]);
    }
    free(cvl);
}

/**
 *
 */
void free_identifier(Identifier *i) {
    if (i == NULL) return;
    free(i->name);
    free(i);
}
