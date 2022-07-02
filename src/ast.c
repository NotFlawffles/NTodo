#include "../include/ast.h"
#include <malloc.h>


Ast *newAst(char *name, char *description, bool checked, bool removable) {
    Ast *ast         = (Ast *) malloc(sizeof(Ast));
    ast->name        = name;
    ast->description = description;
    ast->checked     = checked;
    ast->removable   = removable;
    return ast;
}
