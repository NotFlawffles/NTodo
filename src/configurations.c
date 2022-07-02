#include "../include/configurations.h"
#include "../include/io.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


Configurations *newConfiguarations(char *fileName) {
    Configurations *configs = (Configurations *) malloc(sizeof(Configurations));
    char *content           = readFile(fileName);
    Lexer *lexer            = newLexer(content);
    Parser *parser          = newParser(lexer);
    Ast **ast               = parse(parser);
    for (int i = 0; ast[i] != NULL; i++) {
        if (strcmp(ast[i]->name, "ntodo_src") == 0) {
            configs->ntodoFilePath = ast[i]->description;
        } else if (strcmp(ast[i]->name, "use_removal") == 0) {
            if (strcmp(ast[i]->description, "true") == 0) {
                configs->useRemoval = true;
            } else if (strcmp(ast[i]->description, "false") == 0) {
                configs->useRemoval = false;
            } else {
                fprintf(stderr, "ntodo: %s: unknown value for option %s\n", ast[i]->description, ast[i]->name);
                exit(1);
            }
        }
    }
    return configs;
}
