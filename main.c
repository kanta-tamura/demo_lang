#include <stdio.h>
#include <stdlib.h>

// Tokenizer

// key      := begin | end | if | then | while | do | return | function | var | const | odd | write | writeln
// punct    := + | - | * | / | ( | ) | = | < | > | <> | <= | >= | , | . | ; | :=
// char     := [a-z|A-Z]+
// ident    := char [0-9]*
// num      := [0-9]+
typedef enum {
    TK_KEY,     // Keyword
    TK_PUNCT,   // Punctuators
    TK_IDENT,   // Identifier
    TK_NUM,     // Numeric literals
    TK_EOF,     // End-of-file markers
} TokenKind;

typedef struct Token Token;
struct Token{
    TokenKind kind; // Token kind
    Token *next;    // Next token
    char *buf;      // If kind is TK_IDENT, its string
    int val;        // If kind is TK_NUM, its value
    char *loc;      // Token location
    char *str;      // Token string
    int len;        // Token length
};

Token* new_token(TokenKind kind, Token* cur, char* str, int len) {
    Token* tok = calloc(1, sizeof(Token));
    tok->kind = kind;
    tok->str  = str;
    tok->len  = len;
    tok->next = tok;
    return tok;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
