//
// Created by 陈润泽 on 2017/8/10.
//

#ifndef SILLYCOMPLIER_DETERMINISTICFINITEAUTOMATON_H
#define SILLYCOMPLIER_DETERMINISTICFINITEAUTOMATON_H

#include <set>
#include <map>
#include <string>
#include "SLScanner/FiniteAutomaton.hpp"

namespace Silly {
    class DeterministicFiniteAutomaton : public Silly::FiniteAutomaton {
    protected:
        State transite(Alphabet input);

        DeterministicFiniteAutomaton() {}

        bool isFinished;

    public:
        DeterministicFiniteAutomaton(Silly::DeterministicFiniteAutomaton::StateSet states_,
                                     Silly::DeterministicFiniteAutomaton::TransitionSet transitions_,
                                     Silly::DeterministicFiniteAutomaton::AlphabetSet alphabets_,
                                     Silly::DeterministicFiniteAutomaton::StateSet acceptingStates_);

        State match(std::string str);

        StateType operator()(std::string str);
    };
}

#endif //SILLYCOMPLIER_FINITEAUTOMATON_H
