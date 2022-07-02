#ifndef AST_H
#define AST_H
#include <stdbool.h>

typedef struct {
    char *name;
    char *description;
    bool checked;
    bool removable;
} Ast;

/*
 * example
 * sleep "go to sleep" unchecked
 * sleep "go to sleep" checked removable
 * `ntodo update` to remove that ^ todo after using
 * the command `ntodo remove <todo-name>`
 * otherwise to prevent removal do `ntodo keep <todo-name>`
 */

Ast *newAst(char *name, char *description, bool checked, bool removable);

#endif // AST_H
