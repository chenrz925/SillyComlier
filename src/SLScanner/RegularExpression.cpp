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
    std::cout << postfix << std::endl;
    auto checkPop = [&](Alphabet c) -> bool {
        return c == '+' || c == '|' || c == '*';
    };
    std::stack<ETreeNode> working;
    for (auto it = postfix.begin(); it != postfix.end(); ++it) {
        ETreeNode node(new ExpressionTree);
        node->expression = *it;
        if (checkPop(*it)) {
            if (working.size() == 1) {
                node->left = std::move(working.top());
                working.pop();
            } else if (working.size() >= 2) {
                node->right = std::move(working.top());
                working.pop();
                node->left = std::move(working.top());
                working.pop();
            }
        }
        working.push(std::move(node));
    }
    tree = std::move(working.top());
    working.pop();
}