//
// Created by 陈润泽 on 27/11/2017.
//

#ifndef SILLYCOMPLIER_TOKENWRAPPER_H
#define SILLYCOMPLIER_TOKENWRAPPER_H

#ifndef SILLYCOMPLIER_LEXICALANALYSIS_C
#define SILLYCOMPLIER_LEXICALANALYSIS_C

#include <SLParser/LexicalAnalysis.h>

#endif

#include <vector>

namespace Silly {
    class TokenWrapper {
    private:
        bool isDirty = true;
    public:
        TokenWrapper(const std::string &input, const std::string &log);

        std::vector<Token *> tokens();

    private:
        static void receive(gpointer data, gpointer user_data);
    };
}

#endif //SILLYCOMPLIER_TOKENWRAPPER_H
