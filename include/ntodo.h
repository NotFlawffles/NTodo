#ifndef NTODO_H
#define NTODO_H
#include "ast.h"
#include "configurations.h"

typedef struct {
    Configurations *configurations;
    Ast **todos;
} VM;

VM *newVM(Configurations *configurations);
Ast **readTodos(VM *vm);
void add(VM *vm,     int argc, char **argv);
void removes(VM *vm, int argc, char **argv);
void check(VM *vm,   int argc, char **argv);
void uncheck(VM *vm, int argc, char **argv);
void dest(VM *vm,    int argc, char **argv);
void list(VM *vm,    int argc, char **argv);
void update(VM *vm,  int argc, char **argv);

#endif // NTODO_H
