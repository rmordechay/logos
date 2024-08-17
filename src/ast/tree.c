#include <stdlib.h>
#include <string.h>
#include <printf.h>
#include "tree.h"
#include "parser.h"

void print_object_file_json(ObjectFile *object_file);

/**
 *
 */
void analyse_ast(ObjectFile *root) {
    print_object_file_json(root);
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
FieldList *flatten_field_list(FieldList *field_list, Field *field) {
    int i = field_list->count;
    Field **new_list = realloc(field_list->fields, i * sizeof(Field *));
    field_list->fields = new_list;
    field_list->fields[i] = field;
    field_list->count++;
    return field_list;
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
MethodsBlockList *flatten_methods_block_list(MethodsBlockList *methods_block_list, MethodsBlock *methods_block) {
    int i = methods_block_list->count;
    MethodsBlock **new_list = realloc(methods_block_list->blocks, i * sizeof(MethodsBlock *));
    methods_block_list->blocks = new_list;
    methods_block_list->blocks[i] = methods_block;
    methods_block_list->count++;
    return methods_block_list;
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
MethodsList *flatten_methods_list(MethodsList *methods_list, Method *method) {
    int i = methods_list->count;
    Method **new_list = realloc(methods_list->methods, i * sizeof(Method *));
    methods_list->methods = new_list;
    methods_list->methods[i] = method;
    methods_list->count++;
    return methods_list;
}

/**
 *
 */
Method *create_method(MethodSignature *method_signature, StatementList *statement_list) {
    Method *m = malloc(sizeof(Method));
    m->method_signature = method_signature;
    m->statement_list = statement_list;
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
    if (statement == NULL) {
        return sl;
    } else {
        sl->statements = malloc(sizeof(Statement *));
        sl->count = 1;
        sl->statements[0] = statement;
        return sl;
    }
}

/**
 *
 */
StatementList *flatten_statement_list(StatementList *statement_list, Statement *statement) {
    int i = statement_list->count;
    Statement **new_list = realloc(statement_list->statements, i * sizeof(Statement *));
    statement_list->statements = new_list;
    statement_list->statements[i] = statement;
    statement_list->count++;
    return statement_list;
}

/**
 *
 */
Statement *create_statement(LocalDeclaration *local_declaration) {
    Statement *s = malloc(sizeof(Statement));
    s->local_declaration = local_declaration;
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
    if_or_block_list->count = 1;
    if_or_block_list->if_or_blocks[0] = if_or_block;
    return if_or_block_list;
}


/**
 *
 */
IfOrBlockList *flatten_if_or_block_list(IfOrBlockList *if_or_block_list, IfOrBlock *if_or_block) {
    int i = if_or_block_list->count;
    IfOrBlock **new_list = realloc(if_or_block_list->if_or_blocks, i * sizeof(IfOrBlock *));
    if_or_block_list->if_or_blocks = new_list;
    if_or_block_list->if_or_blocks[i] = if_or_block;
    if_or_block_list->count++;
    return if_or_block_list;
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
UnaryExpr *create_unary_expr_number(int type, char *integer_value) {
    UnaryExpr *ue = malloc(sizeof(UnaryExpr));
    ue->integer_value = strdup(integer_value);
    ue->type = type;
    return ue;
}

/**
 *
 */
UnaryExpr *create_unary_expr_id(Identifier *identifier) {
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
    vdl->declarations = malloc(sizeof(VariableDec *));
    vdl->count = 1;
    vdl->declarations[0] = variable_dec;
    return vdl;
}

/**
 *
 */
VarDecList *flatten_var_dec_list(VarDecList *var_dec_list, VariableDec *variable_dec) {
    int i = var_dec_list->count;
    VariableDec **new_list = realloc(var_dec_list->declarations, i * sizeof(VariableDec *));
    var_dec_list->declarations = new_list;
    var_dec_list->declarations[i] = variable_dec;
    var_dec_list->count++;
    return var_dec_list;
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
TypeList *flatten_type_list(TypeList *type_list, Type *type) {
    int i = type_list->count;
    Type **new_list = realloc(type_list->types, i * sizeof(Type *));
    type_list->types = new_list;
    type_list->types[i] = type;
    type_list->count++;
    return type_list;
}

/**
 *
 */
void free_object_file(ObjectFile *obj) {
    if (obj == NULL) return;
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
    if (ib == NULL) return;
    free_type_list(ib->type_list);
    free(ib);
}

/**
 *
 */
void free_fields_block(FieldsBlock *fb) {
    if (fb == NULL) return;
    free_field_list(fb->field_list);
    free(fb);
}

/**
 *
 */
void free_field_list(FieldList *fl) {
    if (fl == NULL) return;
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
    if (f == NULL) return;
    free_variable_declaration(f->variable_declaration);
    free_type(f->implements);
    free(f);
}

/**
 *
 */
void free_methods_block_list(MethodsBlockList *mbl) {
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
void free_methods_block(MethodsBlock *mb) {
    if (mb == NULL) return;
    free_identifier(mb->identifier);
    free_methods_list(mb->methods_list);
    free(mb);
}

/**
 *
 */
void free_methods_list(MethodsList *ml) {
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
void free_method(Method *m) {
    if (m == NULL) return;
    free_method_signature(m->method_signature);
    free_statement_list(m->statement_list);
    free(m);
}

/**
 *
 */
void free_method_signature(MethodSignature *ms) {
    if (ms == NULL) return;
    free_method_header(ms->method_header);
    free_variable_declaration_list(ms->variable_declaration_list);
    free(ms);
}

/**
 *
 */
void free_method_header(MethodHeader *mh) {
    if (mh == NULL) return;
    free_variable_declaration(mh->variable_declaration);
    free(mh);
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
        case LOCAL_DEC:
            free_local_declaration(s->local_declaration);
            break;
        case IF_STMT:
            free_if_statement(s->if_statement);
            break;
    }
    free(s);
}

/**
 *
 */
void free_local_declaration(LocalDeclaration *ld) {
    if (ld == NULL) return;
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
    free(ue->integer_value);
    free(ue->float_value);
    free_identifier(ue->identifier);
    free(ue);
}

/**
 *
 */
void free_variable_declaration_list(VarDecList *vdl) {
    if (vdl == NULL) return;
    for (int i = 0; i < vdl->count; i++) {
        free_variable_declaration(vdl->declarations[i]);
    }
    free(vdl->declarations);
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
void free_identifier(Identifier *i) {
    if (i == NULL) return;
    free(i->name);
    free(i);
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
