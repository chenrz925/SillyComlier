//
// Created by 陈润泽 on 2017/10/18.
//

#ifndef SILLYCOMPLIER_MINICSCANNER_H
#define SILLYCOMPLIER_MINICSCANNER_H

#include "DeterministicFiniteAutomaton.hpp"
#include "RegularExpression.hpp"
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>

#define NEW_NUMBER(type) long long type##Number = 0
#define NUMBER(type) (type##Number)
#define COUNT(type) (type##Number++)
#define TOKEN_FROM(type, token) (*((type##Token *) token))
#define TOKEN_TO(token) (*((Token *) token))
#define PRINTR(msg) std::cout << #msg << std::endl
#define PRINT(msg) std::cout << msg

namespace Silly {
    class MiniCScanner {
    private:
        std::istream &input_;
        std::ostream &output_;
        //Counters
        NEW_NUMBER(id);
        NEW_NUMBER(keyword);
        NEW_NUMBER(punc);
        NEW_NUMBER(string);
        NEW_NUMBER(char);
        NEW_NUMBER(int);
        NEW_NUMBER(float);
        NEW_NUMBER(line);
        NEW_NUMBER(word);
        bool scanned = false;
    public:
        //Tokens
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
            NIL = -1,
            AUTO,
            BREAK,
            CASE,
            _CHAR,
            CONST,
            CONTINUE,
            DEFAULT,
            DO,
            DOUBLE,
            ELSE,
            ENUM,
            EXTERN,
            _FLOAT,
            FOR,
            GOTO,
            IF,
            INLINE,
            _INT,
            LONG,
            REGISTER,
            RESTRICT,
            RETURN,
            SHORT,
            SIGNED,
            SIZEOF,
            STATIC,
            STRUCT,
            SWITCH,
            TYPEDEF,
            UNION,
            UNSIGNED,
            VOID,
            VOLATILE,
            WHILE,
            _ALIGNAS,
            _ALIGNOF,
            _ATOMIC,
            _BOOL,
            _COMPLEX,
            _GENERIC,
            _IMAGINARY,
            _NORETURN,
            _STATIC_ASSERT,
            _THREAD_LOCAL
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
            char *value;
        } IntToken;
        /*FLOAT Token definition*/
        typedef struct {
            TokenType type;
            char *value;
        } FloatToken;
    private:
        /*Constructor of Token*/
        Token *newToken(TokenType type, const char *yytext);
        /*Punc Table*/
        std::vector<std::string> PUNC_TABLE;
        std::vector<std::string> KEYWORD_TABLE;
        std::vector<Token *> TOKEN_LIST;
        /*Check Character*/
        std::string preCut(std::string &buffer);
        Silly::RegularExpression *INT_RE = nullptr;
        Silly::DeterministicFiniteAutomaton *ID_DFA = nullptr;
    public:
        MiniCScanner();
        MiniCScanner(std::istream &input, std::ostream &log);
        void scan();
        void display();
        void stat();
    };
}

#endif //SILLYCOMPLIER_MINICSCANNER_H
