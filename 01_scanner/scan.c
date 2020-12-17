#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"defs.h"
#include"data.h"
#include"decl.h"

// Return the position of character c
// in string s, or -1 if not found
static int chrpos(char *s, int c) {
    char *p;

    p = strchr(s, c);
    return p ? p - s : -1; 
}

// Get the next character from input file
static int next(void) {
    int c;

    if(Putback) {
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile);
    if('\n' == c) 
        Line++;
    return c;
}

// Putback the unwanted character
static void putback(int c) {
    Putback = c;
}

static int skip(void) {
    int c;

    c = next();
    while(' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
        c = next();
    }
    return c;
}

static int scanint(int c) {
    int k, val = 0;

    // convert each character into int value
    while((k = chrpos("0123456789", c)) >= 0) {
        val = val * 10 + k;
        c = next();
    }

    // We hit a non-integer character, put it back
    putback(c);
    return val;
}

// Scan and return next token found in input.
// Return 1 if token valid, 0 if no tokens left.
int scan(struct token *t) {
    int c;

    // Skip whitespaces
    c = skip();

    switch(c) {
        case EOF:
            return 0;
        case '+':
            t->token = T_PLUS;
            break;
        case '-':
            t->token = T_MINUS;
            break;
        case '/':
            t->token = T_SLASH;
            break;
        case '*':
            t->token = T_STAR;
            break;
        default:

            // If it's a digit, scan the literal integer value
            if(isdigit(c)) {
                t->intvalue = c;
                t->token = T_INTLIT;
                break;
            }
        
        printf("Unrecognized character %c on line %d\n", c, Line);
        exit(1);
    }

    // We found a token
    return 1;
}