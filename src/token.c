#include "../include/token.h"
#include <malloc.h>


Token *newToken(int type, char *value) {
    Token *token     = (Token *) malloc(sizeof(Token));
    token->type      = type;
    token->typeAsStr = tokenTypeAsStr(token->type);
    token->value     = value;
    return token;
}

char *tokenTypeAsStr(int type) {
    switch (type) {
        case TOKEN_IDENTIFIER: return "identifier";
        case TOKEN_STRING:     return "string";
        case TOKEN_NEWLINE:    return "newline";
        case TOKEN_EOF:        return "EOF";
        default:               return "unknown";
    }
}
