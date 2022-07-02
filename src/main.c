#include "../include/configurations.h"
#include "../include/ntodo.h"
#include <stdio.h>


int main(int argc, char **argv) {
    Configurations *configurations = newConfiguarations("/root/.ntodo.conf");
    VM *vm                         = newVM(configurations);
    list(vm, argc, argv);
    return 0;
}
