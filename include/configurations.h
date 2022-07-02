#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H
#include <stdbool.h>

typedef struct {
    char *ntodoFilePath;
    bool useRemoval;
} Configurations;

Configurations *newConfiguarations(char *fileName);

#endif // CONFIGURATIONS_H
