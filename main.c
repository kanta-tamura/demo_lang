#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

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
} TokenKind;

typedef struct Token Token;
struct Token{
    TokenKind kind; // Token kind
    Token *next;    // Next token
    char *str;      // Token string
    char *buf;      // If kind is TK_IDENT, its string
    int val;        // If kind is TK_NUM, its value
    int len;        // Token length
};

// input source file & token to store
char* user_input;
Token* token;

// create new token
Token* new_token(TokenKind kind, Token* cur, char* str, int len) {
    Token* tok = calloc(1, sizeof(Token));
    tok->kind = kind;
    tok->str  = str;
    tok->len  = len;
    tok->next = tok;
    return tok;
}

bool startswith(char* p, char* q) {
    return memcmp(p, q, strlen(q)) == 0;
}

Token* tokenize() {
    char* p = user_input;
    Token head;
    head.next = NULL;
    Token* cur = &head;

    while (*p) {
        // Skip whitespace characters.
        if ( isspace(*p) ) {
            p++;
            continue;
        }

        // Multi-letter punctuator
        if ( startswith(p, "<>") || startswith(p, "<=") ||
             startswith(p, ">=") || startswith(p, ":=") ) {
            cur = new_token(TK_PUNCT, cur, p, 2);
            p += 2;
            continue;
        }

        // Single-letter punctuator
        if ( strchr("+-*/()=<>,.;", *p) ) {
            cur = new_token(TK_PUNCT, cur, p++, 1);
            continue;
        }

        // Integer literal
        if ( isdigit(*p) ) {
            cur = new_token(TK_NUM, cur, p, 0);
            char* q = p;
            cur->val = strtol(p, &p, 10);
            cur->len = p - q;
            continue;
        }

        // Identifier
        if ( isalpha(*p) ) {
            cur = new_token(TK_IDENT, cur, p, 0);
            char* q = p;
            while ( isalnum(*p) ) { p++; }
            cur->len = p - q;
            continue;
        }
    }
    return head.next;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
