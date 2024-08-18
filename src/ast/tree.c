#include <stdlib.h>
#include <string.h>
#include <printf.h>
#include "tree.h"
#include "parser.h"

void print_object_file_json(Entity *entity);

/**
 *
 */
void analyse_ast(Entity *root) {
    print_object_file_json(root);
}

/**
 *
 */
Entity *create_entity(EntityType entity_type, void *entity_tree) {
    Entity *entity = malloc(sizeof(Entity));
    switch (entity_type) {
        case OBJECT_ENTITY:
            entity->type = entity_type;
            entity->object_file = entity_tree;
            break;
        case INTERFACE_ENTITY:
        case ENUM_ENTITY:
            break;
    }
    return entity;
}

/**
 *
 */
ObjectFile *create_object_file(Identifier *identifier,
                               ImplementsBlock *implements_block,
                               FieldsBlock *fields_block,
                               MethodsBlockList *methods_block_list) {
    ObjectFile *obj = malloc(sizeof(ObjectFile));
    obj->id = identifier;
    obj->fields_block = fields_block;
    obj->implements_block = implements_block;
    obj->methods_block_list = methods_block_list;
    return obj;
}

/**
 *
 */
ImplementsBlock *create_implements_block(TypeList *type_list) {
    ImplementsBlock *ib = malloc(sizeof(ImplementsBlock));
    ib->type_list = type_list;
    return ib;
}

/**
 *
 */
FieldsBlock *create_fields_block(FieldList *field_list) {
    FieldsBlock *fb = malloc(sizeof(FieldsBlock));
    fb->field_list = field_list;
    return fb;
}

/**
 *
 */
FieldList *create_field_list(Field *field) {
    FieldList *fl = malloc(sizeof(FieldList));
    fl->fields = malloc(sizeof(Field *));
    fl->count = 1;
    fl->fields[0] = field;
    return fl;
}

/**
 *
 */
