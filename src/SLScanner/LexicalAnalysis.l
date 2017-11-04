%{
#include <stdio.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>

static GSList *__TOKEN_LIST__ = 0;
static const char *__KEYWORD_LIST__[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local"};
static long long __ID_NUMBER__ = 0;
static long long __KEYWORD_NUMBER__ = 0;
static long long __PUNC_NUMBER__ = 0;
static long long __STRING_NUMBER__ = 0;
static long long __CHAR_NUMBER__ = 0;
static long long __INT_NUMBER__ = 0;
static long long __FLOAT_NUMBER__ = 0;
static long long __CHAR_COUNT__ = 0;
static long long __LINE_COUNT__ = 1;

typedef enum {
    ID, KEYWORD, PUNC, STRING, CHAR, INT, FLOAT
} TokenType;
/*Base Token definition*/
typedef struct {
    TokenType type;
} Token;
/*ID Token definition*/
typedef struct {
    TokenType type;
    char *name;
} IDToken;
/*Keyword Token definition*/
typedef enum {
    AUTO, BREAK, CASE, _CHAR, CONST, CONTINUE, DEFAULT, DO, DOUBLE, ELSE, ENUM, EXTERN, _FLOAT, FOR, GOTO, IF, INLINE, _INT, LONG, REGISTER, RESTRICT, RETURN, SHORT, SIGNED, SIZEOF, STATIC, STRUCT, SWITCH, TYPEDEF, UNION, UNSIGNED, VOID, VOLATILE, WHILE, _ALIGNAS, _ALIGNOF, _ATOMIC, _BOOL, _COMPLEX, _GENERIC, _IMAGINARY, _NORETURN, _STATIC_ASSERT, _THREAD_LOCAL
} KeywordType;
typedef struct {
    TokenType type;
    KeywordType keyword;
} KeywordToken;
/*PUNC Token definition*/
typedef struct {
    TokenType type;
    char *punc;
} PuncToken;
/*STRING Token definition*/
typedef struct {
    TokenType type;
    char *str;
} StringToken;
/*CHAR Token definition*/
typedef struct {
    TokenType type;
    char *ch;
} CharToken;
/*INT Token definition*/
typedef struct {
    TokenType type;
    long long value;
} IntToken;
/*FLOAT Token definition*/
typedef struct {
    TokenType type;
    long double value;
} FloatToken;
/*Constructor of Token*/
Token *newToken(TokenType type, const char *yytext) {
    switch (type) {
        case CHAR: {
            CharToken *token = (CharToken *) malloc(sizeof(CharToken));
            token->type = CHAR;
            token->ch = (char *) malloc(strlen(yytext) + 1);
            char *_char_in_ = (char *)yytext + 1;
            char *_char_out_ = token->ch;
            while (*_char_in_ != 0) {
                if (_char_in_ != yytext + strlen(yytext) - 1) {
                    *_char_out_ = *_char_in_;
                    _char_out_++;
                } else {
                    *_char_out_ = 0;
                }
                _char_in_++;
            }
            return (Token *)token;
        }
        case INT: {
            IntToken *token = (IntToken *) malloc(sizeof(IntToken));
            token->type = INT;
            char *end = 0;
            if (yytext[0] == '0') {
                if (yytext[1] == 'x' || yytext[1] == 'X') {
                    token->value = strtoll(yytext, &end, 16);
                } else {
                    token->value = strtoll(yytext, &end, 8);
                }
            } else {
                token->value = strtoll(yytext, &end, 10);
            }
            return (Token *) token;
        }
        case FLOAT: {
            FloatToken * token = (FloatToken *) malloc(sizeof(FloatToken));
            token->type = FLOAT;
            char *end = 0;
            token->value = strtold(yytext, &end);
            return (Token *) token;
        }
        case STRING: {
            StringToken *token = (StringToken *) malloc(sizeof(StringToken));
            token->type = STRING;
            token->str = (char *) malloc(strlen(yytext) - 1);
            char *_char_in_ = (char *)yytext + 1;
            char *_char_out_ = token->str;
            while (*_char_in_ != 0) {
                if (_char_in_ != yytext + strlen(yytext) - 1) {
                    *_char_out_ = *_char_in_;
                    _char_out_++;
                } else {
                    *_char_out_ = 0;
                }
                _char_in_++;
            }
            return (Token *) token;
        }
        case PUNC: {
            PuncToken *token = (PuncToken *) malloc(sizeof(PuncToken));
            token->type = PUNC;
            token->punc = (char *) malloc(strlen(yytext) + 1);
            strcpy(token->punc, yytext);
            return (Token *) token;
        }
        case KEYWORD: {
            KeywordToken *token = (KeywordToken *) malloc(sizeof(KeywordToken));
            token->type = KEYWORD;
            token->keyword = -1;
            for (int keyword = 0; keyword < sizeof(__KEYWORD_LIST__); ++keyword) {
                if (!strcmp(__KEYWORD_LIST__[keyword], yytext)) {
                    token->keyword = keyword;
                    break;
                }
            }
            return (Token *) token;
        }
        default:
        case ID: {
            IDToken *token = (IDToken *) malloc(sizeof(IDToken));
            token->type = ID;
            token->name = (char *) malloc(strlen(yytext) + 1);
            strcpy(token->name, yytext);
            return (Token *) token;
        }
    }
}
void pushToken(Token *token) {
    if (!__TOKEN_LIST__) {
        __TOKEN_LIST__ = g_slist_alloc();
    }
    __TOKEN_LIST__ = g_slist_append(__TOKEN_LIST__, token);
}
%}
/*IDENTIFIER & INT definition*/
digit [0-9]
nondigit [_a-zA-Z]
hexadecimal-digit [a-fA-F0-9]
octal-digit [0-7]
nonzero-digit [1-9]
unsigned-suffix (u|U)
long-suffix (l|L)
long-long-suffix (ll|LL)
integer-suffix (({unsigned-suffix}{long-suffix}?)|({unsigned-suffix}{long-long-suffix})|({long-suffix}{unsigned-suffix}?)|({long-long-suffix}{unsigned-suffix}?))
hexadecimal-prefix (0x|0X)
hexadecimal-constant ({hexadecimal-prefix}{hexadecimal-digit}+{hexadecimal-digit})
octal-constant (0{octal-digit}*)
decimal-constant {nonzero-digit}{digit}*
integer-constant ({decimal-constant}{integer-suffix}?)|({octal-constant}{integer-suffix}?)|({hexadecimal-constant}{integer-suffix}?)
hex-quad {hexadecimal-digit}{4}
universal-character-name (\\u{hex-quad})|(\\U{hex-quad}{2})
identifier-nondigit ({nondigit}|{universal-character-name})
identifier {identifier-nondigit}({identifier-nondigit}|{digit})*
/*FLOAT definition*/
floating-suffix (f|l|F|L)
sign (\+|\-)
hexadecimal-digit-sequence {hexadecimal-digit}+
digit-sequence {digit}+
binary-exponent-part (p{sign}?{digit-sequence})|(P{sign}?{digit-sequence})
hexadecimal-fractional-constant ({hexadecimal-digit-sequence}?\.{hexadecimal-digit-sequence})|({hexadecimal-digit-sequence}\.)
exponent-part (e{sign}?{digit-sequence})|(E{sign}?{digit-sequence})
fractional-constant ({digit-sequence}?\.{digit-sequence})|({digit-sequence}\.)
hexadecimal-floating-constant ({hexadecimal-prefix}{hexadecimal-fractional-constant}{binary-exponent-part}{floating-suffix}?)|({hexadecimal-prefix}{hexadecimal-digit-sequence}{binary-exponent-part}{floating-suffix}?)
decimal-floating-constant ({fractional-constant}{exponent-part}?{floating-suffix}?)|({digit-sequence}{exponent-part}{floating-suffix}?)
floating-constant ({decimal-floating-constant}|{hexadecimal-floating-constant})
/*ENUM definition*/
enumeration-constant {identifier}
/*CHAR definition*/
hexadecimal-escape-sequence \\x{hexadecimal-digit}+
octal-escape-sequence \\{octal-digit}{1,3}
simple-escape-sequence (\\')|(\\\")|(\\\?)|(\\\\)|(\\a)|(\\b)|(\\f)|(\\n)|(\\r)|(\\t)|(\\v)
escape-sequence {simple-escape-sequence}|{octal-escape-sequence}|{hexadecimal-escape-sequence}|{universal-character-name}
c-char {escape-sequence}|[^\'\\\n]
c-char-sequence {c-char}+
character-constant (\'{c-char-sequence}\')|(L\'{c-char-sequence}\')|(u\'{c-char-sequence}\')|(U\'{c-char-sequence}\')
/*STRING definition*/
s-char ([^\"\\\n])|{escape-sequence}
s-char-sequence {s-char}+
encoding-prefix (u8)|(u)|(U)|(L)
string-literal {encoding-prefix}?\"{s-char-sequence}?\"
/*PUNCTUATOR definition*/
punctuator (\[)|(\])|(\()|(\))|(\{)|(\})|(\.)|(\-\>)|(\+\+)|(\-\-)|(&)|(\*)|(\+)|(\-)|(~)|(!)|(\/)|(\%)|(\<\<)|(\>\>)|(\<)|(\>)|(\<=)|(\>=)|(==)|(!=)|(\^)|(\|)|(&&)|(\|\|)|(\?)|(:)|(;)|(\.\.\.)|(=)|(\*=)|(\/=)|(\%=)|(\+=)|(\-=)|(\<\<=)|(\>\>=)|(&=)|(\^=)|(\|=)|(,)|(#)|(##)|(\<:)|(:\>)|(\<%)|(%\>)|(%:)|(%:%:)
/*HEADER NAME definition*/
q-char [^\"\n]
q-char-sequence {q-char}+
h-char [^\"\>]
h-char-sequence {h-char}+
header-name (\<{h-char-sequence}\>)|(\"{q-char-sequence}\")
/*PREPROCESSING NUMBER definition*/
pp-number-base ({digit})|(\.{digit})
pp-number-suffix ({digit})|({identifier-nondigit})|(e{sign})|(E{sign})|(p{sign})|(P{sign})|(\.)
pp-number {pp-number-base}{pp-number-suffix}*
/*COMMENTS definition*/
comments ("/*"([^\*]|(\*)*[^\*/])*(\*)*"*/")|(\/\/.*\n)
/*KEYWORD definition*/
keyword (auto)|(break)|(case)|(char)|(const)|(continue)|(default)|(do)|(double)|(else)|(enum)|(extern)|(float)|(for)|(goto)|(if)|(inline)|(int)|(long)|(register)|(restrict)|(return)|(short)|(signed)|(sizeof)|(static)|(struct)|(switch)|(typedef)|(union)|(unsigned)|(void)|(volatile)|(while)|(_Alignas)|(_Alignof)|(_Atomic)|(_Bool)|(_Complex)|(_Generic)|(_Imaginary)|(_Noreturn)|(_Static_assert)|(_Thread_local)
%%
{comments} {
    fprintf(yyout, "<COMMENTS (%s)>", yytext);
}
{keyword} {
    KeywordToken *token = (KeywordToken *) newToken(KEYWORD, yytext);
    pushToken((Token *) token);
    fprintf(yyout, "<KEYWORD (%s)>", __KEYWORD_LIST__[token->keyword]);
    __KEYWORD_NUMBER__++;
}
{floating-constant} {
    FloatToken *token = (FloatToken *) newToken(FLOAT, yytext);
    pushToken((Token *) token);
    fprintf(yyout, "<FLOAT constant (%LF)>", token->value);
    __FLOAT_NUMBER__++;
}
{integer-constant} {
    IntToken *token = (IntToken *) newToken(INT, yytext);
    pushToken((Token *) token);
    fprintf(yyout, "<INTEGER constant (%lld)>", token->value);
    __INT_NUMBER__++;
}
{character-constant} {
    CharToken *token = (CharToken *) newToken(CHAR, yytext);
    pushToken((Token *) token);
    fprintf(yyout, "<CHAR constant (%s)>", token->ch);
    __CHAR_NUMBER__++;
}
{string-literal} {
    StringToken *token = (StringToken *) newToken(STRING, yytext);
    pushToken((Token *) token);
    fprintf(yyout, "<STRING literal (%s)>", token->str);
    __STRING_NUMBER__++;
}
{punctuator} {
    PuncToken *token = (PuncToken *) newToken(PUNC, yytext);
    pushToken((Token *) token);
    fprintf(yyout, "<PUNCTUATOR (%s)>", token->punc);
    __PUNC_NUMBER__++;
}
{header-name} {
    fprintf(yyout, "<HEADER name (%s)>", yytext);
}
{identifier} {
    IDToken *token = (IDToken *) newToken(ID, yytext);
    pushToken((Token *) token);
    fprintf(yyout, "<IDENTIFIER (%s)>", token->name);
    __ID_NUMBER__++;
}
[\ \t\r] {}
[\n] {
    __LINE_COUNT__++;
}
%%
int main(const int argc, const char **argv) {
    if (argc >= 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    if (argc >= 3) {
        yyout = fopen(argv[2], "w");
    } else {
        yyout = stdout;
    }
    yylex();
    printf("\n\nID: %lld,\nKEYWORD: %lld,\nPUNC: %lld,\nSTRING: %lld,\nCHAR: %lld,\nINT: %lld,\nFLOAT: %lld\n",
        __ID_NUMBER__,
        __KEYWORD_NUMBER__, 
        __PUNC_NUMBER__,
        __STRING_NUMBER__,
        __CHAR_NUMBER__,
        __INT_NUMBER__,
        __FLOAT_NUMBER__
    );
    printf("Line: %lld\n", __LINE_COUNT__);
    return 0;
}
