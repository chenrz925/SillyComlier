%{
#include <stdio.h>
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
octal-constant (0{octal-digit}+)
decimal-constant {nonzero-digit}{digit}+
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

%%
{floating-constant} {
    printf("<FLOAT constant (%s)>", yytext);
}
{integer-constant} {
    printf("<INTEGER constant (%s)>", yytext);
}
{character-constant} {
    printf("<CHAR constant (%s)>", yytext);
}
{string-literal} {
    printf("<STRING literal (%s)>", yytext);
}
{punctuator} {
    printf("<PUNCTUATOR (%s)>", yytext);
}
{identifier} {
    printf("<IDENTIFIER (%s)>", yytext);
}
