#include "../include/ntodo.h"
#include "../include/io.h"
#include "../include/configurations.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/generator.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


VM *newVM(Configurations *configurations) {
    VM *vm             = (VM *) malloc(sizeof(VM));
    vm->configurations = configurations;
    if (readFile(vm->configurations->ntodoFilePath) == NULL) {
        fprintf(stderr, "ntodo: %s: todos file not found.\nmake a new todos file in the shown path or specify your own path to a `.ntodos` file. for more information run ntodo --help config\n", vm->configurations->ntodoFilePath);
        exit(1);
    }
    vm->todos          = readTodos(vm);
    return vm;
}

Ast **readTodos(VM *vm) {
    char *source   = readFile(vm->configurations->ntodoFilePath);
    Lexer *lexer   = newLexer(source);
    Parser *parser = newParser(lexer);
    return parse(parser);
}

void usage(void) {
    printf("useage: ntodo [[add] <argument> <sub-argunent> | [remove | check | uncheck | update | list] <argumentS> | [update] | [list] | [list]]\n");
    exit(1);
}

void add(VM *vm, int argc, char **argv) {
    if (argc < 4) usage();
    for (int i = 0; vm->todos[i] != NULL; i++) {
        if (strcmp(vm->todos[i]->name, argv[2]) == 0) {
            fprintf(stderr, "ntodo: %s: todo already exist.\nno todo has been added\n", vm->todos[i]->name);
            exit(1);
        }
    }
    writeFile(vm->configurations->ntodoFilePath, generate(newAst(argv[2], argv[3], false, false)));
    printf("ntodo: added todo: (%s: \"%s\")\n", argv[2], argv[3]);
}

void removes(VM *vm, int argc, char **argv) {
    clearFile(vm->configurations->ntodoFilePath);
    for (int i = 2; i < argc; i++) {
        for (int j = 0; vm->todos[j] != NULL; j++) {
            if (strcmp(vm->todos[j]->name, argv[i]) == 0 && !vm->todos[j]->removable) vm->todos[j]->removable = true;
            writeFile(vm->configurations->ntodoFilePath, generate(vm->todos[j]));
        }
    }
}

void check(VM *vm, int argc, char **argv) {
    clearFile(vm->configurations->ntodoFilePath);
    for (int i = 2; i < argc; i++) {
        for (int j = 0; vm->todos[j]; j++) {
            if (strcmp(vm->todos[j]->name, argv[i]) == 0 && !vm->todos[j]->checked) vm->todos[j]->checked = true;
            writeFile(vm->configurations->ntodoFilePath, generate(vm->todos[j]));
        }
    }
}

void uncheck(VM *vm, int argc, char **argv) {
    clearFile(vm->configurations->ntodoFilePath);
    for (int i = 2; i < argc; i++) {
        for (int j = 0; vm->todos[j]; j++) {
            if (strcmp(vm->todos[j]->name, argv[i]) == 0 && vm->todos[j]->checked) vm->todos[j]->checked = false;
            writeFile(vm->configurations->ntodoFilePath, generate(vm->todos[j]));
        }
    }   
}

void dest(VM *vm, int argc, char **argv) {
    printf("%s\n", vm->configurations->ntodoFilePath);
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
            printf("%d TODOs are ready to be removed\nrun `ntodo update` to update the todos\n", removeFilesCount);
        }
    } else {
        for (int i = 2; i < argc; i++) {
            for (int j = 0; vm->todos[j] != NULL; j++) {
                if (strcmp(vm->todos[j]->name, argv[i]) == 0) {
                    if (vm->todos[j]->checked) printf("[x] - ");
                    else printf("[ ] - ");
                    printf("%s: %s.\n", vm->todos[j]->name, vm->todos[j]->description);
                } else if (strcmp(argv[i], "removable") == 0 && vm->todos[j]->removable) {
                    if (vm->todos[j]->checked) printf("[x] - ");
                    else printf("[ ] - ");
                    printf("%s: %s.\n", vm->todos[j]->name, vm->todos[j]->description);
                } else if (strcmp(argv[i], "unremovable") == 0 && !vm->todos[j]->removable) {
                    if (vm->todos[j]->checked) printf("[x] - ");
                    else printf("[ ] - ");
                    printf("%s: %s.\n", vm->todos[j]->name, vm->todos[j]->description);
                }
            }
        }
    }
}

void update(VM *vm, int argc, char **argv) {
    clearFile(vm->configurations->ntodoFilePath);
    if (argc > 2) {
        printf("ntodo: update takes no arguments.\n");
        exit(1);
    }
    int removedCount = 0;
    for (int i = 0; vm->todos[i] != NULL; i++) {
        if (!vm->todos[i]->removable) writeFile(vm->configurations->ntodoFilePath, generate(vm->todos[i]));
        else removedCount++;
    }
    printf("ntodo: successfully updated TODOs, %d TODOs has been removed.\n", removedCount);
}
