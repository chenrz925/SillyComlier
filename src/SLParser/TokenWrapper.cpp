//
// Created by 陈润泽 on 27/11/2017.
//

#include <SLParser/TokenWrapper.hpp>
#include <iostream>

Silly::TokenWrapper::TokenWrapper(const std::string &input, const std::string &log) {
    if (__TOKEN_LIST__) {
        isDirty = true;
        throw "ERR|DIRTY";
    }
    if (input.empty()) {
        yyin = stdin;
    } else {
        yyin = fopen(input.c_str(), "r");
    }
    if (log.empty()) {
        yyout = stdout;
    } else {
        yyout = fopen(input.c_str(), "w");
    }
    yylex();
}

std::vector<Token *> Silly::TokenWrapper::tokens() {
    std::vector<Token *> tokenList;
    g_slist_foreach(__TOKEN_LIST__, receive, nullptr);
    return tokenList;
}

void Silly::TokenWrapper::receive(gpointer data, gpointer user_data) {
    Token *token = (*(Token **)(data));
    std::cout << token->type;
}
