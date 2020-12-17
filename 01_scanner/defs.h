#ifndef __defs_h__
#define __defs_h__

enum {
    T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT
};

struct token {
    int token;
    int intvalue;
};

#endif