//
// Created by 陈润泽 on 2017/8/13.
//

#ifndef SILLYCOMPLIER_NONDETERMINISTICFINITEAUTOMATON_H
#define SILLYCOMPLIER_NONDETERMINISTICFINITEAUTOMATON_H

#include "SLScanner/DeterministicFiniteAutomaton.h"

#define SL_GTEST_PROTECTED_OPEN_NFA 0
#if SL_GTEST_PROTECTED_OPEN_NFA

#include <gtest/gtest.h>

#endif

namespace Silly {
    class NondeterministicFiniteAutomaton : public DeterministicFiniteAutomaton {
    public:
        typedef std::multimap<State, State> ETransitionSet;
        typedef std::pair<State, State> ETransition;
    protected:
        StateSet nStates;
        AlphabetSet nAlphabets;
        TransitionSet nTransitions;
        ETransitionSet nETransitions;
        StateSet nAcceptingStates;
        bool constructed;

        void construct();

        NondeterministicFiniteAutomaton() {}

#if SL_GTEST_PROTECTED_OPEN_NFA
        public:
#else
        protected:
#endif

        StateSet eClosure(State input);

        StateSet eClosure(StateSet inputs);

        StateSet delta(State inputState, Alphabet inputAlphabet);

        StateSet delta(StateSet inputStates, Alphabet inputAlphabet);

    public:

        NondeterministicFiniteAutomaton(StateSet states_, TransitionSet transitions_, ETransitionSet etransitions_,
                                        AlphabetSet alphabets, StateSet acceptingStates);

        virtual State match(std::string str);

        virtual StateType operator()(std::string str);

        virtual void reboot();
    };
}


#endif //SILLYCOMPLIER_NONDETERMINISTICFINITEAUTOMATON_H
