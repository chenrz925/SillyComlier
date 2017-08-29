#include "SLScanner/RegularExpression.h"
#include <stack>
#include <queue>

using namespace Silly;

RegularExpression::RegularExpression(std::string pattern_) {
    pattern = pattern_;
    for (Alphabet c : pattern_) {
        if (c != '|' && c != '+' && c != '*' && c != '(' && c != ')')
            alphabets.insert(c);
    }
    std::string postfix = toPostfix();
    buildTree(postfix);
#if SL_GTEST_PROTECTED_OPEN_RE
    std::cout << "POSTFIX FROM TREE\n" << toPostfixFromTree(tree) << std::endl;
#endif
}

NondeterministicFiniteAutomaton::StateType RegularExpression::operator()(std::string str) {
    return NondeterministicFiniteAutomaton::operator()(str);
}

bool RegularExpression::operator[](std::string str) {
    return NondeterministicFiniteAutomaton::operator()(std::move(str)) == NondeterministicFiniteAutomaton::Accepted;
}

std::string RegularExpression::toPostfix() {
    std::stack<Alphabet> working;
    std::string postfix;
    for (Alphabet a : pattern) {
        if (a == '(' || a == '+' || a == '|') {
            working.push(a);
        } else if (a == ')' || a == '\0') {
            while (true) {
                Alphabet out = working.top();
                working.pop();
                if (out == '(' || working.empty()) {
                    break;
                }
                postfix += out;

            }
        } else {
            postfix += a;
        }
    }
    while (!working.empty()) {
        Alphabet out = working.top();
        working.pop();
        postfix += out;
    }
    return postfix;
}

void RegularExpression::buildTree(std::string postfix) {
#if SL_GTEST_PROTECTED_OPEN_RE
    std::cout << "\nPOSTFIX\n" << postfix << std::endl;
#endif
    std::stack<ETreeNode> working;
    for (char &it : postfix) {
        ETreeNode node(new ExpressionTree);
        node->expression = it;
        if (it == '+' || it == '|') {
            if (working.size() < 2)
                throw std::string("Wrong Expression.");
            node->right = std::move(working.top());
            working.pop();
            node->left = std::move(working.top());
            working.pop();
        } else if (it == '*') {
            node->left = std::move(working.top());
            working.pop();
        }
        working.push(std::move(node));
    }
    tree = std::move(working.top());
}

#if SL_GTEST_PROTECTED_OPEN_RE
std::string RegularExpression::toPostfixFromTree(ETreeNode &node) {
    std::string postfix_;
    if (node->left)
        postfix_ += toPostfixFromTree(node->left);
    if (node->right)
        postfix_ += toPostfixFromTree(node->right);
    postfix_ += node->expression;
    return postfix_;
}

#endif