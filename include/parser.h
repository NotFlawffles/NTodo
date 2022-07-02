#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "ast.h"

typedef struct {
    Lexer *lexer;
    Token *current;
    unsigned int line;
} Parser;

Parser *newParser(Lexer *lexer);
Ast **parse(Parser *parser);
void eat(Parser *parser, int type);

// Token("go to sleep", string, 1)

#endif // PARSER_H
