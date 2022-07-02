#ifndef TOKEN_H
#define TOKEN_H

typedef struct {
    enum {
        TOKEN_IDENTIFIER,
        TOKEN_STRING,
        TOKEN_ASSIGN,
        TOKEN_NEWLINE,
        TOKEN_EOF,
    } type;
    char *typeAsStr;
    char *value;
} Token;

Token *newToken(int type, char *value);
char *tokenTypeAsStr(int type);

#endif // TOKEN_H
