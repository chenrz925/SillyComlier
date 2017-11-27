//
// Created by 陈润泽 on 2017/8/11.
//

#ifndef SILLYCOMPLIER_FINITEAUTOMATON_H
#define SILLYCOMPLIER_FINITEAUTOMATON_H

#include <set>
#include <map>

namespace Silly {
    class FiniteAutomaton {
    public:
        typedef int32_t State;
        typedef char Alphabet;
        typedef std::pair<State, Alphabet> Move;
        typedef std::map<Move, State> TransitionSet;
        typedef std::set<State> StateSet;
        typedef std::set<Alphabet> AlphabetSet;
        typedef enum {
            Accepted = 1, NotAccepted = 0, Trapped = -1
        } StateType;
    protected:
        //定义实现
        StateSet states;
        TransitionSet transitions;
        AlphabetSet alphabets;
        StateSet acceptingStates;
        //运行状态
        State currentState;
        Alphabet currentAlphabet;
        int offset;
        void reboot();
        void count() {
            offset++;
        }

    public:
        FiniteAutomaton() {}

        StateType checkState(State state) const;
        int length() const {
            return offset;
        }
    };

    const FiniteAutomaton::AlphabetSet NumberAlphabets = {
            '0', '1', '2', '3', '4',
            '5', '6', '7', '8', '9',
            '.', '+', '-', 'e', 'E'
    };
    const FiniteAutomaton::AlphabetSet EnglishAlphabets = {
            'a', 'b', 'c', 'd', 'e',
            'f', 'g', 'h', 'i', 'j',
            'k', 'l', 'm', 'n', 'o',
            'p', 'q', 'r', 's', 't',
            'u', 'v', 'w', 'x', 'y',
            'z', 'A', 'B', 'C', 'D',
            'E', 'F', 'G', 'H', 'I',
            'J', 'K', 'L', 'M', 'N',
            'O', 'P', 'Q', 'R', 'S',
            'T', 'U', 'V', 'W', 'X',
            'Y', 'Z'
    };
    const FiniteAutomaton::AlphabetSet DigitAlphabets = {
            '0', '1', '2', '3', '4',
            '5', '6', '7', '8', '9'
    };
    const FiniteAutomaton::Alphabet EmptyAlphabet = -1;
    const FiniteAutomaton::State StartState = 0;
    const FiniteAutomaton::State TrapState = -1;
    typedef FiniteAutomaton FA;
}


#endif //SILLYCOMPLIER_FINITEAUTOMATON_H
