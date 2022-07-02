#include "../include/ntodo.h"
#include "../include/io.h"
#include "../include/configurations.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include <malloc.h>
#include <stdio.h>


VM *newVM(Configurations *configurations) {
    VM *vm             = (VM *) malloc(sizeof(VM));
    vm->configurations = configurations;
    vm->todos          = readTodos(vm);
    return vm;
}

Ast **readTodos(VM *vm) {
    char *source   = readFile(vm->configurations->ntodoFilePath);
    Lexer *lexer   = newLexer(source);
    Parser *parser = newParser(lexer);
    return parse(parser);
}

void add(VM *vm, int argc, char **argv) {

}

void removes(VM *vm, int argc, char **argv) {

}

void check(VM *vm, int argc, char **argv) {

}

void uncheck(VM *vm, int argc, char **argv) {

}

void dest(VM *vm, int argc, char **argv) {

}

void list(VM *vm, int argc, char **argv) {
    bool removeFiles;
    int removeFilesCount = 0;
    if (argc == 2) {
        for (int i = 0; vm->todos[i] != NULL; i++) {
            if (vm->todos[i]->checked) printf("[x] - ");
            else printf("[ ] - ");
            printf("%s: %s", vm->todos[i]->name, vm->todos[i]->description);
            if (vm->todos[i]->removable) {
                removeFilesCount++;
                removeFiles = true;
                printf(", on remove state");
            }
            printf(".\n");
        }
        if (removeFiles) {
            printf("%d TODOs are ready to be removed\nrun `ntodo update`", removeFilesCount);
        }
    }
}

void update(VM *vm, int argc, char **argv) {

}
