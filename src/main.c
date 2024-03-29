#include "../include/configurations.h"
#include "../include/ntodo.h"
#include "../include/ui.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void unknownCommand(char *command) {
    fprintf(stderr, "ntodo: %s: unknown command.\n", command);
    usage();
}

int main(int argc, char **argv) {
    Configurations *configurations      =        newConfiguarations("/root/.ntodo.conf");
    VM *vm                              =        newVM(configurations);
    if (argv[1]                         == NULL) usage();
    else if (strcmp(argv[1], "add")     == 0)    add(vm, argc, argv);
    else if (strcmp(argv[1], "remove")  == 0)    removes(vm, argc, argv);
    else if (strcmp(argv[1], "check")   == 0)    check(vm, argc, argv);
    else if (strcmp(argv[1], "uncheck") == 0)    uncheck(vm, argc, argv);
    else if (strcmp(argv[1], "toggle")  == 0)    toggle(vm, argc, argv);
    else if (strcmp(argv[1], "dest")    == 0)    dest(vm);
    else if (strcmp(argv[1], "list")    == 0)    list(vm, argc, argv);
    else if (strcmp(argv[1], "update")  == 0)    update(vm);
    else if (strcmp(argv[1], "raw")     == 0)    _raw(vm);
    else if (strcmp(argv[1], "ui")      == 0)    runUi(vm);
    else                                         unknownCommand(argv[1]);
    return 0;
}
