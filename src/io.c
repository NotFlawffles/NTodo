#include "../include/io.h"
#include <stdio.h>
#include <malloc.h>


char *readFile(char *fileName) {
    FILE *file    = fopen(fileName, "r");
    fseek(file, 0, SEEK_END);
    long size     = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *content = malloc(size * sizeof(char));
    fread(content, 1, size, file);
    return content;
}
