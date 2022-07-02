#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include "token.h"

typedef struct {
    char *source;
    size_t index;
    char current;
} Lexer;

Lexer *newLexer(char *source);
Token *nextToken(Lexer *lexer);
void advance(Lexer *lexer);
Token *collectIdentifier(Lexer *lexer);
void skipWhitespace(Lexer *lexer);
Token *collectString(Lexer *lexer);

#endif // LEXER_H
