#include "../include/lexer.h"
#include <malloc.h>
#include <ctype.h>
#include <string.h>


Lexer *newLexer(char *source) {
    Lexer *lexer   = (Lexer *) malloc(sizeof(Lexer));
    lexer->source  = source;
    lexer->index   = 0;
    lexer->current = lexer->source[lexer->index];
    return lexer;
}

Token *nextToken(Lexer *lexer) {
    skipWhitespace(lexer);
    if (isalpha(lexer->current)) return collectIdentifier(lexer);
    switch (lexer->current) {
        case '\"': return collectString(lexer);
        case '=':
            advance(lexer);
            return newToken(TOKEN_ASSIGN, "=");
        case '\n':
            advance(lexer);
            return newToken(TOKEN_NEWLINE, "\n");
        default:   return newToken(TOKEN_EOF, "EOF");
    }
}

void advance(Lexer *lexer) {
    lexer->current = lexer->source[++lexer->index];
}

Token *collectIdentifier(Lexer *lexer) {
    char *value = (char *) malloc(sizeof(char));
    while (isalnum(lexer->current) || lexer->current == '_') {
        value = realloc(value, (strlen(value) + 1) * sizeof(char));
        strcat(value, (char []) {lexer->current, 0});
        advance(lexer);
    }
    return newToken(TOKEN_IDENTIFIER, value);
}

void skipWhitespace(Lexer *lexer) {
    while (lexer->current == ' ' || lexer->current == '\t') advance(lexer);
}

Token *collectString(Lexer *lexer) {
    char *value = (char *) malloc(sizeof(char));
    advance(lexer);
    while (lexer->current != '\"') {
        value = realloc(value, (strlen(value) + 1) * sizeof(char));
        strcat(value, (char []) {lexer->current, 0});
        advance(lexer);
    }
    advance(lexer);
    return newToken(TOKEN_STRING, value);
}
