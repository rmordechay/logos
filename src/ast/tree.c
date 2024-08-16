#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"

/**
 *
 */
void analyse_ast(ObjectFile *root) {
    printf("%s\n", root->name->name);
}

/**
 *
 */
ObjectFile *create_object_file(Identifier *name,
                               ImplementsBlock *implements_block,
                               FieldsBlock *fields_block,
                               MethodsBlockList *methods_block_list) {
    ObjectFile* obj = malloc(sizeof(ObjectFile));
    obj->name = name;
    obj->fields_block = fields_block;
    obj->implements_block = implements_block;
    obj->methods_block_list = methods_block_list;
    return obj;
}

/**
 *
 */
Title *create_title(Identifier *name) {
    Title *title = malloc(sizeof(Title));
    title->name = name;
    return title;
}

/**
 *
 */
ImplementsBlock* create_implements_block(TypeList* type_list) {
    ImplementsBlock* ib = malloc(sizeof(ImplementsBlock));
    ib->type_list = type_list;
    return ib;
}

/**
 *
 */
FieldsBlock* create_fields_block(FieldList* field_list) {
    FieldsBlock* fb = malloc(sizeof(FieldsBlock));
    fb->field_list = field_list;
    return fb;
}

/**
 *
 */
FieldList* create_field_list(int count) {
    FieldList* fl = malloc(sizeof(FieldList));
    fl->fields = malloc(sizeof(Field*) * count);
    fl->count = count;
    return fl;
}

/**
 *
 */
Field* create_field(VariableDec *variable_declaration, Type* type) {
    Field* f = malloc(sizeof(Field));
    f->variable_declaration = variable_declaration;
    f->type = type;
    return f;
}

/**
 *
 */
MethodsBlockList* create_methods_block_list(int count) {
    MethodsBlockList* mbl = malloc(sizeof(MethodsBlockList));
    mbl->blocks = malloc(sizeof(MethodsBlock*) * count);
    mbl->count = count;
    return mbl;
}

/**
 *
 */
MethodsBlock* create_methods_block(Identifier* identifier, MethodsList* methods_list) {
    MethodsBlock* mb = malloc(sizeof(MethodsBlock));
    mb->identifier = identifier;
    mb->methods_list = methods_list;
    return mb;
}

/**
 *
 */
MethodsList* create_methods_list(int count) {
    MethodsList* ml = malloc(sizeof(MethodsList));
    ml->methods = malloc(sizeof(Method*) * count);
    ml->count = count;
    return ml;
}

/**
 *
 */
Method* create_method(MethodSignature* method_signature, StatementList* statement_list) {
    Method* m = malloc(sizeof(Method));
    m->method_signature = method_signature;
    m->statement_list = statement_list;
    return m;
}

/**
 *
 */
MethodSignature* create_method_signature(MethodHeader* method_header, VariableDeclarationList* variable_declaration_list) {
    MethodSignature* ms = malloc(sizeof(MethodSignature));
    ms->method_header = method_header;
    ms->variable_declaration_list = variable_declaration_list;
    return ms;
}

/**
 *
 */
MethodHeader* create_method_header(VariableDec* variable_declaration) {
    MethodHeader* mh = malloc(sizeof(MethodHeader));
    mh->variable_declaration = variable_declaration;
    return mh;
}

/**
 *
 */
StatementList* create_statement_list(int count) {
    StatementList* sl = malloc(sizeof(StatementList));
    sl->statements = malloc(sizeof(Statement*) * count);
    sl->count = count;
    return sl;
}

/**
 *
 */
Statement* create_statement(LocalDeclaration* local_declaration) {
    Statement* s = malloc(sizeof(Statement));
    s->local_declaration = local_declaration;
    return s;
}

/**
 *
 */
LocalDeclaration* create_local_declaration(VariableDec* variable_declaration, Expr* expr) {
    LocalDeclaration* ld = malloc(sizeof(LocalDeclaration));
    ld->variable_declaration = variable_declaration;
    ld->expr = expr;
    return ld;
}

/**
 *
 */
Expr* create_expr_unary(UnaryExpr* unary_expr) {
    Expr* e = malloc(sizeof(Expr));
    e->unary_expr = unary_expr;
    return e;
}

/**
 *
 */
Expr* create_expr_binary(BinaryExpr* binary_expr) {
    Expr* e = malloc(sizeof(Expr));
    e->binary_expr = binary_expr;
    return e;
}

/**
 *
 */
BinaryExpr* create_binary_expr(Expr* left, Expr* right, char operator) {
    BinaryExpr* be = malloc(sizeof(BinaryExpr));
    be->left = left;
    be->right = right;
    be->operator = operator;
    return be;
}

/**
 *
 */
UnaryExpr* create_unary_expr_int(char* integer_value) {
    UnaryExpr* ue = malloc(sizeof(UnaryExpr));
    ue->integer_value = strdup(integer_value);
    return ue;
}

/**
 *
 */
