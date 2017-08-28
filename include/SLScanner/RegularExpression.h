#ifndef SILLYCOMPLIER_REGULAREXPRESSION_H
#define SILLYCOMPLIER_REGULAREXPRESSION_H

#include "NondeterministicFiniteAutomaton.h"
#include <memory>

#define SL_GTEST_PROTECTED_OPEN 1
#if SL_GTEST_PROTECTED_OPEN
#include <gtest/gtest.h>
#endif

namespace Silly {
    class RegularExpression : public NondeterministicFiniteAutomaton {
    protected:
        struct ExpressionTree;
        typedef struct ExpressionTree {
            std::unique_ptr<ExpressionTree> left;
            std::unique_ptr<ExpressionTree> right;
            Alphabet expression;
        } ExpressionTree;
        typedef std::unique_ptr<ExpressionTree> ETreeNode;
        ETreeNode tree;
        std::string pattern;
    public:
        RegularExpression(std::string pattern_);

        virtual bool operator[](std::string str);

    protected:

        virtual StateType operator()(std::string str);

#if SL_GTEST_PROTECTED_OPEN
    public:
#else
    protected:
#endif
        std::string toPostfix();
        void buildTree(std::string postfix);
    };
}

#endif //SILLYCOMPLIER_REGULAREXPRESSION_H
