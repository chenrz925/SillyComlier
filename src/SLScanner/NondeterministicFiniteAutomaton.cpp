//
// Created by 陈润泽 on 2017/8/13.
//

#include <queue>
#include "SLScanner/NondeterministicFiniteAutomaton.h"

Silly::NondeterministicFiniteAutomaton::NondeterministicFiniteAutomaton(StateSet states_, TransitionSet transitions_,
                                                                        ETransitionSet etransitions_,
                                                                        AlphabetSet alphabets_,
                                                                        StateSet acceptingStates_) {
    nStates = states_;
    nAlphabets = alphabets_;
    nTransitions = transitions_;
    nETransitions = etransitions_;
    nAcceptingStates = acceptingStates_;
    constructed = false;
}

Silly::NondeterministicFiniteAutomaton::StateSet Silly::NondeterministicFiniteAutomaton::eClosure(State input) {
    std::queue<State> working;
    StateSet closure;
    working.push(input);
    while (!working.empty()) {
        State state = working.front();
        working.pop();
        for (auto it = nETransitions.find(state); it != nETransitions.end(); ++it) {
            if (it->first == state) {
                closure.insert(it->second);
                bool isNewState = false;
                for (auto fn = nETransitions.find(it->second); fn != nETransitions.end(); ++fn) {
                    if (fn->first == it->second && closure.find(fn->second) == closure.end()) {
                        isNewState = true;
                        break;
                    }
                }
                if (isNewState)
                    working.push(it->second);
            }
        }
    }
    return closure;
}

Silly::NondeterministicFiniteAutomaton::StateSet Silly::NondeterministicFiniteAutomaton::eClosure(StateSet inputs) {
    StateSet closure;
    for (auto it = inputs.begin(); it != inputs.end(); ++it) {
        StateSet output = eClosure(*it);
        closure.insert(output.begin(), output.end());
    }
    return closure;
}

Silly::FiniteAutomaton::StateSet Silly::NondeterministicFiniteAutomaton::delta(State inputState,
                                                                               Alphabet inputAlphabet) {
    StateSet target;
    if (nTransitions.find(Move(inputState, inputAlphabet)) != nTransitions.end())
        target.insert(nTransitions[Move(inputState, inputAlphabet)]);
    return target;
}

Silly::FiniteAutomaton::StateSet Silly::NondeterministicFiniteAutomaton::delta(StateSet inputStates,
                                                                               Alphabet inputAlphabet) {
    StateSet target;
    for (auto it = inputStates.begin(); it != inputStates.end(); ++it) {
        auto dt = delta(*it, inputAlphabet);
        target.insert(dt.begin(), dt.end());
    }
    return target;
}