UnaryExpr* create_unary_expr_float(char* float_value) {
    UnaryExpr* ue = malloc(sizeof(UnaryExpr));
    ue->float_value = strdup(float_value);
    return ue;
}

/**
 *
 */
UnaryExpr* create_unary_expr_id(Identifier* identifier) {
    UnaryExpr* ue = malloc(sizeof(UnaryExpr));
    ue->identifier = identifier;
    return ue;
}

/**
 *
 */
VariableDeclarationList* create_variable_declaration_list(int count) {
    VariableDeclarationList* vdl = malloc(sizeof(VariableDeclarationList));
    vdl->declarations = malloc(sizeof(VariableDec*) * count);
    vdl->count = count;
    return vdl;
}

/**
 *
 */
VariableDec* create_variable_declaration(Type* type, Identifier* identifier) {
    VariableDec* vd = malloc(sizeof(VariableDec));
    vd->type = type;
    vd->identifier = identifier;
    return vd;
}

/**
 *
 */
Identifier* create_identifier(const char* name) {
    Identifier* id = malloc(sizeof(Identifier));
    id->name = strdup(name);
    return id;
}

/**
 *
 */
Type* create_type(const char* name) {
    Type* t = malloc(sizeof(Type));
    t->name = strdup(name);
    return t;
}

/**
 *
 */
TypeList* create_type_list(int count) {
    TypeList* tl = malloc(sizeof(TypeList));
    tl->types = malloc(sizeof(Type*) * count);
    tl->count = count;
    return tl;
}


/**
 *
 */
void free_object_file(ObjectFile* obj) {
    if (obj == NULL) return;
    free_fields_block(obj->fields_block);
    free_methods_block_list(obj->methods_block_list);
    free_implements_block(obj->implements_block);
    free(obj->name);
    free(obj);
}

/**
 *
 */
void free_title(Title *title) {
    free_identifier(title->name);
}

/**
 *
 */
void free_implements_block(ImplementsBlock* ib) {
    if (ib == NULL) return;
    free_type_list(ib->type_list);
    free(ib);
}

/**
 *
 */
void free_fields_block(FieldsBlock* fb) {
    if (fb == NULL) return;
    free_field_list(fb->field_list);
    free(fb);
}

/**
 *
 */
void free_field_list(FieldList* fl) {
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
void free_field(Field* f) {
    if (f == NULL) return;
    free_variable_declaration(f->variable_declaration);
    free_type(f->type);
    free(f);
}

/**
 *
 */
void free_methods_block_list(MethodsBlockList* mbl) {
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
void free_methods_block(MethodsBlock* mb) {
    if (mb == NULL) return;
    free_identifier(mb->identifier);
    free_methods_list(mb->methods_list);
    free(mb);
}

/**
 *
 */
void free_methods_list(MethodsList* ml) {
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
void free_method(Method* m) {
    if (m == NULL) return;
    free_method_signature(m->method_signature);
    free_statement_list(m->statement_list);
    free(m);
}

/**
 *
 */
void free_method_signature(MethodSignature* ms) {
    if (ms == NULL) return;
    free_method_header(ms->method_header);
    free_variable_declaration_list(ms->variable_declaration_list);
    free(ms);
}

/**
 *
 */
void free_method_header(MethodHeader* mh) {
    if (mh == NULL) return;
    free_variable_declaration(mh->variable_declaration);
    free(mh);
}

/**
 *
 */
void free_statement_list(StatementList* sl) {
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
void free_statement(Statement* s) {
    if (s == NULL) return;
    free_local_declaration(s->local_declaration);
    free(s);
}

/**
 *
 */
void free_local_declaration(LocalDeclaration* ld) {
    if (ld == NULL) return;
    free_variable_declaration(ld->variable_declaration);
    free_expr(ld->expr);
    free(ld);
}

/**
 *
 */
void free_expr(Expr* e) {
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
void free_binary_expr(BinaryExpr* be) {
    if (be == NULL) return;
    free_expr(be->left);
    free_expr(be->right);
    free(be);
}

/**
 *
 */
void free_unary_expr(UnaryExpr* ue) {
    if (ue == NULL) return;
    free(ue->integer_value);
    free(ue->float_value);
    free_identifier(ue->identifier);
    free(ue);
}

/**
 *
 */
void free_variable_declaration_list(VariableDeclarationList* vdl) {
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
void free_variable_declaration(VariableDec* vd) {
    if (vd == NULL) return;
    free_type(vd->type);
    free_identifier(vd->identifier);
    free(vd);
}

/**
 *
 */
void free_identifier(Identifier* id) {
    if (id == NULL) return;
    free(id->name);
    free(id);
}

/**
 *
 */
void free_type(Type* t) {
    if (t == NULL) return;
    free(t->name);
    free(t);
}

/**
 *
 */
void free_type_list(TypeList* tl) {
    if (tl == NULL) return;
    for (int i = 0; i < tl->count; i++) {
        free_type(tl->types[i]);
    }
    free(tl->types);
    free(tl);
}
