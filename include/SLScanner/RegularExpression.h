#ifndef SILLYCOMPLIER_REGULAREXPRESSION_H
#define SILLYCOMPLIER_REGULAREXPRESSION_H

#include "NondeterministicFiniteAutomaton.h"
#include <memory>

#define SL_GTEST_PROTECTED_OPEN_RE 1
#if SL_GTEST_PROTECTED_OPEN_RE
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
        std::string pattern;
    public:
        RegularExpression(std::string pattern_);

        virtual bool operator[](std::string str);

    protected:

        virtual StateType operator()(std::string str);

#if SL_GTEST_PROTECTED_OPEN_RE
    public:
        std::string toPostfixFromTree(ETreeNode &node);
#else
    protected:
#endif
        ETreeNode tree;
        std::string toPostfix();
        void buildTree(std::string postfix);
    };
}

#endif //SILLYCOMPLIER_REGULAREXPRESSION_H