FieldList *flatten_field_list(FieldList *list, Field *element) {
    int new_size = list->count + 1;
    Field **new_list = realloc(list->fields, new_size * sizeof(Field *));
    list->fields = new_list;
    list->fields[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
Field *create_field(VariableDec *variable_declaration, Type *type) {
    Field *f = malloc(sizeof(Field));
    f->variable_declaration = variable_declaration;
    f->implements = type;
    return f;
}

/**
 *
 */
MethodsBlockList *create_methods_block_list(MethodsBlock *methodBlock) {
    MethodsBlockList *mbl = malloc(sizeof(MethodsBlockList));
    mbl->blocks = malloc(sizeof(MethodsBlock *));
    mbl->count = 1;
    mbl->blocks[0] = methodBlock;
    return mbl;
}

/**
 *
 */
MethodsBlockList *flatten_methods_block_list(MethodsBlockList *list, MethodsBlock *element) {
    int new_size = list->count + 1;
    MethodsBlock **new_list = realloc(list->blocks, new_size * sizeof(MethodsBlock *));
    list->blocks = new_list;
    list->blocks[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
MethodsBlock *create_methods_block(Identifier *identifier, MethodsList *methods_list) {
    MethodsBlock *mb = malloc(sizeof(MethodsBlock));
    mb->identifier = identifier;
    mb->methods_list = methods_list;
    return mb;
}


/**
 *
 */
MethodsList *create_methods_list(Method *method) {
    MethodsList *ml = malloc(sizeof(MethodsList));
    ml->methods = malloc(sizeof(Method *));
    ml->count = 1;
    ml->methods[0] = method;
    return ml;
}

/**
 *
 */
MethodsList *flatten_methods_list(MethodsList *list, Method *element) {
    int new_size = list->count + 1;
    Method **new_list = realloc(list->methods, new_size * sizeof(Method *));
    list->methods = new_list;
    list->methods[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
Method *create_method(MethodSignature *method_signature, StatementList *statement_list) {
    Method *m = malloc(sizeof(Method));
    m->method_signature = method_signature;
    m->statement_list = statement_list;
    m->name = &m->method_signature->method_header->variable_declaration->identifier->name;
    return m;
}

/**
 *
 */
MethodSignature *create_method_signature(MethodHeader *method_header, VarDecList *variable_declaration_list) {
    MethodSignature *ms = malloc(sizeof(MethodSignature));
    ms->method_header = method_header;
    ms->variable_declaration_list = variable_declaration_list;
    return ms;
}

/**
 *
 */
MethodHeader *create_method_header(VariableDec *variable_declaration) {
    MethodHeader *mh = malloc(sizeof(MethodHeader));
    mh->variable_declaration = variable_declaration;
    return mh;
}

/**
 *
 */
StatementList *create_statement_list(Statement *statement) {
    StatementList *sl = malloc(sizeof(StatementList));
    if (statement != NULL) {
        sl->statements = malloc(sizeof(Statement *));
        sl->count = 1;
        sl->statements[0] = statement;
    } else {
        sl->count = 0;
        sl->statements = NULL;
    }
    return sl;
}

/**
 *
 */
StatementList *flatten_statement_list(StatementList *list, Statement *element) {
    int new_size = list->count + 1;
    Statement **new_list = realloc(list->statements, new_size * sizeof(Statement *));
    list->statements = new_list;
    list->statements[list->count] = element;
    list->count++;
    return list;
}

/**
 *
 */
Statement *create_stmt_from_local_dec(LocalDeclaration *local_declaration) {
    Statement *s = malloc(sizeof(Statement));
    s->local_declaration = local_declaration;
    s->type = LOCAL_DECLARATION;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_if_stmt(IfStatement *if_statement) {
    Statement *s = malloc(sizeof(Statement));
    s->if_statement = if_statement;
    s->type = IF_STATEMENT;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_pm(PatternMatching *pattern_matching) {
    Statement *s = malloc(sizeof(Statement));
    s->pattern_matching = pattern_matching;
    s->type = PATTERN_MATCHING;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_pme(PatternMatchingExpr *pattern_matching_expr) {
    Statement *s = malloc(sizeof(Statement));
    s->pattern_matching_expr = pattern_matching_expr;
    s->type = PATTERN_MATCHING_EXPR;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_for_loop(ForLoop *for_loop) {
    Statement *s = malloc(sizeof(Statement));
    s->for_loop = for_loop;
    s->type = FOR_LOOP;
    return s;
}

/**
 *
 */
Statement *create_stmt_from_return_stmt(ReturnStatement *return_statement) {
    Statement *s = malloc(sizeof(Statement));
    s->return_statement = return_statement;
    s->type = RETURN_STATEMENT;
    return s;
}

/**
 *
 */
LocalDeclaration *create_local_declaration(VariableDec *variable_declaration, Expr *expr) {
    LocalDeclaration *ld = malloc(sizeof(LocalDeclaration));
    ld->variable_declaration = variable_declaration;
    ld->expr = expr;
    return ld;
}

/**
 *
 */
IfStatement *create_if_statement(IfBlock *if_block, IfOrBlockList *if_or_block_list, OrBlock *or_block) {
    IfStatement *if_statement = malloc(sizeof(IfStatement));
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
    if_block->statement_list = statement_list;
    if_block->expr = expr;
    return if_block;
}

/**
 *
 */
IfOrBlockList *create_if_or_block_list(IfOrBlock *if_or_block) {
    IfOrBlockList *if_or_block_list = malloc(sizeof(IfOrBlockList));
    if_or_block_list->if_or_blocks = malloc(sizeof(IfOrBlock *));
    if_or_block_list->count = 1;
    if_or_block_list->if_or_blocks[0] = if_or_block;
    return if_or_block_list;
}


/**
 *
 */
IfOrBlockList *flatten_if_or_block_list(IfOrBlockList *list, IfOrBlock *element) {
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
    if_or_block->statement_list = statement_list;
    if_or_block->expr = expr;
    return if_or_block;
}

/**
 *
 */
OrBlock *create_or_block(StatementList *statement_list) {
    OrBlock *or_block = malloc(sizeof(OrBlock));
    or_block->statement_list = statement_list;
    return or_block;
}

/**
 *
 */
PatternMatching *create_pattern_matching(PatternList *pattern_list) {
    PatternMatching *pattern_matching = malloc(sizeof(PatternMatching));
    pattern_matching->pattern_list = pattern_list;
    return pattern_matching;
}

/**
 *
 */
PatternMatchingExpr *create_pattern_matching_expr(Expr *condition, PatternList *pattern_list) {
    PatternMatchingExpr *pattern_matching = malloc(sizeof(PatternMatchingExpr *));
    pattern_matching->expr = condition;
    pattern_matching->pattern_list = pattern_list;
    return pattern_matching;
}

/**
 *
 */
Pattern *create_pattern_from_stmt_list(Expr *condition, StatementList *statement_list) {
    Pattern *pattern = malloc(sizeof(Pattern *));
    pattern->condition = condition;
    pattern->type = STMT_LIST_BODY;
    pattern->statement_list = statement_list;
    return pattern;
}

/**
 *
 */
Pattern *create_pattern_from_expr(Expr *condition, Expr *expr) {
    Pattern *pattern = malloc(sizeof(Pattern *));
    pattern->condition = condition;
    pattern->type = EXPR_BODY;
    pattern->expr = expr;
    return pattern;
}

/**
 *
 */
PatternList *create_pattern_list(Pattern *pattern) {
    PatternList *pl = malloc(sizeof(PatternList *));
    pl->patterns = malloc(sizeof(Pattern *));
    pl->count = 1;
    pl->patterns[0] = pattern;
    return pl;
}

/**
 *
 */
PatternList *flatten_pattern_list(PatternList *list, Pattern *element) {
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
ForLoop *create_for_loop_from_for_in(ForInLoop *for_in_loop, StatementList *statement_list) {
    ForLoop *for_loop = malloc(sizeof(ForLoop));
    for_loop->type = FOR_IN_LOOP;
    for_loop->statement_list = statement_list;
    for_loop->for_in_loop = for_in_loop;
    return for_loop;
}
/**
 *
 */
ForLoop *create_for_loop_from_while(WhileLoop *while_loop, StatementList *statement_list) {
    ForLoop *for_loop = malloc(sizeof(ForLoop));
    for_loop->type = WHILE_LOOP;
    for_loop->statement_list = statement_list;
    for_loop->while_loop = while_loop;
    return for_loop;
}
/**
 *
 */
ForLoop *create_for_loop_from_inf_loop(StatementList* statement_list) {
    ForLoop *for_loop = malloc(sizeof(ForLoop));
    for_loop->type = INFINITE_LOOP;
    for_loop->statement_list = statement_list;
    return for_loop;
}

/**
 *
 */
ForInLoop *create_for_in_loop(ExprList *expr_list, Expr *in_expr) {
    ForInLoop *for_loop_in = malloc(sizeof(ForInLoop));
    for_loop_in->expr_list = expr_list;
    for_loop_in->in_expr = in_expr;
    return for_loop_in;
}

/**
 *
 */
WhileLoop *create_while_loop(ExprList *expr_list) {
    WhileLoop *while_loop = malloc(sizeof(WhileLoop));
    while_loop->expr_list = expr_list;
    return while_loop;
}
/**
 *
 */
ReturnStatement *create_return_statement(ExprList *expr_list) {
    ReturnStatement *return_statement = malloc(sizeof(ReturnStatement));
    return_statement->expr_list = expr_list;
    return return_statement;
}

/**
 *
 */
Expr *create_expr_from_unary(UnaryExpr *unary_expr) {
    Expr *e = malloc(sizeof(Expr));
    e->unary_expr = unary_expr;
    e->type = UNARY;
    return e;
}

/**
 *
 */
Expr *create_expr_from_binary(BinaryExpr *binary_expr) {
    Expr *e = malloc(sizeof(Expr));
    e->binary_expr = binary_expr;
    e->type = BINARY;
    return e;
}

/**
 *
 */
ExprList *create_expr_list(Expr *expr) {
    ExprList *expr_list = malloc(sizeof(ExprList *));
    expr_list->exprs = malloc(sizeof(Expr *));
    expr_list->count = 1;
    expr_list->exprs[0] = expr;
    return expr_list;
}

/**
 *
 */
ExprList *flatten_expr_list(ExprList *list, Expr *element) {
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
    ue->integer_value = strdup(integer_value);
    ue->type = type;
    return ue;
}


/**
 *
 */
UnaryExpr *create_unary_expr_from_id(Identifier *identifier) {
    UnaryExpr *ue = malloc(sizeof(UnaryExpr));
    ue->identifier = identifier;
    ue->type = IDENTIFIER;
    return ue;
}

/**
 *
 */
VarDecList *create_var_dec_list(VariableDec *variable_dec) {
    VarDecList *vdl = malloc(sizeof(VarDecList));
    vdl->var_declarations = malloc(sizeof(VariableDec *));
    vdl->count = 1;
    vdl->var_declarations[0] = variable_dec;
    return vdl;
}

/**
 *
 */
VarDecList *flatten_var_dec_list(VarDecList *list, VariableDec *element) {
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
    vd->type = type;
    vd->identifier = identifier;
    return vd;
}

/**
 *
 */
Identifier *create_identifier(const char *name) {
    Identifier *id = malloc(sizeof(Identifier));
    id->name = strdup(name);
    return id;
}

/**
 *
 */
Type *create_type(const char *name) {
    Type *t = malloc(sizeof(Type));
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
TypeList *flatten_type_list(TypeList *list, Type *element) {
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
    switch (obj->type) {
        case OBJECT_ENTITY:
            free_object_file(obj->object_file);
            break;
        case INTERFACE_ENTITY:
        case ENUM_ENTITY:
            break;
    }
}

/**
 *
 */
void free_object_file(ObjectFile *obj) {
    free_fields_block(obj->fields_block);
    free_methods_block_list(obj->methods_block_list);
    free_implements_block(obj->implements_block);
    free(obj->id);
    free(obj);
}

/**
 *
 */
void free_implements_block(ImplementsBlock *ib) {
    free_type_list(ib->type_list);
    free(ib);
}

/**
 *
 */
void free_fields_block(FieldsBlock *fb) {
    free_field_list(fb->field_list);
    free(fb);
}

/**
 *
 */
void free_field_list(FieldList *fl) {
    for (int i = 0; i < fl->count; i++) {
        free_field(fl->fields[i]);
    }
    free(fl->fields);
    free(fl);
}

/**
 *
 */
void free_field(Field *f) {
    free_variable_declaration(f->variable_declaration);
    free_type(f->implements);
    free(f);
}

/**
 *
 */
void free_methods_block_list(MethodsBlockList *mbl) {
    for (int i = 0; i < mbl->count; i++) {
        free_methods_block(mbl->blocks[i]);
    }
    free(mbl->blocks);
    free(mbl);
}

/**
 *
 */
void free_methods_block(MethodsBlock *mb) {
    free_identifier(mb->identifier);
    free_methods_list(mb->methods_list);
    free(mb);
}

/**
 *
 */
void free_methods_list(MethodsList *ml) {
    for (int i = 0; i < ml->count; i++) {
        free_method(ml->methods[i]);
    }
    free(ml->methods);
    free(ml);
}

/**
 *
 */
void free_method(Method *m) {
    free_method_signature(m->method_signature);
    free_statement_list(m->statement_list);
    free(m);
}

/**
 *
 */
void free_method_signature(MethodSignature *ms) {
    free_method_header(ms->method_header);
    free_variable_declaration_list(ms->variable_declaration_list);
    free(ms);
}

/**
 *
 */
void free_method_header(MethodHeader *mh) {
    free_variable_declaration(mh->variable_declaration);
    free(mh);
}

/**
 *
 */
void free_statement_list(StatementList *sl) {
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
    switch (s->type) {
        case LOCAL_DECLARATION:
            free_local_declaration(s->local_declaration);
            break;
        case IF_STATEMENT:
            free_if_statement(s->if_statement);
            break;
        case PATTERN_MATCHING:
            free_pattern_matching(s->pattern_matching);
            break;
        case PATTERN_MATCHING_EXPR:
            free_pattern_matching_expr(s->pattern_matching_expr);
            break;
        case FOR_LOOP:
            free_for_loop(s->for_loop);
            break;
        case RETURN_STATEMENT:
            free_return_statement(s->return_statement);
            break;
    }
    free(s);
}

/**
 *
 */
void free_local_declaration(LocalDeclaration *ld) {
    free_variable_declaration(ld->variable_declaration);
    free_expr(ld->expr);
    free(ld);
}

/**
 *
 */
void free_if_statement(IfStatement *is) {
    free_if_block(is->if_block);
    free_or_block(is->or_block);
    free_if_or_block_list(is->if_or_block_list);
    free(is);
}

/**
 *
 */
void free_if_block(IfBlock *ib) {
    free_expr(ib->expr);
    free_statement_list(ib->statement_list);
    free(ib);
}

/**
 *
 */
void free_if_or_block_list(IfOrBlockList *iobl) {
    for (int i = 0; i < iobl->count; i++) {
        free_if_or_block(iobl->if_or_blocks[i]);
    }
    free(iobl);
}

/**
 *
 */
void free_if_or_block(IfOrBlock *iob) {
    free_expr(iob->expr);
    free_statement_list(iob->statement_list);
    free(iob);
}

/**
 *
 */
void free_or_block(OrBlock *ob) {
    free_statement_list(ob->statement_list);
    free(ob);
}

/**
 *
 */
void free_pattern(Pattern *p) {
    switch (p->type) {
        case EXPR_BODY:
            free_expr(p->expr);
            break;
        case STMT_LIST_BODY:
            free_statement_list(p->statement_list);
            break;
    }
    free(p);
}

/**
 *
 */
void free_pattern_list(PatternList *pl) {
    for (int i = 0; i < pl->count; i++) {
        free_pattern(pl->patterns[i]);
    }
    free(pl);
}

/**
 *
 */
void free_pattern_matching(PatternMatching *pm) {
    free_pattern_list(pm->pattern_list);
    free(pm);
}

/**
 *
 */
void free_pattern_matching_expr(PatternMatchingExpr *pme) {
    free_expr(pme->expr);
    free_pattern_list(pme->pattern_list);
    free(pme);
}

/**
 *
 */
void free_for_loop(ForLoop *fl) {
    switch (fl->type) {
        case WHILE_LOOP:
            free_while_loop(fl->while_loop);
            break;
        case FOR_IN_LOOP:
            free_for_in_loop(fl->for_in_loop);
            break;
        case INFINITE_LOOP:
            break;
    }
    free_statement_list(fl->statement_list);
    free(fl);
}

/**
 *
 */
void free_for_in_loop(ForInLoop *fli) {
    free_expr_list(fli->expr_list);
    free_expr(fli->in_expr);
    free(fli);
}

/**
 *
 */
void free_while_loop(WhileLoop *wl) {
    free_expr_list(wl->expr_list);
    free(wl);
}

/**
 *
 */
void free_return_statement(ReturnStatement *rs) {
    free_expr_list(rs->expr_list);
    free(rs);
}

/**
 *
 */
void free_expr(Expr *e) {
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
    for (int i = 0; i < el->count; ++i) {
        free_expr(el->exprs[i]);
    }
    free(el);
}

/**
 *
 */
void free_binary_expr(BinaryExpr *be) {
    free_expr(be->left);
    free_expr(be->right);
    free(be);
}

/**
 *
 */
void free_unary_expr(UnaryExpr *ue) {
    free(ue->integer_value);
    free(ue->float_value);
    free_identifier(ue->identifier);
    free(ue);
}

/**
 *
 */
void free_variable_declaration_list(VarDecList *vdl) {
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
    free_type(vd->type);
    free_identifier(vd->identifier);
    free(vd);
}

/**
 *
 */
void free_identifier(Identifier *i) {
    free(i->name);
    free(i);
}

/**
 *
 */
void free_type(Type *t) {
    free(t->name);
    free(t);
}

/**
 *
 */
void free_type_list(TypeList *tl) {
    for (int i = 0; i < tl->count; i++) {
        free_type(tl->types[i]);
    }
    free(tl->types);
    free(tl);
}
