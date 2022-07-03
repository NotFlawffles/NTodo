#include "../include/parser.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Parser *newParser(Lexer *lexer) {
    Parser *parser  = (Parser *) malloc(sizeof(Parser));
    parser->lexer   = lexer;
    parser->current = nextToken(lexer);
    parser->line    = 1;
    return parser;
}

Ast **parse(Parser *parser) {
    Ast **compound = (Ast **) malloc(sizeof(Ast *));
    size_t size    = 0;
    while (parser->current->type != TOKEN_EOF) {
        if (parser->current->type == TOKEN_NEWLINE) {
            parser->line++;
            eat(parser, TOKEN_NEWLINE);
            continue;
        }
        char *name        = parser->current->value;
        eat(parser, TOKEN_IDENTIFIER);
        if (parser->current->type == TOKEN_ASSIGN) {
            eat(parser, TOKEN_ASSIGN);
            char *description = parser->current->value;
            eat(parser, TOKEN_STRING);
            eat(parser, TOKEN_NEWLINE);
            parser->line++;
            compound         = realloc(compound, (sizeof(compound) + sizeof(Ast *)) * sizeof(Ast));
            compound[size++] = newAst(name, description, 0, 0);           
            continue;
        }
        char *description = parser->current->value;
        eat(parser, TOKEN_STRING);
        bool checked;
        if (strcmp(parser->current->value, "unchecked") == 0) {
            checked       = false;
        } else if (strcmp(parser->current->value, "checked") == 0) {
            checked       = true;
        } else {
            fprintf(stderr, "ntodo: %s: unknown option. at line %d\n", parser->current->value, parser->line);
            exit(1);
        }
        eat(parser, TOKEN_IDENTIFIER);
        bool removable;
        if (parser->current->type == TOKEN_IDENTIFIER) {
            if (strcmp(parser->current->value, "removable") == 0) {
                removable = true;
            } else if (strcmp(parser->current->value, "unremovable") == 0) {
                removable = false;
            } else {
                fprintf(stderr, "ntodo: %s: unknown option. at line %d\n", parser->current->value, parser->line);
                exit(1);
            }
            eat(parser, TOKEN_IDENTIFIER);
            eat(parser, TOKEN_NEWLINE);
        } else {
            eat(parser, TOKEN_NEWLINE);
        }
        parser->line++;
        compound         = realloc(compound, (sizeof(compound) + sizeof(Ast *)) * sizeof(Ast));
        compound[size++] = newAst(name, description, checked, removable);
    }
    return compound;
}

void eat(Parser *parser, int type) {
    if (parser->current->type != type) {
        fprintf(stderr, "ntodo: expected %s, got %s instead. at line %d\n", tokenTypeAsStr(type), parser->current->typeAsStr, parser->line);
        exit(1);
    }
    parser->current = nextToken(parser->lexer);
}
