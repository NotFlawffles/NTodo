#include "../include/generator.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>


char *generate(Ast *todo) {
    char *line = (char *) malloc((strlen(todo->name) + strlen(todo->description) + 4) * sizeof(char));
    strcat(line, todo->name);
    strcat(line, (char []) {' ', 0});
    strcat(line, (char []) {'\"', 0});
    strcat(line, todo->description);
    strcat(line, (char []) {'\"', 0});
    strcat(line, (char []) {' ', 0});
    if (todo->checked) {
        line = realloc(line, (strlen(line) + strlen("checked") + 1) * sizeof(char));
        strcat(line, "checked");
    } else {
        line = realloc(line, (strlen(line) + strlen("unchecked") + 1) * sizeof(char));
        strcat(line, "unchecked");
    }
    strcat(line, (char []) {' ', 0});
    if (todo->removable) {
        line = realloc(line, (strlen(line) + strlen("removable")) * sizeof(char));
        strcat(line, "removable");
    } else {
        line = realloc(line, (strlen(line) + strlen("unremovable")) * sizeof(char));
        strcat(line, "unremovable");
    }
    return line;
}
